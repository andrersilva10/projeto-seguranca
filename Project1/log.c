#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
struct listaChar {
	char info;
	struct listaChar *prox;
};
struct listaChar* lst;
void insere(struct listaChar*, char);
void exibir(struct listaChar*);
//int iniciaThread(char* argv[]);
//DWORD WINAPI IniciaLog(LPVOID lpParameter);

void insere(struct listaChar* ponteiro, char valor) {
	struct listaChar* aux = NULL;
	for (aux = ponteiro; aux != NULL; aux = aux->prox) {
		if (aux->prox != NULL) {
			aux->prox = (struct listaChar*)malloc(sizeof(struct listaChar));
			aux->prox->info = valor;
			aux->prox->prox = NULL;
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




int iniciaThread(char* argv[]) {
	lst = (struct listaChar*) malloc(sizeof(struct listaChar));
	lst->info = '$';

	HANDLE thread;

	thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)IniciaLog,
		(LPVOID)argv[0], 0, NULL);

	if (thread)
	{
		return WaitForSingleObject(thread, INFINITE);
	}
	return 1;
	
}
*/