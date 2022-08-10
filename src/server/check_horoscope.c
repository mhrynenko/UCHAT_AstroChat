#include "../../inc/server.h"

int check_horoscope (char* date) {
    char** split_date = mx_strsplit(date, '.');
    int day = atoi(split_date[0]);
    int month = atoi(split_date[1]);

    switch (month)
    {
    case 1:
        if (day < 20) return CAPRICORN;
        else return AQUARIUS;
        break;
    case 2:
        if (day < 19) return AQUARIUS;
        else return PISCES;
        break;
    case 3:
        if (day < 21) return PISCES;
        else return ARIES;
        break;
    case 4:
        if (day < 20) return ARIES;
        else return TAURUS;
        break;
    case 5:
        if (day < 21) return TAURUS;
        else return GEMINI;
        break;
    case 6:
        if (day < 21) return GEMINI;
        else return CANCER;
        break;
    case 7:
        if (day < 23) return CANCER;
        else return LEO;
        break;
    case 8:
        if (day < 23) return LEO;
        else return VIRGO;
        break;
    case 9:
        if (day < 23) return VIRGO;
        else return LIBRA;
        break;
    case 10:
        if (day < 23) return LIBRA;
        else return SCORPIO;
        break;
    case 11:
        if (day < 23) return SCORPIO;
        else return SAGITTARIUS;
        break;
    case 12:
        if (day < 22) return SAGITTARIUS;
        else return CAPRICORN;
        break;
    
    default:
        break;
    }
    return 0;
}
