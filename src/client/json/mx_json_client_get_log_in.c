#include "../../../inc/client.h"

user_info_t user_info;

char* mx_json_client_get_log_in(char* text) {
    struct json_object *parsed_json;
    struct json_object *status;
    struct json_object *id;
    struct json_object *login;
    struct json_object *name;
    struct json_object *prediction;
    struct json_object *zodiac_sign;

    parsed_json = json_tokener_parse(text);
    json_object_object_get_ex(parsed_json, "id", &id);
    json_object_object_get_ex(parsed_json, "status", &status);
    json_object_object_get_ex(parsed_json, "login", &login);
    json_object_object_get_ex(parsed_json, "name", &name);
    json_object_object_get_ex(parsed_json, "sign", &zodiac_sign);
    json_object_object_get_ex(parsed_json, "prediction", &prediction);

    
    if(json_object_get_int(status)){
        return strdup(json_object_to_json_string(status));
    }

    user_info.Zodiack = json_object_get_int(zodiac_sign);
    user_info.predict = (char*)json_object_get_string(prediction);
    user_info.user_id = json_object_get_int(id);
    user_info.user_login = (char*)json_object_get_string(login);
    user_info.user_name = (char*)json_object_get_string(name);

    return strdup(json_object_to_json_string(status));
}
