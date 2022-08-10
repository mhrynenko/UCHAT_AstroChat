#include "../../inc/server.h"

 void send_message_to_user(char*s, int uid) {
	pthread_mutex_lock(&clients_mutex);

	for(int i=0; i < MAX_CLIENTS; ++i){
		if(clients[i]){
			if(clients[i]->uid == uid){
				if(SSL_write(clients[i]->ssl, s, strlen(s) + 1) < 0){
					perror("ERROR: write to descriptor failed");
				}
				
				printf("send to User =  %s\n", s);
				break;
			}
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

void send_message_to_user_by_bd_id(char*s, int uid) {
	pthread_mutex_lock(&clients_mutex);

	for(int i=0; i < MAX_CLIENTS; ++i){
		if(clients[i]){
			if(clients[i]->bd_uid == uid){
				if(SSL_write(clients[i]->ssl, s, strlen(s) + 1) < 0){
					perror("ERROR: write to descriptor failed");
				}
				
				printf("send by id =  %s\n", s);
				break;
			}
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

void send_message_to_groups(char* s, t_list* list) {
	pthread_mutex_lock(&clients_mutex);

	for(int i = 0; i < MAX_CLIENTS; ++i) {
		if(clients[i]){
			for(; list != NULL; list = list->next) {
				if(clients[i]->uid == (int)list->data){
					if(SSL_write(clients[i]->ssl, s, strlen(s) + 1) < 0){
						perror("ERROR: write to descriptor failed");
					}
					break;
				}
			}
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}
