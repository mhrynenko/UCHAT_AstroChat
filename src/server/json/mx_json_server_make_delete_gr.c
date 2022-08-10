#include "../../../inc/server.h"

char * mx_json_server_make_delete_gr(int id) {
    json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(RESP_DEL_GROUP));
    json_object_object_add(request, "group_id", json_object_new_int(id));
    return  strdup(json_object_to_json_string(request));
}
