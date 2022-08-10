#include "../../../inc/client.h"

char* mx_json_client_make_empty_group(char* gr_name) {
	json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(REQ_EMPTY_GROUP));
    json_object_object_add(request, "group_name", json_object_new_string(gr_name));
    return  strdup(json_object_to_json_string(request));
}

