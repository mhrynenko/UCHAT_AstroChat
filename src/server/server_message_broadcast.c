#include "../../inc/server.h"

void server_message_broadcast(char* message, int group, int date, client_t* client) {

	//add message to db
	char filename[] = "";
	int id_message = sql_set_message (client->bd_uid, group, 0, message, 0, filename, 0, 0, date);

	char* user_msg_id = sql_get("user_id", "id", mx_itoa(id_message), MESSAGE);
	char* user_name = sql_get("name", "id", user_msg_id, USER);
	
	char* temp = sql_get("id", "date_of_sending", mx_itoa(date), MESSAGE);
	int message_id = atoi(temp);


	char* responce = mx_json_server_make_msg(message, message_id ,user_name,  group, client->bd_uid, time(NULL));

	//get clients in the group
	t_list* members = sql_get_plural("user_id", "group_id", mx_itoa(group), MEMBER);


	//send message to connected clients
	while (members) {
		send_message_to_user_by_bd_id(responce, atoi((char*)(members->data)));
		members = members->next;
	}

	free(responce);

	return;
}

