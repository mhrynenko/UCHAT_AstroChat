#include "../../../inc/client.h"

char* mx_json_client_make_edit_msg(int msg_id, char* new_msg) {
    json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(REQ_EDIT_MSG));
    json_object_object_add(request, "message_id", json_object_new_int(msg_id));
    json_object_object_add(request, "new_message", json_object_new_string(new_msg));

    return  strdup(json_object_to_json_string(request));
}
