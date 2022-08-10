#include "../../../inc/client.h"
//client

char* mx_json_client_handler(char* text) {
    
	struct json_object *parsed_json;
    struct json_object *type;
    char *buff;
    
    parsed_json = json_tokener_parse(text);
    json_object_object_get_ex(parsed_json, "type", &type);
    int type_int = json_object_get_int(type);


    

    switch (type_int)
    {
    case RESP_LOGIN:
        return mx_json_client_get_log_in(text);
    case RESP_REGISTER:
        return mx_json_client_get_register(text);
    case REQ_SEND_MSG:
        return mx_json_client_get_msg(text);
    case RESP_MAKE_GROUP:
        return mx_json_client_get_group(text);
    case RESP_EDIT_MSG:
        return mx_json_client_get_edit_msg(text);
	case RESP_DEL_MSG:
		return mx_json_client_get_delete_msg(text);
	case RESP_DEL_GROUP:
		return mx_json_client_get_delete_group(text);
    default:
        return NULL;
    }
    json_object_put(parsed_json);
    return buff;
}
