#include "../../inc/server.h"

const char* line = "abcdefghijklmnopqrstuvwxyz0123456789";
//абвгдежзийклмнопрстуфхцчшщъыъэюя
const char* secret_word = "uchat";


char *encrypt_viegen_code(const char *word) {
    char* res = mx_strnew(strlen(word));
    int ind  = 0;

    for(int i = 0; i < mx_strlen(word); i++){
        if (strchr(line, word[i])) {
            res[i] = line[(mx_get_char_index(line, word[i]) + mx_get_char_index(line, secret_word[ind])) % strlen(line)];
            if (ind == 4) ind = 0;
            else ind++;
        }
        else res[i] = word[i];
    }
    return res;
}

char *decrypt_viegen_code(const char *word) {
    char* res = mx_strnew(strlen(word));
    int ind  = 0;

    for(int i = 0; i < mx_strlen(word); i++){
        if (strchr(line, word[i])) {
            res[i] = line[(mx_strlen(line) + mx_get_char_index(line, word[i]) - mx_get_char_index(line, secret_word[ind])) % strlen(line)];
            if (ind == 4) ind = 0;
            else ind++;
        }
        else res[i] = word[i];
    }
    return res;
}

