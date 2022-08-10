NAME_C = uchat

NAME_S = uchat_server

SRCS = src/server/*.c -Ilibraries/openssl/

SRCC = src/client/*.c -Ilibraries/openssl/

JSON_CL = src/client/json/*.c
JSON_SR = src/server/json/*.c
FRONT_FILES = front/src/*.c
DATA_BASE = dataBase/*.c

JSON_LIB = libraries/json-c/lib/libjson-c.a
OPENSSL_LIB = libraries/openssl/libcrypto.a libraries/openssl/libssl.a 
LIB = libmx/libmx.a

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror -ledit -lsqlite3
GTKFLAGS = `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` 

all: install

install: 
	@printf "\x1b[32mCompiling libmx...\n\x1b[0m"
	@make -C libmx/
	@printf "\x1b[34mCompiling server...\n\x1b[0m"
	@clang $(CFLAGS) $(SRCS) $(JSON_SR) $(DATA_BASE) $(LIB) $(JSON_LIB) $(OPENSSL_LIB) -o $(NAME_S) 
	@printf "\x1b[33mCompiling client...\n\x1b[0m"
	@clang $(CFLAGS) -o $(NAME_C) $(FRONT_FILES) $(SRCC) $(JSON_CL) $(LIB) $(JSON_LIB) $(OPENSSL_LIB) $(GTKFLAGS) 
	@printf "\x1b[32mDone!\n\x1b[0m"
	
rm:
	@rm -rf $(NAME_S) $(NAME_C)

clean:
	@rm -rf $(LIB)	
cl:
	@make rm
	@printf "\x1b[34mCompiling server...\n\x1b[0m"
	@clang $(CFLAGS) $(SRCS) $(JSON_SR) $(DATA_BASE) $(LIB) $(JSON_LIB) $(OPENSSL_LIB) -o $(NAME_S) 
	@printf "\x1b[33mCompiling client...\n\x1b[0m"
	@clang $(CFLAGS) -o $(NAME_C) $(FRONT_FILES) $(SRCC) $(JSON_CL) $(LIB) $(JSON_LIB) $(OPENSSL_LIB) $(GTKFLAGS) 
	@printf "\x1b[32mDone!\n\x1b[0m"

reinstall:
	@make rm
	@make
