typedef struct elemento Elemento;

typedef struct pilha Pilha;

Pilha* pilha_cria(void);

int pilha_vazia(Pilha* p);

void pilha_push(Pilha* p, void* info);

void* pilha_pop(Pilha* p);

void* pilha_iniInfo(Pilha* p);

void pilha_libera(Pilha* p);
