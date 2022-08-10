#include "../../inc/client.h"

void* process_input(void *args) {
	// char * req;
	// while(1) {
	// 	printf("%s: ", name);
	// 	char *temp = NULL;
	// 	temp = readline(NULL);
	// 	sprintf(buffer, "%s", temp);
	// 	req = strdup(mx_json_client_make_msg(buffer, name));
	// 	//printf("json req = %s\n", req);
	// 	send(clientSocket, req, strlen(req), 0);
	// 	if(strcmp(buffer, ":exit") == 0){
	// 		close(clientSocket);
	// 		printf("[-]Disconnected from server.\n");
	// 		exit(1);
	// 	}
	// 	free(temp);
	// 	mx_strdel(&req);
	// 	bzero(buffer, sizeof(buffer));
	// }

    return args;
}

