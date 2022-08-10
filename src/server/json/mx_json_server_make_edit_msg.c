#include "../../../inc/server.h"

char * mx_json_server_make_edit_msg(char* msg, int id, int gid) {
    json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(RESP_EDIT_MSG));
    json_object_object_add(request, "message", json_object_new_string(msg));
    json_object_object_add(request, "id", json_object_new_int(id));
    json_object_object_add(request, "gid", json_object_new_int(gid));
    return  strdup(json_object_to_json_string(request));
}
