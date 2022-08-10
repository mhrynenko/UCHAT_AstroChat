#include "../../inc/client.h"

int status_error = -1;
bool is_disconnected = false;


void Reconnect() {
    SSL_CTX *ctx;
	SSL_library_init();
	ctx = InitCTX();

	struct sockaddr_in serverAddr;
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("Reconnecting...\n");
		return;
	}

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(mx_port));
	serverAddr.sin_addr.s_addr = inet_addr(mx_ip);

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Reconnecting...\n");
        close(ret);
		return;
	}
	ssl = SSL_new(ctx);
	if(SSL_set_fd(ssl, clientSocket) == 0)
		printf("ERROR FD\n");

	if ( SSL_connect(ssl) == -1 )
        printf("COnnect ERRoR\n");
	
	printf("SSL: chipher: %s\n", SSL_get_cipher(ssl));
    X509 *cert = SSL_get_peer_certificate(ssl);
    if (cert == NULL) {
        printf("SSL: No certificates configured.\n");
    }
    else {
        char *line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("SSL: Subject: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("SSL: Issuer: %s\n", line);
        free(line);
        X509_free(cert);
    }
    printf("Reconected!\n");
    is_disconnected = false;
    if(!is_log_in)
        return;
    char* req = mx_json_client_make_log_in(user_info.user_login, user_info.user_password);
	SSL_write(ssl, req, strlen(req));
    wait_answer();
}

void* listen_handler(void *args) {
    char *temp;
    args = NULL;
	while(1) {
        if(SSL_read(ssl, buffer, BUFFER_SZ) > 0) {
            char* json = buffer;
            while(*json) {
                //printf("got json = %s\n", json);
                temp = mx_json_client_handler(json);
                json = json + strlen(json) + 1;
                status_error = atoi(temp);
            }
            bzero(buffer, sizeof(buffer));
        }
        else {
            is_disconnected = true;
            close(ret);
            
            Reconnect();
            sleep(2);
        }
        bzero(buffer, sizeof(buffer));
        mx_strdel(&temp);
        }
    return 0;
}
