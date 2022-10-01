#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

struct elemento {
	void* info;
	struct elemento* prox;
};

struct pilha {
	Elemento* ini;
};

Pilha* pilha_cria(void) {
	Pilha* p = (Pilha*)malloc(sizeof(Pilha));
	if (p == NULL) {
		printf("Falha na alocação de memória.\n");
		exit(1);
	}
	p->ini = NULL;
	return p;
}

int pilha_vazia(Pilha* p) {
	if (p->ini == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

void pilha_push(Pilha* p, void* info) {		//insere um novo elemento no topo da pilha
	Elemento* novo = (Elemento*)malloc(sizeof(Elemento));
	if (novo == NULL) {
		printf("Falha na alocação de memória.\n");
		exit(1);
	}
	novo->info = info;
	novo->prox = p->ini;
	p->ini = novo;
}

void* pilha_pop(Pilha* p) {		//retira o elemento do topo da pilha
	if (pilha_vazia(p)) {
		printf("Pilha Vazia.\n");
		exit(1);
	}
	Elemento* temp = p->ini;
	void* info = temp->info;
	p->ini = temp->prox;
	free(temp);
	return info;
}

void* pilha_iniInfo(Pilha* p) {		//retorna a informação contida no primeiro elemento da pilha
	if (pilha_vazia(p)) {
		return NULL;
	}
	else {
		return p->ini->info;
	}
}

void pilha_libera(Pilha* p) {
	Elemento* q = p->ini;		//ponteiro utilizado para percorrer a pilha
	while (q != NULL) {
		Elemento* temp = q->prox;
		free(q->info);
		free(q);
		q = temp;
	}
	free(p);
}