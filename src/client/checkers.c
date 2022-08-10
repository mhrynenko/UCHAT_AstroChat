#include "../../inc/client.h"

int check_correct_login (char *login) {
    if (strlen(login) < 5) return 1;
    for (int i = 0; i < mx_strlen(login); i++) {
        if (mx_isalpha(login[i]) || mx_isdigit(login[i]) || login[i] == '_') 
            continue;
        else return 1;
    }
    return 0;
}

int check_correct_password (char *password, int* strong_pass) {
    if (strlen(password) < 5) return 1;
    char *correct = "_-@.*/";
    bool is_lower = false, is_upper = false, is_digit = false, is_symbol = false;
    for (int i = 0; i < mx_strlen(password); i++) {
        if (mx_isalpha(password[i])) {
            if (password[i] >= 'a' && password[i] <= 'z')
                is_lower = true;
            else is_upper = true;
        }        
        else if (mx_isdigit(password[i]))
            is_digit = true;
        else if (strchr(correct, password[i]))
            is_symbol = true;
        else return 1;
    }
    *strong_pass = 0;
    if (is_lower) (*strong_pass)++;
    if (is_upper) (*strong_pass)++;
    if (is_digit) (*strong_pass)++;
    if (is_symbol) (*strong_pass)++;
    return 0;
}
