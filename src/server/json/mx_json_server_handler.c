#include "../../../inc/server.h"
//server
char* mx_json_server_handler(char* text, client_t* client) {
    
	struct json_object *parsed_json;
    struct json_object *type;
    char *buff;
    
    parsed_json = json_tokener_parse(text);
    json_object_object_get_ex(parsed_json, "type", &type);
    int type_int = json_object_get_int(type);
    switch (type_int)
    {
    case REQ_LOGIN:
        return mx_json_server_get_log_in(text, client);
    case REQ_REGISTER:
        return mx_json_server_get_register(text);
    case REQ_SEND_MSG:
        return mx_json_server_get_msg(text, client);
    case REQ_MAKE_GROUP:
        return mx_json_server_get_group(text, client);
    case REQ_EDIT_MSG:
        return mx_json_server_get_edit_msg(text);
	case REQ_DEL_MSG:
		return mx_json_server_get_delete_msg(text);
	case REQ_EMPTY_GROUP:
		return mx_json_server_get_empty_group(text, client);
	case REQ_INVITE:
		return mx_json_server_get_invite(text);
    case REQ_DEL_GROUP:
        return mx_json_server_get_delete_gr(text, client);
    default:
        return NULL;
    }
    json_object_put(parsed_json);
    return buff;
}
