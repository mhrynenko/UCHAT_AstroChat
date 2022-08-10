#include "../../../inc/server.h"

char* mx_json_server_get_invite(char* text) {

	srand(time(NULL));
    struct json_object *parsed_json;
    struct json_object *login;
    struct json_object *group_id;

    parsed_json = json_tokener_parse(text);
    json_object_object_get_ex(parsed_json, "login", &login);
    json_object_object_get_ex(parsed_json, "group_id", &group_id);

	char *encrypted_login = encrypt_viegen_code(json_object_get_string(login));

	char* uid = sql_get("id", "login", encrypted_login, USER);
	if(!uid) return NULL;

	t_list* members = sql_get_plural("user_id", "group_id", mx_itoa(json_object_get_int(group_id)), MEMBER);

	while(members) {
		if(!strcmp(encrypted_login, sql_get("login", "id", (char*)members->data, USER))) return NULL;
		members = members->next;
	}

	add_user_to_group(atoi(uid), json_object_get_int(group_id), PEASANT, time(NULL));

	return NULL;
}

