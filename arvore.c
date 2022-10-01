#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

struct arvexp {
	int operador;	// vale 1 se o nó armazena um operador e vale 0 se nó armazena um número
	void* info;
	struct arvexp* pai;
	struct arvexp* esq;
	struct arvexp* dir;
};

Arvexp* cria_vazia(void) {
	return NULL;
}

int arv_vazia(Arvexp* noh) {
	if (noh == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

Arvexp* cria_noh(void* info, Arvexp* pai, int operador) {
	Arvexp* noh = (Arvexp*)malloc(sizeof(Arvexp));
	if (noh == NULL) {
		printf("Erro na alocação de memória.\n");
		exit(1);
	}
	noh->info = info;
	noh->pai = pai;
	noh->esq = noh->dir = NULL;
	noh->operador = operador;
	return noh;
}

void anexa(Arvexp* noh, Arvexp* filho) {
	Arvexp* p = noh;
	while (!arv_vazia(p->dir) && !arv_vazia(p->esq)) {
		p = p->pai;
	}
	if (arv_vazia(noh->dir)) {
		filho->pai = p;
		p->dir = filho;
	}
	else {
		filho->pai = p;
		p->esq = filho;
	}
}

int calcula(Arvexp* noh, int* divisao_por_zero) {
	if (noh != NULL) {
		if (noh->operador) {
			if (*(char*)noh->info == '-') {
				return calcula(noh->esq, divisao_por_zero) - calcula(noh->dir, divisao_por_zero);
			}
			if (*(char*)noh->info == '+') {
				return calcula(noh->esq, divisao_por_zero) + calcula(noh->dir, divisao_por_zero);
			}
			if (*(char*)noh->info == '/') {
				if (calcula(noh->dir, divisao_por_zero) == 0) {
					*divisao_por_zero = 1;
					return 0;
				}
				return calcula(noh->esq, divisao_por_zero) / calcula(noh->dir, divisao_por_zero);
			}
			if (*(char*)noh->info == '*') {
				return calcula(noh->esq, divisao_por_zero) * calcula(noh->dir, divisao_por_zero);
			}
		}
		else {
			return *(int*)noh->info;
		}
	}
	return 0;
}

void imprime_exp(Arvexp* noh) {
	if (noh != NULL) {
		if (noh->operador) {
			printf("(");
			imprime_exp(noh->esq);
			printf(" %c ", *(char*)noh->info);
			imprime_exp(noh->dir);
			printf(")");
		}
		else {
			printf("%d", *(int*)noh->info);
		}
	}
}

Arvexp* libera_arv(Arvexp* noh) {
	if (noh != NULL) {
		libera_arv(noh->esq);
		libera_arv(noh->dir);
		free(noh->info);
		free(noh);
	}
	return NULL;
}