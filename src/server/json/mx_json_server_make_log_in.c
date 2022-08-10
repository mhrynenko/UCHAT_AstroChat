#include "../../../inc/server.h"

char* mx_json_server_make_log_in(int user_id, int status) {
    struct json_object *request = json_object_new_object();
    json_object_object_add(request, "type", json_object_new_int(RESP_LOGIN));
    json_object_object_add(request, "status", json_object_new_int(status)); //0 if ok, 1 if user not found
    json_object_object_add(request, "id", json_object_new_int(user_id));
    json_object_object_add(request, "name", json_object_new_string(sql_get("name", "id", mx_itoa(user_id), USER)));
    json_object_object_add(request, "login", json_object_new_string(decrypt_viegen_code(sql_get("login", "id", mx_itoa(user_id), USER))));
	char* pred = get_prediction(user_id);
	char preddef[] = "Someting went wrong today";
    json_object_object_add(request, "prediction", json_object_new_string(pred ? pred : preddef));
	free(pred);
	json_object_object_add(request, "sign", json_object_new_string(sql_get("zodiac_sign", "id", mx_itoa(user_id), USER)));

    //groups,

    return strdup(json_object_get_string(request));
}
