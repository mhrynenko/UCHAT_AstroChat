#include "../../../inc/client.h"

typedef struct DeleteChatData {
	int gid;
} deletechatdata_t;

bool ChatDeleteWrap(void* data) {
	delete_chat_button(((deletechatdata_t*)data)->gid);
	return false;
}

char* mx_json_client_get_delete_group(char* text) {
	static const char status[] = "0";

	struct json_object* parsed_json = json_tokener_parse(text);
	struct json_object* group;

	json_object_object_get_ex(parsed_json, "group_id", &group);

	int guid = json_object_get_int(group);

	deletechatdata_t* deletedata = malloc(sizeof(deletechatdata_t));
	deletedata->gid = guid;
	gdk_threads_add_idle((GSourceFunc)(&ChatDeleteWrap), (void*)deletedata);
	json_object_put(parsed_json);
	return strdup(status);
}
