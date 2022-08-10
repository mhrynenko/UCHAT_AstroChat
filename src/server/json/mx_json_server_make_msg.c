#include "../../../inc/server.h"

char * mx_json_server_make_msg(char* msg, int message_id, char *sender_name, int group, int user_id, int data) {
    json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(REQ_SEND_MSG));
    json_object_object_add(request, "username", json_object_new_string(sender_name));
    json_object_object_add(request, "message", json_object_new_string(msg));
    json_object_object_add(request, "message_id", json_object_new_int(message_id));
    json_object_object_add(request, "user_id", json_object_new_int(user_id));
    json_object_object_add(request, "group", json_object_new_int(group));
	json_object_object_add(request, "date", json_object_new_int(data));
    json_object_object_add(request, "edited", json_object_new_string(sql_get("edited", "id", mx_itoa(message_id), MESSAGE)));
    return  strdup(json_object_to_json_string(request));
    
}
