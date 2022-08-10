#include "../../../inc/client.h"



bool ChatSendMsgWrap(void* data) {
	ChatSendMsg(((chatmsgdata_t*)data));
	return false;
}

char* mx_json_client_get_msg(char* text) {
	static const char status[] = "0";

	struct json_object* parsed_json = json_tokener_parse(text);
	struct json_object* group;
	struct json_object* message;
	struct json_object* message_id;
	struct json_object* username;
	struct json_object* user_id;
	struct json_object* date;
	struct json_object* edited;

	json_object_object_get_ex(parsed_json, "group", &group);
    json_object_object_get_ex(parsed_json, "message", &message);
	json_object_object_get_ex(parsed_json, "username", &username);
	json_object_object_get_ex(parsed_json, "user_id", &user_id);
	json_object_object_get_ex(parsed_json, "date", &date);
	json_object_object_get_ex(parsed_json, "message_id", &message_id);
	json_object_object_get_ex(parsed_json, "edited", &edited);

	int guid = json_object_get_int(group);
	int uid = json_object_get_int(user_id);
	unsigned int data_msg = json_object_get_int(date);
	int msg_id = json_object_get_int(message_id);
	char* msgstr = strdup(json_object_get_string(message));
	char* unamestr = strdup(json_object_get_string(username));
	int edt = atoi(strdup(json_object_get_string(edited)));

	chatmsgdata_t* msgdata = malloc(sizeof(chatmsgdata_t));
	msgdata->guid = guid;
	msgdata->text = msgstr;
	msgdata->name = unamestr;
	msgdata->message_id = msg_id;
	msgdata->sender_id = uid;
	msgdata->date = data_msg;
	msgdata->is_edited = edt;
	//printf("\a\n");
	gdk_threads_add_idle((GSourceFunc)(&ChatSendMsgWrap), (void*)(msgdata));
	json_object_put(parsed_json);
	return strdup(status);
}
