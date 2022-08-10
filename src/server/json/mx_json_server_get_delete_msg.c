#include "../../../inc/server.h"

char * mx_json_server_get_delete_msg(char* text) {
    json_object* parsed_json = json_tokener_parse(text);
	json_object* message_id;
	//parse json
	json_object_object_get_ex(parsed_json, "id", &message_id);
	//send deletion to every user in group
	server_message_delete(json_object_get_int(message_id));
	json_object_put(parsed_json);
    return NULL;
    
}
