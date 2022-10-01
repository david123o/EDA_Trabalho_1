typedef struct arvexp Arvexp;

Arvexp* cria_vazia(void);

int arv_vazia(Arvexp* noh);

Arvexp* cria_noh(void* info, Arvexp* pai, int operador);

void anexa(Arvexp* noh, Arvexp* filho);

int calcula(Arvexp* noh, int* divisao_por_zero);

void imprime_exp(Arvexp* noh);

Arvexp* libera_arv(Arvexp* noh);