#include "../../../inc/client.h"

char * mx_json_client_make_delete_msg(int id) {
    json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(REQ_DEL_MSG));
    json_object_object_add(request, "id", json_object_new_int(id));
    return  strdup(json_object_to_json_string(request));
}
