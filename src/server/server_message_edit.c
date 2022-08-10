#include "../../inc/server.h"

void server_message_edit(char* message, int id) {
	char* responce = mx_json_server_make_edit_msg(message, id, atoi(sql_get("group_id", "id", mx_itoa(id), MESSAGE)));

	//update message in db
	sql_update("edited", "1", "id", mx_itoa(id), MESSAGE);
	sql_update("message", message, "id", mx_itoa(id), MESSAGE);



	//get clients in the group
	t_list* members = sql_get_plural("user_id", "group_id", sql_get("group_id", "id", mx_itoa(id), MESSAGE), MEMBER);


	//send edit to connected clients
	while (members) {
		send_message_to_user_by_bd_id(responce, atoi((char*)(members->data)));
		members = members->next;
	}

	free(responce);

	return;
}
