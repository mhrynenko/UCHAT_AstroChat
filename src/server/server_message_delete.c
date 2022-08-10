#include "../../inc/server.h"

void server_message_delete(int id) {
	char* responce = mx_json_server_make_delete_msg(id);

	//get clients in the group
	t_list* members = sql_get_plural("user_id", "group_id", sql_get("group_id", "id", mx_itoa(id), MESSAGE), MEMBER);


	//delete message from db
	sql_delete("id", mx_itoa(id), MESSAGE);


	//send deletion to connected clients
	while (members) {
		send_message_to_user_by_bd_id(responce, atoi((char*)(members->data)));
		members = members->next;
	}

	free(responce);

	return;
}
