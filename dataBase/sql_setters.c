 #include "header_bd.h"

void sql_set_member (int user_id, int group_id, int type, int date_of_entry){
    sqlite3 *db;
    char *err_msg = 0;
    
    sql_open_db(&db);
    char *sql = "INSERT INTO Member(user_id, group_id, was_read, type, date_of_entry) VALUES (";
    sql = join(sql, mx_itoa(user_id));
    sql = join(sql, ", ");
    sql = join(sql, mx_itoa(group_id));
    sql = join(sql, ", ");
    sql = join(sql, "0");
    sql = join(sql, ", ");
    sql = join(sql, mx_itoa(type));
    sql = join(sql, ", ");
    sql = join(sql, mx_itoa(date_of_entry));
    sql = join(sql, ");");
    
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return;
    } 
    
    sqlite3_close(db);
}

int sql_set_user (char* login, char* password, char* name, int registration_date, char* bio, char* data_of_birth, int zodiac_sign){
    sqlite3 *db;
    char *err_msg = 0;
    
    sql_open_db(&db);
    char *sql = "INSERT INTO User(login, password, name, registration_date, bio, data_of_birth, zodiac_sign) VALUES (\"";
    sql = join(sql, login);
    sql = join(sql, "\", \"");
    sql = join(sql, password);
    sql = join(sql, "\", \"");
    sql = join(sql, name);
    sql = join(sql, "\", ");
    sql = join(sql, mx_itoa(registration_date));
    sql = join(sql, ", \"");
    sql = join(sql, bio);
    sql = join(sql, "\", \"");
    sql = join(sql, data_of_birth);
    sql = join(sql, "\", ");
    sql = join(sql, mx_itoa(zodiac_sign));
    sql = join(sql, ");");
    
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    } 
    
    sqlite3_close(db);
    return 0;
}

int sql_set_prediction (char* prediction){
    sqlite3 *db;
    char *err_msg = 0;
    
    sql_open_db(&db);
    char *sql = "INSERT INTO Prediction(prediction) VALUES (\"";
    sql = join(sql, prediction);
    sql = join(sql, "\");");
    
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    }
    sqlite3_close(db);
    return 0;
}

int sql_set_group (char* name, char* link, char* bio, int id_creator, int type, int date_of_creation) {
    sqlite3 *db;
    char *err_msg = 0;
    
    sql_open_db(&db);
    char *sql = "INSERT INTO Groups(name, link, bio, id_creator, type, date_of_creation) VALUES (\"";
    sql = join(sql, name);
    sql = join(sql, "\", \"");
    sql = join(sql, link);
    sql = join(sql, "\", \"");
    sql = join(sql, bio);
    sql = join(sql, "\", ");
    sql = join(sql, mx_itoa(id_creator));
    sql = join(sql, ", ");
    sql = join(sql, mx_itoa(type));
    sql = join(sql, ", ");
    sql = join(sql, mx_itoa(date_of_creation));
    sql = join(sql, ");");
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    } 
    
    sqlite3_close(db);
    return 0;
}
int sql_set_message (int user_id, int group_id, int type, char *message, int edited, char *file_name, int file_size, int file_id, int date_of_sending) {
    sqlite3 *db;
    char *err_msg = 0;
    
    sql_open_db(&db);
    char *sql = "INSERT INTO Message(user_id, group_id, type, message, edited, file_name, file_size, file_id, date_of_sending) VALUES (";
    sql = join(sql, mx_itoa(user_id));
    sql = join(sql, ", ");
    sql = join(sql, mx_itoa(group_id));
    sql = join(sql, ", ");
    sql = join(sql, mx_itoa(type));
    sql = join(sql, ", \"");
    sql = join(sql, message);
    sql = join(sql, "\", ");
    sql = join(sql, mx_itoa(edited));
    sql = join(sql, ", \"");
    sql = join(sql, file_name);
    sql = join(sql, "\",");
    sql = join(sql, mx_itoa(file_size));
    sql = join(sql, ", ");
    sql = join(sql, mx_itoa(file_id));
    sql = join(sql, ", ");
    sql = join(sql, mx_itoa(date_of_sending));
    sql = join(sql, ");");
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return -1;
    } 
    
    sqlite3_close(db);
    return atoi(sql_get_last_id());
}
