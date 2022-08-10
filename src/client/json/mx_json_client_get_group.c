#include "../../../inc/client.h"

int lastgid = -1;

typedef struct TabData {
	char* name;
	int guid;
} tabdata_t;

bool CreateTabWrap( void* data) {
	CreateTab(((tabdata_t*)data)->name, ((tabdata_t*)data)->guid);
	free(data);
	return false;
}

char* mx_json_client_get_group(char* text) {
    struct json_object *parsed_json;
    struct json_object *status;
	struct json_object *name;
	struct json_object *guid_json;

    parsed_json = json_tokener_parse(text);
    json_object_object_get_ex(parsed_json, "status", &status);
	json_object_object_get_ex(parsed_json, "group_name", &name);
	json_object_object_get_ex(parsed_json, "group_id", &guid_json);

    if(json_object_get_int(status)){
        return strdup(json_object_to_json_string(status));
    }
	int guid = json_object_get_int(guid_json);

	if(guid != -1) {
		tabdata_t* data = malloc(sizeof(tabdata_t)); 
		data->name = strdup(json_object_get_string(name)); 
		data->guid = guid;
		gdk_threads_add_idle((GSourceFunc)(&CreateTabWrap), (void*)(data));
	}
	
	lastgid = guid;


    return strdup(json_object_to_json_string(status));
}
