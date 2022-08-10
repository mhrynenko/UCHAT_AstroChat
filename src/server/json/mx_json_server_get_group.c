#include "../../../inc/server.h"


static bool check_group_existance(char* owner_id, char* guest_id) {

    t_list *list_o = sql_get_plural("group_id", "user_id", owner_id, MEMBER);
    t_list *list_g = sql_get_plural("group_id", "user_id", guest_id, MEMBER);
    t_list *temp_o = list_o;
   
    
    while(temp_o) {
        if((sql_get("type", "id", (char*)temp_o->data, GROUP) != NULL) 
        && (atoi(sql_get("type", "id", (char*)temp_o->data, GROUP)) == INDIVIDUAL)) {
            t_list *temp_g = list_g;
            while(temp_g) {
                if((sql_get("type", "id", (char*)temp_g->data, GROUP) != NULL) 
                && (atoi(sql_get("type", "id", (char*)temp_g->data, GROUP)) == INDIVIDUAL)) {
                    if(strcmp((char*)temp_o->data, (char*)temp_g->data) == 0)
                        return true;
                    }
                temp_g = temp_g->next;
        }
    }
    temp_o = temp_o->next;
    }
    return false;
}

char* mx_json_server_get_group(char* json_string, client_t* client){
    srand(time(NULL));
    struct json_object *parsed_json;
    struct json_object *login_guest;
    struct json_object *group_type;
   
    char *buff = NULL;
    int status = ITS_FINE;
    int link = rand();

    parsed_json = json_tokener_parse(json_string);
    json_object_object_get_ex(parsed_json, "login_guest", &login_guest);
    json_object_object_get_ex(parsed_json, "group_type", &group_type);

    char *encrypted_login = encrypt_viegen_code(json_object_get_string(login_guest));
    
    if (((sql_get("id", "login", encrypted_login, USER)) == NULL) 
    || (client->bd_uid == atoi(sql_get("id", "login", encrypted_login, USER)) 
    || (check_group_existance(mx_itoa(client->bd_uid), sql_get("id", "login", encrypted_login, USER))))) { //chekin if ID exist and if dialog already exist
        status = ERROR_OCCURED;
        buff = mx_json_server_make_error(RESP_MAKE_GROUP);
        return buff;
    }


    char *chat_name = mx_strjoin(client->name, "--");
    char *guest_name = sql_get("name", "login", encrypted_login, USER);
    chat_name = mx_strjoin(chat_name, guest_name);

    if(status == ITS_FINE){                                                             //putin into bd
        sql_set_group(chat_name, mx_itoa(link), "test", client->bd_uid, json_object_get_int(group_type), time(NULL));
        buff = mx_json_server_make_group(json_object_get_int(group_type), chat_name, status, -1);
        int guid = atoi(sql_get("id", "link", mx_itoa(link), GROUP));
        add_user_to_group(client->bd_uid, guid, ADMIN, time(NULL));
        add_user_to_group(atoi(sql_get("id", "login", encrypted_login, USER)), guid, ADMIN, time(NULL));
    }

  
    

	mx_strdel(&chat_name); 
    mx_strdel(&guest_name); 
    mx_strdel(&encrypted_login);
    json_object_put(parsed_json);
    return buff;

}
