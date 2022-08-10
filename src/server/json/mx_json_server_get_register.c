#include "../../../inc/server.h"


char* mx_json_server_get_register(char* text){
    struct json_object *parsed_json;
    struct json_object *login;
    struct json_object *password;
    struct json_object *date;
    struct json_object *name;
    struct json_object *birth_date;
    char *buff = NULL;
    char* id;
    int status = ITS_FINE;

    parsed_json = json_tokener_parse(text);
    json_object_object_get_ex(parsed_json, "login", &login);
    json_object_object_get_ex(parsed_json, "password", &password);
    json_object_object_get_ex(parsed_json, "date", &date);
    json_object_object_get_ex(parsed_json, "name", &name);
    json_object_object_get_ex(parsed_json, "birth_date", &birth_date);

    char *encrypted_login = encrypt_viegen_code(json_object_get_string(login));
    char *encrypted_password = encrypt_viegen_code(json_object_get_string(password));
    
    if ((sql_get("id", "login", encrypted_login, USER)) != NULL) { //chekin if ID exist
        status = ERROR_OCCURED;
    }

    if(status == ITS_FINE){                                                             //putin into bd
        sql_set_user(encrypted_login, encrypted_password , (char *) json_object_get_string(name), (int)json_object_get_int(date), "bio", 
        (char*)json_object_get_string(birth_date), check_horoscope((char*)json_object_get_string(birth_date)));
    }

    if ((id = sql_get("id", "login", encrypted_login, USER)) == NULL) { //double check
        status = ERROR_OCCURED;
    }

    
    buff = id ? mx_json_server_make_register(atoi(id), status) : mx_json_server_make_error(RESP_REGISTER);
    mx_strdel(&encrypted_login);
    mx_strdel(&encrypted_password);
    json_object_put(parsed_json);
    return buff;

}
