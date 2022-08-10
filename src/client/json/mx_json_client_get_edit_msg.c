#include "../../../inc/client.h"

char* mx_json_client_get_edit_msg(char* text) {
    struct json_object *parsed_json;
    struct json_object *msg;
    struct json_object *gid;
    struct json_object *id;
    
    parsed_json = json_tokener_parse(text);
    json_object_object_get_ex(parsed_json, "id", &id);
    json_object_object_get_ex(parsed_json, "gid", &gid);
    json_object_object_get_ex(parsed_json, "message", &msg);
    //printf("NEW MSG: %s\n", json_object_get_string(msg));
    

    //add editing in GTK!
    edit_message(json_object_get_int(gid), json_object_get_int(id), (char*)json_object_get_string(msg));

    return strdup("0");
}
