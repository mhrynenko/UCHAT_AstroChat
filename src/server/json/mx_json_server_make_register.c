#include "../../../inc/server.h"

char* mx_json_server_make_register(int user_id, int status) {
    json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(RESP_REGISTER));
    json_object_object_add(request, "status", json_object_new_int(status)), //0 if ok, 1 if user not found
    json_object_object_add(request, "id", json_object_new_int(user_id));

    


    return strdup(json_object_to_json_string(request));
}
