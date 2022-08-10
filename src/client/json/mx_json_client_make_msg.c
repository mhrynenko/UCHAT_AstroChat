#include "../../../inc/client.h"

char * mx_json_client_make_msg(char* msg, int group) {
    json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(REQ_SEND_MSG));
    json_object_object_add(request, "message", json_object_new_string(msg));
    json_object_object_add(request, "group", json_object_new_int(group));
    return  strdup(json_object_to_json_string(request));
    
}
