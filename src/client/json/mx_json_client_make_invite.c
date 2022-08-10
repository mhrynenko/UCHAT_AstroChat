#include "../../../inc/client.h"

char * mx_json_client_make_invite(char* login_guest, int gid) {
    json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(REQ_INVITE));
    json_object_object_add(request, "login", json_object_new_string(login_guest));
    json_object_object_add(request, "group_id", json_object_new_int(gid));
   
    return  strdup(json_object_to_json_string(request));
    
}
