#include "header_bd.h"

int sql_open_db (sqlite3 **db){

    int rc = sqlite3_open("dataBase/chat.db", db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        
        return 1;
    }
    return 0;
}

void sql_create_db () {
    sqlite3 *db;
    char *err_msg = 0;
    sql_open_db(&db);
    char *sql_1 = "CREATE TABLE IF NOT EXISTS Member(\"id\""
                "INTEGER NOT NULL UNIQUE, \"user_id\" INTEGER NOT NULL,"
	            "\"group_id\" INTEGER," 
                "\"type\" INTEGER NOT NULL,"
                "\"was_read\" INTEGER NOT NULL,"
                "\"date_of_entry\" INTEGER NOT NULL,"
	            "PRIMARY KEY(\"id\" AUTOINCREMENT));";
    
    int rc = sqlite3_exec(db, sql_1, 0, 0, &err_msg);
    char *sql_2 = "CREATE TABLE IF NOT EXISTS \"User\" ("
            "\"id\"	INTEGER NOT NULL UNIQUE,"
            "\"login\"	TEXT NOT NULL UNIQUE,"
            "\"password\"	TEXT NOT NULL,"
            "\"name\"	TEXT NOT NULL,"
            "\"registration_date\"	INTEGER NOT NULL,"
            "\"bio\"	TEXT DEFAULT \"\","
            "\"data_of_birth\"	TEXT NOT NULL,"
            "\"zodiac_sign\"	INTEGER,"
            "PRIMARY KEY(\"id\" AUTOINCREMENT))";
    
    rc = sqlite3_exec(db, sql_2, 0, 0, &err_msg);
    char *sql_3 = "CREATE TABLE IF NOT EXISTS \"Groups\" ("
            "\"id\"	INTEGER NOT NULL UNIQUE,"
            "\"name\"	TEXT NOT NULL,"
            "\"link\"	TEXT NOT NULL UNIQUE,"
            "\"bio\"	TEXT,"
            "\"id_creator\"	INTEGER NOT NULL,"
            "\"type\"	INTEGER NOT NULL,"
            "\"date_of_creation\"	INTEGER NOT NULL,"
            "PRIMARY KEY(\"id\" AUTOINCREMENT))";
    
    rc = sqlite3_exec(db, sql_3, 0, 0, &err_msg);
    char *sql_4 = "CREATE TABLE IF NOT EXISTS \"Message\" ("
            "\"id\"	INTEGER NOT NULL UNIQUE,"
            "\"user_id\"	INTEGER NOT NULL,"
            "\"group_id\"	INTEGER NOT NULL,"
            "\"type\"	INTEGER NOT NULL,"
            "\"message\"	TEXT,"
            "\"edited\"	INTEGER,"
            "\"file_name\"	TEXT,"
            "\"file_size\"	INTEGER,"
            "\"file_id\"	INTEGER,"
            "\"date_of_sending\"	INTEGER NOT NULL,"
            "PRIMARY KEY(\"id\" AUTOINCREMENT))";
    
    rc = sqlite3_exec(db, sql_4, 0, 0, &err_msg);
    char *sql_5 = "CREATE TABLE IF NOT EXISTS \"Prediction\" ("
            "\"id\"	INTEGER NOT NULL UNIQUE,"
            "\"prediction\"	TEXT NOT NULL UNIQUE,"
            "PRIMARY KEY(\"id\" AUTOINCREMENT))";
    
    rc = sqlite3_exec(db, sql_5, 0, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return;
    } 
    
    sqlite3_close(db);
}

char *join(const char* s1, const char* s2) {
    char* result = malloc(strlen(s1) + strlen(s2) + 1);

    if (result) // thanks @pmg
    {
        strcpy(result, s1);
        strcat(result, s2);
    }

    return result;
}

char* sql_get(char* find_var, char* seek_var, char *value_seek_var, int table) {
    sqlite3 *db;
    sqlite3_stmt *res;
    
    sql_open_db(&db);
    char *sql = "SELECT ";
    sql = join(sql, find_var);
    switch (table)
    {
    case USER:
        sql = join(sql, " FROM User WHERE ");
        break;
    case GROUP:
        sql = join(sql, " FROM Groups WHERE ");
        break;
    case MESSAGE:
        sql = join(sql, " FROM Message WHERE ");
        break;
    case MEMBER:
        sql = join(sql, " FROM Member WHERE ");
        break;
    case PREDICTION:
        sql = join(sql, " FROM Prediction WHERE ");
        break;
    default:
        break;
    }
    sql = join(sql, seek_var);
    sql = join(sql, " = \"");
    sql = join(sql, value_seek_var);
    sql = join(sql, "\"");
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, 3);
    } else {
        
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    
    int step = sqlite3_step(res);
    char *answer = (char *)sqlite3_column_text(res, 0);
    if (answer) {
        char* result = malloc(strlen((const char*)answer));

        if (step == SQLITE_ROW)
        result = strcpy(result, (const char*)sqlite3_column_text(res, 0));    
        
        sqlite3_finalize(res);
        sqlite3_close(db);
        
        return result;
    }
    else {
        sqlite3_finalize(res);
        sqlite3_close(db);
        return NULL;
    }
}

static int callback(void *answ, int argc, char **argv, char **azColName){
   int i;
   azColName = 0;
   for(i = 0; i<argc; i++){
       char *value = strdup(argv[i]);
      mx_push_back((t_list**)answ, (void*)value);
   }
   return 0;
}

t_list* sql_get_plural(char* find_var, char* seek_var, char *value_seek_var, int table) {
   sqlite3 *db;
   char *errMsg = 0;
   int rc;
    t_list *answ = NULL;
   sql_open_db(&db);

   /* Create SQL statement */
    char *sql = "SELECT ";
    sql = join(sql, find_var);
    switch (table)
    {
    case USER:
        sql = join(sql, " FROM User WHERE \"");
        break;
    case GROUP:
        sql = join(sql, " FROM Groups WHERE \"");
        break;
    case MESSAGE:
        sql = join(sql, " FROM Message WHERE \"");
        break;
    case MEMBER:
        sql = join(sql, " FROM Member WHERE \"");
        break;
    case PREDICTION:
        sql = join(sql, " FROM Prediction WHERE ");
        break;
    default:
        break;
    }
    sql = join(sql, seek_var);
    sql = join(sql, "\" = \"");
    sql = join(sql, value_seek_var);
    sql = join(sql, "\"");
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)&answ, &errMsg);

   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", errMsg);
      sqlite3_free(errMsg);
   }
   sqlite3_close(db);
   return answ;
}

char* sql_get_last_id () {
    sqlite3 *db;
    sqlite3_stmt *res;
    
    sql_open_db(&db);
    char *sql = "SELECT MAX(id) FROM Message";
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, 3);
    } else {
        
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    
    int step = sqlite3_step(res);
    char *answer = (char *)sqlite3_column_text(res, 0);
    if (answer) {
        char* result = malloc(strlen((const char*)answer));

        if (step == SQLITE_ROW)
        result = strcpy(result, (const char*)sqlite3_column_text(res, 0));    
        
        sqlite3_finalize(res);
        sqlite3_close(db);
        
        return result;
    }
    else {
        sqlite3_finalize(res);
        sqlite3_close(db);
        return NULL;
    }
}

int sql_update(char *update_var, char *value_update_var, char *seek_var, char *value_seek_var, int table) {
    sqlite3 *db;
    char *err_msg = 0;
    sql_open_db(&db);
    char *sql = "UPDATE ";
    switch (table)
    {
    case USER:
        sql = join(sql, "User SET ");
        break;
    case GROUP:
        sql = join(sql, "Groups SET ");
        break;
    case MESSAGE:
        sql = join(sql, "Message SET ");
        break;
    case MEMBER:
        sql = join(sql, "Member SET ");
        break;
    case PREDICTION:
        sql = join(sql, "Prediction SET ");
        break;
    default:
        break;
    }
    sql = join(sql, update_var);
    sql = join(sql, " = \"");
    sql = join(sql, value_update_var);
    sql = join(sql, "\" WHERE ");
    sql = join(sql, seek_var);
    sql = join(sql, " = \"");
    sql = join(sql, value_seek_var);
    sql = join(sql, "\";");
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc == SQLITE_OK) return 0;
    else {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    }
}

int sql_delete(char* seek_var, char *value_seek_var, int table) {
    sqlite3 *db;
    sql_open_db(&db);
    char *sql = "DELETE";
    char *err_msg = 0;
    switch (table)
    {
    case USER:
        sql = join(sql, " FROM User WHERE ");
        break;
    case GROUP:
        sql = join(sql, " FROM Groups WHERE ");
        break;
    case MESSAGE:
        sql = join(sql, " FROM Message WHERE ");
        break;
    case MEMBER:
        sql = join(sql, " FROM Member WHERE ");
        break;
    case PREDICTION:
        sql = join(sql, " FROM Prediction WHERE ");
        break;
    default:
        break;
    }
    sql = join(sql, seek_var);
    sql = join(sql, " = \"");
    sql = join(sql, value_seek_var);
    sql = join(sql, "\"");
    
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc == SQLITE_OK) return 0;
    else {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    }
}
