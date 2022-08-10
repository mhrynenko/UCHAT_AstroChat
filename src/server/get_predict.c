#include "../../inc/server.h"

void sql_set_table_prediction () {
    char* file = mx_file_to_str("dataBase/Predictions.txt");
    char** pred = mx_strsplit(file, '\n');
    while (*pred) {
        sql_set_prediction(*pred);
        pred++;
    }
    
}

char* get_prediction(int id) {
    int PRED_SIZE = 42;
    time_t rawtime;
    struct tm *timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    srand(atoi(join(mx_itoa(timeinfo->tm_yday + 1), mx_itoa(id))));
    char *pred = sql_get("prediction", "id", mx_itoa(rand() % PRED_SIZE + 1), PREDICTION);   
    return pred ? strndup(pred, mx_get_char_index(pred, '.')) : NULL;
}
