#ifndef SR
#define SR

#include "uchat.h"
#include "../dataBase/header_bd.h"



void *handle_client(void *arg);

void queue_add(client_t *cl);
void queue_remove(int uid);

void send_message_to_user(char*s, int uid);
void send_message_to_user_by_bd_id(char*s, int uid);

char *mx_json_server_get_field(char *json_str, char *field);
char *mx_json_server_get_log_in(char* text, client_t* client);
char *mx_json_server_get_msg(char* text, client_t* client);
char * mx_json_server_get_edit_msg(char* text);
char * mx_json_server_get_deletes_msg(char* text);
char *mx_json_server_get_register(char* text);
char* mx_json_server_get_group(char* json_string, client_t* client);
char* mx_json_server_get_predicition(client_t* client);
char * mx_json_server_get_delete_msg(char* text);
char* mx_json_server_get_invite(char* text);
char* mx_json_server_get_empty_group(char* text, client_t* client);
char * mx_json_server_get_delete_gr(char* text, client_t* client);
void server_message_delete(int id);
void server_group_delete(int id, int uid);

char *mx_json_server_handler(char* text, client_t* client);

char *mx_json_server_make_log_in(int user_id, int status);
char *mx_json_server_make_msg(char* msg, int message_id, char *sender_name, int group, int user_id, int data);
char * mx_json_server_make_edit_msg(char* msg, int id, int gid);
char * mx_json_server_make_delete_msg(int id);
char *mx_json_server_make_register(int user_id, int status);
char* mx_json_server_make_group(int group_type, char* name, int status, int guid);
char * mx_json_server_make_delete_gr(int id);

void server_message_broadcast(char* message, int group, int date, client_t* client);
void server_message_edit(char* message, int id);
void add_user_to_group (int uid, int guid, int type, int date);
void send_user_groups(int uid);

char* mx_json_server_make_error(int operation);

char* get_prediction(int id);
int check_horoscope (char* date);
char *encrypt_viegen_code(const char *word);
char *decrypt_viegen_code(const char *word);

#endif
