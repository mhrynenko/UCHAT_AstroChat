#include "../../inc/server.h"


void add_user_to_group (int uid, int guid, int type, int date) {

	sql_set_member (uid, guid, type, date);

	//we alseo need to send group message to client
	char* json = mx_json_server_make_group(type, sql_get("name", "id", mx_itoa(guid), GROUP), 0, guid);
	send_message_to_user_by_bd_id(json, uid);
}

