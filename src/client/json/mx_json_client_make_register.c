#include "../../../inc/client.h"

char* mx_json_client_make_register(char* name, char* login, char* password, char* birht_date) {
    json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(REQ_REGISTER));
    json_object_object_add(request, "name", json_object_new_string(name));
    json_object_object_add(request, "login", json_object_new_string(login));
    json_object_object_add(request, "password", json_object_new_string(password));
    json_object_object_add(request, "birth_date", json_object_new_string(birht_date));
    json_object_object_add(request, "date", json_object_new_uint64(time(NULL)));
    return strdup(json_object_to_json_string(request));
}
