#include "../../../inc/server.h"

char * mx_json_server_make_delete_msg(int id) {
    json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(RESP_DEL_MSG));
    json_object_object_add(request, "id", json_object_new_int(id));
	char* guid = sql_get("group_id", "id", mx_itoa(id), MESSAGE);
    json_object_object_add(request, "group_id", json_object_new_int(atoi(guid)));
    return  strdup(json_object_to_json_string(request));
}
