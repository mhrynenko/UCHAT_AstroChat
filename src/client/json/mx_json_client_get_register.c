#include "../../../inc/client.h"


char* mx_json_client_get_register(char* text) {
    struct json_object *parsed_json;
    struct json_object *status;
    struct json_object *id;

    parsed_json = json_tokener_parse(text);
    json_object_object_get_ex(parsed_json, "status", &status);
    json_object_object_get_ex(parsed_json, "id", &id);

    return strdup(json_object_to_json_string(status));
}
