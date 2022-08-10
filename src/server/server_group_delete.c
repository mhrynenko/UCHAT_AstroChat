#include "../../inc/server.h"

void server_group_delete(int id, int uid) {
	char* responce = mx_json_server_make_delete_gr(id);

	//get clients in the group
	t_list* members = sql_get_plural("user_id", "group_id", mx_itoa(id), MEMBER);
	t_list* membersI = sql_get_plural("id", "group_id", mx_itoa(id), MEMBER);
	t_list* membersIbuff = membersI;

	bool isAdmin = false;
	char* memebrUID;

	while(membersI) {
		if(atoi(sql_get("user_id", "id", (char*)(membersI->data), MEMBER)) == uid) {
			isAdmin = (atoi(sql_get("type", "id", (char*)(membersI->data), MEMBER)) == ADMIN);
			memebrUID = (char*)(membersI->data);
			break;
		}
		membersI = membersI->next;
	}

	if(isAdmin) {
		//delete group from db
		sql_delete("id", mx_itoa(id), GROUP);

		while(membersIbuff) {
			sql_delete("id", (char*)(membersIbuff->data), MEMBER);
			membersIbuff = membersIbuff->next;
		}

		//send deletion to connected clients
		while (members) {
			send_message_to_user_by_bd_id(responce, atoi((char*)(members->data)));
			members = members->next;
		}

	} else {
		sql_delete("id", memebrUID, MEMBER);
		send_message_to_user_by_bd_id(responce, uid);	
	}
	free(responce);

	return;
}
