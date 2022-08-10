#include "../../inc/server.h"

void *handle_client(void *arg){
	char buff_out[BUFFER_SZ];
	int leave_flag = 0;

	cli_count++;
	client_t *cli = (client_t *)arg;
	char *resp;
	

	if (SSL_accept(cli->ssl) <= 0){
		ERR_print_errors_fp(stderr);
		abort();
	}
        

	while(1){
		if (leave_flag) {
			break;
		}
		int receive = SSL_read(cli->ssl, buff_out, BUFFER_SZ);
		
		if (receive > 0){
			if(strlen(buff_out) > 0){
				//printf("json req = %s ;\n", buff_out);
				resp = mx_json_server_handler(buff_out, cli);
				if(resp) {
					//printf("json resp = %s\n", resp);

					send_message_to_user(resp, cli->uid);
					mx_strdel(&resp);
				}
			}
		} else if (receive == 0 || strcmp(buff_out, "exit") == 0){
			sprintf(buff_out, "%s has left\n", cli->name);
			printf("%s", buff_out);
			leave_flag = 1;
		} else {
			printf("ERROR: -1\n");
			leave_flag = 1;
		}

		bzero(buff_out, sizeof(buff_out));
	}

	close(cli->sockfd);
	queue_remove(cli->uid);
	free(cli);
	cli_count--;
	pthread_detach(pthread_self());

	return NULL;
}
