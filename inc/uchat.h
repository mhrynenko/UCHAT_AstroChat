#ifndef CH
#define CH

#define PORT 4444

#include "../libraries/json-c/include/json-c/json.h"
#include "../libmx/inc/libmx.h"
#include <sqlite3.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <editline/readline.h>
#include <pthread.h>
#include <time.h>
#include <sys/stat.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/bio.h>


enum JSON_STUFF {
    REQ_LOGIN, 
    REQ_REGISTER,
    REQ_MAKE_GROUP,
    REQ_SEND_MSG, 
    REQ_EDIT_MSG,
    REQ_DEL_MSG,
	REQ_INVITE,
	REQ_EMPTY_GROUP,
    REQ_DEL_GROUP,
    RESP_LOGIN, 
    RESP_REGISTER,
    RESP_MAKE_GROUP,
    RESP_SEND_MSG,
    RESP_EDIT_MSG,
    RESP_DEL_MSG,
    RESP_DEL_GROUP
};

enum PERMISSIONS {
    ADMIN,
    MODER,
    PEASANT
};

enum GROUP_TYPES {
    INDIVIDUAL,
    PUBLIC
};

enum STATUS_ERROR {
    ITS_FINE,
    ERROR_OCCURED
};

enum TABLES {
    USER,
    GROUP,
    MEMBER,
    MESSAGE,
    PREDICTION
};

enum HOROSCOPE {
    ARIES, //овен
    TAURUS, //телец
    GEMINI, //близнецы
    CANCER, //рак
    LEO, //лев
    VIRGO, //дева
    LIBRA, //весы
    SCORPIO, //скорпион
    SAGITTARIUS, //стрелец
    CAPRICORN, //козерог
    AQUARIUS, //водолей
    PISCES //рыбы
};

#define MAX_CLIENTS 100
#define BUFFER_SZ 128000

/* Client structure */
typedef struct {
	struct sockaddr_in address;
	int sockfd;
	int uid;
	int bd_uid;
	char name[32];
    SSL *ssl;
    SSL_CTX* ctx;
    //groups_id
} client_t;

extern client_t *clients[MAX_CLIENTS];
extern pthread_mutex_t clients_mutex;
extern _Atomic unsigned int cli_count;

#endif
