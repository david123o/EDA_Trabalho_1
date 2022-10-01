/*
EDA - Trabalho 1 - 02/10/2022

David Castro - 110339
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "arvore.h"

char* duplica(char* linha) {
	int len = strlen(linha);
	char* d = (char*)malloc(len + 1 * sizeof(char));
	if (d == NULL) {
		printf("Falha na alocação de memória.\n");
		exit(1);
	}
	strcpy(d, linha);
	return d;
}

char* le_expressao(void) {
	char linha[101];
	printf("Entre com a expressão a ser calculada:\n");
	scanf("%100[^\n]", linha);
	return duplica(linha);
}

int eh_numero(char c) {	//verifica se o caractere é um número 
	if (c >= '0' && c <= '9') {
		return 1;
	}
	else {
		return 0;
	}
}

int eh_operador(char c) {	// verifica se o caractere é um operador
	if (c == '+' || c == '-' || c == '*' || c == '/') {
		return 1;
	}
	else {
		return 0;
	}
}

int precedencia(char operador) {	//retorna a precedência do operador em relação ao demais
	if (operador == '+' || operador == '-') {
		return 1;
	}
	if (operador == '*' || operador == '/') {
		return 2;
	}
	else {
		return 0;
	}
}

char* infix_to_postfix(char* infix) {
	int i, j;
	char saida[100];
	char* op;
	Pilha* p = pilha_cria(); //pilha de operadores
	for (i = 0, j = 0; infix[i] != '\0'; i++) {
		if (eh_operador(infix[i])) {
			saida[j] = ' '; //adiciona um espaço entre os elementos inseridos no buffer de saída (para tratar númers de múltiplos dígitos)
			j++;
			while (!pilha_vazia(p) && precedencia(infix[i]) <= precedencia(*(char*)pilha_iniInfo(p))) { //percorre a pilha enquanto a precedência do operador lido é menor ou igual à do operador que está no topo da pilha
				op = (char*)pilha_pop(p); //remove o operador ocupante do topo da pilha
				saida[j] = *op;	//insere o operador removido no buffer de saída
				free(op);
				j++;
				saida[j] = ' ';
				j++;
			}
			char* aux = (char*)malloc(sizeof(char));	//aloca espaço de memória para o caractere que será inserido na pilha
			*aux = infix[i];
			pilha_push(p, aux);	//insere o operador lido no topo da pilha
		}
		else if (infix[i] == '(') {
			char* aux = (char*)malloc(sizeof(char));
			*aux = infix[i];
			pilha_push(p, aux);	//insere o operador lido no topo da pilha
		}
		else if (infix[i] == ')') {
			while (!pilha_vazia(p) && *(char*)pilha_iniInfo(p) != '(') {	//percorre a pilha até que o elemento do topo seja um parêntese esquerdo
				saida[j] = ' ';
				j++;
				op = (char*)pilha_pop(p);
				saida[j] = *op;
				free(op);
				j++;
			}
			op = pilha_pop(p);	//remove o parêntese esquerdo
			free(op);
		}
		else if (eh_numero(infix[i])) {
			saida[j] = infix[i];
			j++;
		}
	}
	while (!pilha_vazia(p)) {	//insere os operadores que restaram na pilha do buffer de saída
		saida[j] = ' ';
		j++;
		op = (char*)pilha_pop(p);
		saida[j] = *op;
		free(op);
		j++;
	}
	saida[j] = '\0';	//adiciona o caractere vazio ao final do buffer de saída
	pilha_libera(p);
	return duplica(saida);
}

Arvexp* postfix_to_arvexp(char* postfix) {
	int i, len = strlen(postfix), leu_num = 0, num;
	char* aux_c = (char*)malloc(sizeof(char));	//aloca um espaço de memória para o operador a ser inserido na raíz da árvore
	*aux_c = postfix[len - 1];
	Arvexp* raiz = cria_noh(aux_c, cria_vazia(), 1);
	Arvexp* corrente = raiz;	//faz o ponteiro para o nó corrente apontar para a raíz
	for (i = len - 2; i >= -1; i--) {
		if (eh_numero(postfix[i])) {
			if (!leu_num) {		//caso seja o primeiro ou o único dígito lido do número
				num = postfix[i] - '0';	//converte o dígito de char para int
			}
			else {
				num = num + 10 * (postfix[i] - '0'); //converte o dígito de char para int e calcula o valor do número levando em consideração o dígito anteriormente lido
			}
			leu_num = 1; //indica que um número foi lido
		}
		else if (eh_operador(postfix[i])) {
			aux_c = (char*)malloc(sizeof(char));	//aloca um espaço de memória para o operador a ser inserido no novo nó
			*aux_c = postfix[i];
			Arvexp* novo = cria_noh(aux_c, cria_vazia(), 1);	//cria um novo nó que será anexado ao nó corrente
			anexa(corrente, novo);		//anexa o novo nó criado ao nó corrente
			corrente = novo;	//faz o corrente apontar para o novo
			leu_num = 0;
		}
		else if (leu_num) {		//caso tenha lido um número antes de ler o separador
			int* aux_n = (int*)malloc(sizeof(int));		//aloca um espaço de memória para o número a ser inserido no novo nó
			*aux_n = num;
			Arvexp* novo = cria_noh(aux_n, cria_vazia(), 0);	//cria um novo nó que será anexado ao nó corrente
			anexa(corrente, novo);
			leu_num = 0;	//indica que um número não foi lido
		}
	}
	return raiz;
}

int main(void) {
	char* infix = le_expressao();
	char* postfix;
	Arvexp* arv = cria_vazia();
	int resultado, divisao_por_zero = 0;

	postfix = infix_to_postfix(infix);
	free(infix);
	//printf("%s\n", postfix);

	arv = postfix_to_arvexp(postfix);
	free(postfix);
	imprime_exp(arv);
	resultado = calcula(arv, &divisao_por_zero);
	if (!divisao_por_zero) {
		printf(" = %d\n", resultado);
	}
	else {
		printf(" = erro\nNão é possível fazer a divisão por 0.\n");
	}
	arv = libera_arv(arv);

	return 0;
}