#include "../../../inc/client.h"

char * mx_json_client_make_log_in(char* login, char* password) {
    json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(REQ_LOGIN));
    json_object_object_add(request, "login", json_object_new_string(login));
    json_object_object_add(request, "password", json_object_new_string(password));

    return  strdup(json_object_to_json_string(request));
    
}
