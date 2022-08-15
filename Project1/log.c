#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include "mysql.h"
#define SERVIDOR "localhost"
#define USUARIO "root"
#define SENHA "abzdwe123"
#define BD "keylogger" 
#define __STDC_WANT_LIB_EXT1__ 1
#define ARQUIVO_DESTINO "program.txt"
struct lista {
	char* info;
	size_t length;
	struct lista* prox;
};

void log(struct lista*);
struct lista* inserir(struct lista* lst, char* info);
char* toString(struct lista* lst);
char* lerTodoArquivo();

void log(struct lista* lst) {
	char* texto = toString(lst);
	char* textoArquivo = lerTodoArquivo();
	
	int len = 0;
	len = strlen(texto);
	len += strlen(textoArquivo);

	//cria uma string com um tamanho um pouco maior que as duas que serão concatenadas
	char* teste = (char*)malloc((sizeof(char) * len) + sizeof(char) * 5);

	strcpy(teste, textoArquivo);
	strcat(teste, texto);
	
	int num;
	FILE *fptr;

	fptr = fopen(ARQUIVO_DESTINO, "w");

	// exiting program 
	if (fptr == NULL) {
		printf("Error!");
		exit(1);
	}
	fprintf(fptr, "%s", teste);
	fclose(fptr);

	//limpa a memoria
	free(texto);
	free(textoArquivo);
	free(teste);
}

char* lerTodoArquivo() {
	FILE *in_file = fopen(ARQUIVO_DESTINO, "r");
	struct lista* lst = NULL;

    struct stat sb;
    stat(ARQUIVO_DESTINO, &sb);

    char *file_contents = malloc(sb.st_size + (sizeof(char) * 5));

    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
        //printf("> %s\n", file_contents);
		lst = inserir(lst, file_contents);
    }

    fclose(in_file);
	char* retorno = toString(lst);
	return retorno;
    //exit(EXIT_SUCCESS);
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

	char *retorno = (char*)malloc(sizeof(char) * tamanho + (sizeof(char) * 1));
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