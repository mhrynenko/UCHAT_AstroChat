#include "../../../inc/server.h"

char *mx_json_server_get_field(char *json_str, char *field) {
    json_object *root, *temp;
    root = json_tokener_parse(json_str);
    temp = json_object_object_get(root, field);
    return strdup(json_object_get_string(temp));

}
