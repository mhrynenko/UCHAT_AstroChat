#include "../../inc/client.h"

void create_group_from_userlist(char* list, char *group_name) {
	lastgid = -1;
	char* group_req = mx_json_client_make_empty_group(group_name);
	SSL_write(ssl, group_req, strlen(group_req));
	free(group_req);

	char* c = list;
	char* logins[512];
	int loginsind = 0;

	logins[loginsind] = c;
	loginsind++;

	while(*c) {
		if(*c == ',' || *c == ' ' || *c == ';') {
			*c = 0;
			logins[loginsind] = c + 1;
			loginsind++;
		}

		c++;
	}
	
	while(lastgid == -1);

	for(int i = 0; i < loginsind; i++) {
		if(strlen(logins[i])) {
			char* invite_req = mx_json_client_make_invite(logins[i], lastgid);
			SSL_write(ssl, invite_req, strlen(invite_req));
			free(invite_req);
		}
	}
}

