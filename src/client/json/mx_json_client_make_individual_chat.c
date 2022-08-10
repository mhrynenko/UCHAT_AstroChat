#include "../../../inc/client.h"

char * mx_json_client_make_individual_chat(char* login_guest) {
    json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(REQ_MAKE_GROUP));
    json_object_object_add(request, "login_guest", json_object_new_string(login_guest));
    json_object_object_add(request, "group_type", json_object_new_int(INDIVIDUAL));
   
    return  strdup(json_object_to_json_string(request));
    
}
