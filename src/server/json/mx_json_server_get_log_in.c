#include "../../../inc/server.h"



char* mx_json_server_get_log_in(char* text, client_t* client) {
    struct json_object *parsed_json;
    struct json_object *login;
    struct json_object *password;
    
    char* id;
    int status = ITS_FINE;
    char *buff = NULL;
    
    parsed_json = json_tokener_parse(text);
    json_object_object_get_ex(parsed_json, "login", &login);
    json_object_object_get_ex(parsed_json, "password", &password);

    char *encrypted_login = encrypt_viegen_code(json_object_get_string(login));
    char *encrypted_password = encrypt_viegen_code(json_object_get_string(password));
    // printf("enc_l %s enc_p %s\n", encrypted_login, encrypted_password);
    // printf("dec_l %s dec_p %s\n", decrypt_viegen_code(encrypted_login), decrypt_viegen_code(encrypted_password));
    
    if ((id = sql_get("id", "login", encrypted_login, USER)) == NULL) { //chekin login
        //printf("dec_l %s\n", decrypt_viegen_code(encrypted_login));
        status = ERROR_OCCURED;
    }
    else if(strcmp(sql_get("password", "id", id, USER), encrypted_password) != 0) { //chekin password
        status = ERROR_OCCURED;
    }
    else {
        buff = mx_json_server_make_log_in(atoi(id), status);
        client->bd_uid = atoi(id);
        char* name = sql_get("name", "id", mx_itoa(client->bd_uid), USER);
        strcpy(client->name, name);
        free(name);
		
		send_message_to_user(buff, client->uid);
		send_user_groups(client->bd_uid);
		
    }
    buff = status == ITS_FINE ? NULL : mx_json_server_make_error(RESP_LOGIN);
    mx_strdel(&encrypted_login);
    mx_strdel(&encrypted_password);
    json_object_put(parsed_json);
    return buff;
}

