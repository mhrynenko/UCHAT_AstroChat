#ifndef CL
#define CL

#include "uchat.h"
#include "gtk.h"

extern char *name;
extern char *password;
extern char buffer[BUFFER_SZ];
extern int clientSocket, ret;
extern char *request_buffer;
extern int status_error;
extern SSL *ssl;
extern bool is_log_in;
extern bool is_disconnected;

extern char* mx_ip;
extern char* mx_port;

typedef struct user_info {
    int user_id;
    char* user_name;
    char* user_login;
    char* user_password;
    char* predict;
    int Zodiack;
} user_info_t;

extern user_info_t user_info;

typedef struct ChatMsgData {
	int guid;
	int sender_id;
    int message_id;
	unsigned int date;
    int is_edited;
	char* text;
	char* name;

} chatmsgdata_t;
SSL_CTX* InitCTX(void);
void load_certs(SSL_CTX* context, char* cert_name, char* key_name);

void* process_input(void *args);
void* listen_handler(void *args);
char* mx_json_client_get_register(char* text);

char* mx_json_client_handler(char* text);
char* mx_json_client_make_register(char* name, char* login, char* password, char* date);
char * mx_json_client_make_log_in(char* login, char* password);
char * mx_json_client_make_individual_chat(char* login_guest);
char * mx_json_client_make_msg(char* msg, int group);
char * mx_json_client_make_delete_msg(int id);
char * mx_json_client_make_prediction();
char* mx_json_client_make_edit_msg(int msg_id, char* new_msg);
char* mx_json_client_make_invite(char* login_guest, int gid);
char* mx_json_client_make_empty_group(char *name);
char* mx_json_client_make_del_group(int id);

char* mx_json_client_get_register(char* login);
char *mx_json_client_get_msg(char* msg);
char* mx_json_client_get_log_in(char* text);
char* mx_json_client_get_group(char* text);
char* mx_json_client_get_prediction(char* text);
char* mx_json_client_get_edit_msg(char* text);
char* mx_json_client_get_delete_msg(char* text);
char *mx_json_client_get_delete_msg(char *text);
char* mx_json_client_get_delete_group(char* text);

void create_group_from_userlist(char* list, char *name);

int check_correct_login (char *login);
int check_correct_password (char *password, int* strong_pass);

//GUI
void wait_answer();
void GUI_login(int argc, char *argv[]);
void GUI_chat();
void CreateTab (char* name, int groupid);
void ChatSendMsg (chatmsgdata_t* msg);
void delete_message(int groupid, int msgid);
void edit_message(int groupid, int msgid, char* newtext);
void delete_chat_button(int chatroomid);

extern int lastgid;

#endif
