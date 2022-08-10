#include "../../inc/server.h"

void send_user_groups(int uid) {
	//get groups of the user
	t_list* groups = sql_get_plural("group_id", "user_id", mx_itoa(uid), MEMBER);
	
	//send groups to user
	while(groups) {
		//group id
		int group = atoi((char*) (groups->data));
		//get group name from bd by group id
		char* gname = sql_get("name", "id", mx_itoa(group), GROUP);
		if(!gname) {
			printf("User %d is member of non existent group %d\n", uid, group);
			groups = groups->next;
			continue;
		}

		//make group json
		char* json = mx_json_server_make_group(0, gname, 0, group);
		//send group json
		printf("\nsending group %d\n", group);
		send_message_to_user_by_bd_id(json, uid);
		free(json);
		
		//send messages from the group
		t_list* messages = sql_get_plural("id", "group_id", (char*)groups->data, MESSAGE);
		printf("\nsending messages\n");
		while(messages) {
			char* message = (char*)(messages->data);
			//printf("asdasdasdasd %s asdsadaasdasd\n", message);
			char* text = sql_get("message", "id", message, MESSAGE);
			char* user_id_txt = sql_get("user_id", "id", message, MESSAGE);
			if(!user_id_txt || !text)
			{
				messages = messages->next;
				continue;
			}
			
			
			char* username = sql_get("name", "id", strdup(user_id_txt), USER);

			if(!username)
			{
				messages = messages->next;
				continue;
			}

			char* data_of_sending = sql_get("date_of_sending", "id", message, MESSAGE);

			char* msg_json = mx_json_server_make_msg(text, atoi(message), username, group, atoi(user_id_txt), atoi(data_of_sending));
			send_message_to_user_by_bd_id(msg_json, uid);

			free(msg_json);

			messages = messages->next;
			//usleep(25);
		}

		groups = groups->next;
	}

}
