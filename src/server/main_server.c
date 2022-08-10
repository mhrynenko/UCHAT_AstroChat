#include "../../inc/server.h"

_Atomic unsigned int cli_count = 0;
static int uid = 10;
client_t *clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
char *ip;


void DEBUG_ADD_USERS() {
    sql_set_user(encrypt_viegen_code("mark"), encrypt_viegen_code("00000"), "mark", time(NULL), "test", "21.01.2000", CANCER);
    sql_set_user(encrypt_viegen_code("apik"), encrypt_viegen_code("00000"), "apik", time(NULL), "test", "21.01.2000", PISCES);
	sql_set_user(encrypt_viegen_code("nastya"), encrypt_viegen_code("00000"), "nastya", time(NULL), "test", "21.01.2000", AQUARIUS);
	sql_set_user(encrypt_viegen_code("kolya"), encrypt_viegen_code("00000"), "kolya", time(NULL), "test", "21.01.2000", VIRGO);
	sql_set_user(encrypt_viegen_code("max"), encrypt_viegen_code("00000"), "max", time(NULL), "test", "21.01.2000", TAURUS);
	sql_set_table_prediction();
}


SSL_CTX* InitServerCTX(void)
{
    const SSL_METHOD *ssl_method;
    SSL_CTX *ssl_context; 

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    ssl_method = TLS_server_method();
    ssl_context = SSL_CTX_new(ssl_method);

    if(ssl_context == NULL) {
        ERR_print_errors_fp(stderr);
        abort();
    }

    return ssl_context;
}



void load_certs(SSL_CTX* context, char* cert_name, char* key_name) {
    // set the local certificate from file with certificate
    if ( SSL_CTX_use_certificate_file(context, cert_name, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    // set the private key from key_name (may be the same as cert_name)
    if ( SSL_CTX_use_PrivateKey_file(context, key_name, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    // verify private key
    if ( !SSL_CTX_check_private_key(context) )
    {
        fprintf(stderr, "ERROR: Private key does not match the public certificate\n");
        abort();
    }
}


int main_server(int portARG) {
	system("clear");
    SSL_CTX *ctx;
	SSL_library_init();
    ctx = InitServerCTX();

    load_certs(ctx, "cert.pem", "key.pem");
    


	
	int port = portARG;
	int option = 1;
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	pthread_t tid;
  /* Socket settings */


	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_port = htons(port);
  /* Ignore pipe signals */
	//signal(SIGPIPE, SIG_IGN);

	if(setsockopt(listenfd, SOL_SOCKET,(SO_REUSEADDR),(char*)&option,sizeof(option)) < 0){ //indus magic
		perror("ERROR: setsockopt failed");
    return EXIT_FAILURE;
	}
	/* Bind */
	if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR: Socket binding failed");
		return EXIT_FAILURE;
	}

  /* Listen */
	if (listen(listenfd, 10) < 0) {
		perror("ERROR: Socket listening failed");
		return EXIT_FAILURE;
		}

	sql_create_db();


	char *check = get_prediction(0);
	if(!check) {
		DEBUG_ADD_USERS();
		printf("DATA BASE HAD BEEN SET\n");
	}
	else printf("DATA BASE EXIST\n");


	printf("=== WELCOME TO THE CHATROOM ===\n");

	while(1){
		SSL *ssl;
		socklen_t clilen = sizeof(cli_addr);
		connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &clilen);
		/* Client settings */
		client_t *cli = (client_t *)malloc(sizeof(client_t));
		cli->address = cli_addr;
		cli->sockfd = connfd;
		cli->uid = uid++;

		ssl = SSL_new(ctx);
        SSL_set_fd(ssl, connfd);
		

		 if (SSL_accept(ssl) <= 0) {
             ERR_print_errors_fp(stderr);
		 }
        
		cli->ssl = ssl;
		cli->ctx = ctx;

		/* Add client to the queue and fork thread */
		queue_add(cli);
		pthread_create(&tid, NULL, &handle_client, (void*)cli);

		/* Reduce CPU usage */
		sleep(1);
	}
}


int main(int argc, char** argv){
	if(argc != 2) {
		printf("usage: ./uchat_server PORT\n");
		return -1;
	}
	else{

		char hostname[1024];
		gethostname(hostname, 1024);
		struct hostent* he = gethostbyname(hostname);
		ip = inet_ntoa(*(struct in_addr*)he->h_addr);
		printf("IP = %s\n", ip);

		pid_t process_id = 0;
		pid_t sid = 0;
		
		process_id = fork();
		if (process_id < 0) {
			exit(1);
		}
		if (process_id > 0) {
			printf("Server launched, pid = %d\n", process_id);
			exit(0);
		}
		umask(0);
		sid = setsid();
		
		if (sid < 0)
			exit(1);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		main_server(atoi(argv[1]));
	}
	
	return EXIT_SUCCESS;
}
