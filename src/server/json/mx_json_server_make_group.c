#include "../../../inc/server.h"

char* mx_json_server_make_group(int group_type, char* name, int status, int guid) {
	struct json_object* json = json_object_new_object();
	json_object_object_add(json, "type", json_object_new_int(RESP_MAKE_GROUP));
	json_object_object_add(json, "status", json_object_new_int(status));
	json_object_object_add(json, "group_type", json_object_new_int(group_type));
	json_object_object_add(json, "group_id", json_object_new_int(guid));
	json_object_object_add(json, "group_name", json_object_new_string(name));
	return strdup(json_object_get_string(json));
}

