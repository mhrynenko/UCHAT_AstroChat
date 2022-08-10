#include "../../inc/client.h"

char *name;
char *password;
char buffer[BUFFER_SZ];
int clientSocket, ret;
SSL* ssl;

char* mx_ip;
char* mx_port;

SSL_CTX* InitCTX(void)
{
    const SSL_METHOD *ssl_method;
    SSL_CTX *ssl_context;

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    ssl_method = TLS_client_method();
    ssl_context = SSL_CTX_new(ssl_method);
    if (ssl_context == NULL) {
        ERR_print_errors_fp(stderr);
        abort();
    }

    return ssl_context;
}


int main(int argc, char *argv[]){
	if(argc != 3) {
		printf("Usage: ./uchat IP PORT");
		return - 1;
	}
	mx_ip = argv[1];
	mx_port = argv[2];
	
	system("clear");

	SSL_CTX *ctx;
	SSL_library_init();
	ctx = InitCTX();
	struct sockaddr_in serverAddr;
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(mx_port));
	serverAddr.sin_addr.s_addr = inet_addr(mx_ip);

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");
	ssl = SSL_new(ctx);
	if(SSL_set_fd(ssl, clientSocket) == 0)
		printf("ERROR FD\n");

	if ( SSL_connect(ssl) == -1 )
        printf("COnnect ERRoR\n");
	
    X509 *cert = SSL_get_peer_certificate(ssl);
    if (cert == NULL) {
        printf("SSL: No certificates configured.\n");
    }
    else {
        char *line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        free(line);
        X509_free(cert);
    }

	pthread_t thread_listen;
    int status_listen, status_addr;
	status_listen = pthread_create(&thread_listen, NULL, listen_handler, NULL);
	if (status_listen != 0) {
		printf("main error: can't create thread, status = %d\n", status_listen);
		exit(-12);
	}

	GUI_login(argc, argv);
	status_listen = pthread_join(thread_listen, (void**)&status_addr);
	
	close(ret);
    SSL_CTX_free(ctx); 
	return 0;
}
