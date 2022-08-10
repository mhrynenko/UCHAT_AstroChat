#include "../../../inc/server.h"

char* mx_json_server_make_error(int operation) {
    struct json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(operation));
    json_object_object_add(request, "status", json_object_new_int(1));

    return  strdup(json_object_to_json_string(request));
}
