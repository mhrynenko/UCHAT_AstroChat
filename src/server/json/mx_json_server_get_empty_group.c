#include "../../../inc/server.h"

char* mx_json_server_get_empty_group(char* text, client_t* client){
    srand(time(NULL));
   
   struct json_object *parsed_json;
   struct json_object *group_name;

    parsed_json = json_tokener_parse(text);
    json_object_object_get_ex(parsed_json, "group_name", &group_name);

    int link = rand();
    char *chat_name = mx_strdup(json_object_get_string(group_name));

    sql_set_group(chat_name, mx_itoa(link), "test", client->bd_uid, PUBLIC, time(NULL));

	int guid = atoi(sql_get("id", "link", mx_itoa(link), GROUP));
    
	add_user_to_group(client->bd_uid, guid, ADMIN, time(NULL));

	free(chat_name);

    return NULL;

}
