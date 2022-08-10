#ifndef DTBS
#define DTBS


#include "../inc/uchat.h"

int sql_open_db (sqlite3 **db);
void sql_create_db ();
char *join(const char* s1, const char* s2);

//To find one variable
char* sql_get(char* find_var, char* seek_var, char *value_seek_var, int table);

//To find all variables with some rule. If you dont need queue of ALL values in table (for examp. all User id)
//just choose seek_var = value_seek_var -> sql_get_plural("id", "", "", USER)
t_list* sql_get_plural(char* find_var, char* seek_var, char *value_seek_var, int table);

//To update all variables with some rule
int sql_update(char *update_var, char *value_update_var, char *seek_var, char *value_seek_var, int table);

//To delet all fields with some rule
int sql_delete(char* seek_var, char *value_seek_var, int table);

//setters
int sql_set_user (char* login, char* password, char* name, int registration_date, char* bio, char* data_of_birth, int zodiac_sign);
void sql_set_member (int user_id, int group_id, int type, int date_of_entry);
int sql_set_group (char* name, char* link, char* bio, int id_creator, int type, int date_of_creation);
char* sql_get_last_id ();
int sql_set_message (int user_id, int group_id, int type, char *message, int edited, char *file_name, int file_size, int file_id, int date_of_sending);
int sql_set_prediction (char* prediction);
void sql_set_table_prediction ();

#endif
