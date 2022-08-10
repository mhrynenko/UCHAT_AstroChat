#include "../../../inc/server.h"

char * mx_json_server_get_delete_gr(char* text, client_t* client) {
    json_object* parsed_json = json_tokener_parse(text);
	json_object* group_id;

	//parse json
	json_object_object_get_ex(parsed_json, "id", &group_id);
    // something
	server_group_delete(json_object_get_int(group_id), client->bd_uid);
    return NULL;
}
