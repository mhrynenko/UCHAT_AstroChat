#include "../../../inc/client.h"

char* mx_json_client_make_del_group(int id) {
    json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(REQ_DEL_GROUP));
    json_object_object_add(request, "id", json_object_new_int(id));
    return  strdup(json_object_to_json_string(request));
}

