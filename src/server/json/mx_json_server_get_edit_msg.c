#include "../../../inc/server.h"

char *mx_json_server_get_edit_msg(char *text)
{
	json_object *parsed_json = json_tokener_parse(text);
	json_object *message_id;
	json_object *new_message;

	//parse json
	json_object_object_get_ex(parsed_json, "message_id", &message_id);
	json_object_object_get_ex(parsed_json, "new_message", &new_message);

	char *old_message = sql_get("message", "id", mx_itoa(json_object_get_int(message_id)), MESSAGE);

	//cancel request if old and new messages are identical
	if (!strcmp(old_message, json_object_get_string(new_message)))
	{
		char *gids = sql_get("group_id", "id", mx_itoa(json_object_get_int(message_id)), MESSAGE);
		char *resp = mx_json_server_make_edit_msg(strdup(json_object_get_string(new_message)), json_object_get_int(message_id), atoi(gids));
		free(gids);
		return resp;
	}

	//send messages to every user in group
	char *messagestr = strdup(json_object_get_string(new_message));
	server_message_edit(messagestr, json_object_get_int(message_id));
	free(messagestr);
	json_object_put(parsed_json);
	return NULL;
}
