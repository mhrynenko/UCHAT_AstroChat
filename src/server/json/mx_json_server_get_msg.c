#include "../../../inc/server.h"

char * mx_json_server_get_msg(char* text, client_t* client) {
    json_object* parsed_json = json_tokener_parse(text);
	json_object* message;
	json_object* group;
	//parse json
	json_object_object_get_ex(parsed_json, "message", &message);
	json_object_object_get_ex(parsed_json, "group", &group);
	
	//send messages to every user in group
	char* messagestr = strdup(json_object_get_string(message));
	server_message_broadcast(messagestr,(int) json_object_get_int(group), time(NULL), client);
	free(messagestr);
	json_object_put(parsed_json);
    return  NULL;//ssstrdup(mx_json_server_make_msg(messagestr, client->name, json_object_get_int(group), client->bd_uid));
    
}
