// Exemplo 2.1
#include <stdio.h>
#include <stdlib.h>
typedef struct lista {
	int info;
	struct lista* prox;
} Lista;

Lista* lst_cria(void);
Lista* lst_insere(Lista*,int);
void lst_exibe(Lista*);

int main(void) {
	Lista* lst = lst_cria();
	lst = lst_insere(lst, 23);
	lst = lst_insere(lst, 45);
	lst_exibe(lst);
	return 0;
}

/* Função de criação: cria uma lista vazia */
Lista* lst_cria(void) {
	return NULL;
}

/* Função de inserção no início da lista */
Lista* lst_insere(Lista* lst, int i) {
	Lista* novo = (Lista*)malloc(sizeof(Lista));
	novo->info = i;
	novo->prox = lst;
	return novo;
}

/* Função de exibição da lista */
void lst_exibe(Lista* lst) {
	Lista* aux;  // variável auxiliar
	for(aux=lst;aux!=NULL;aux=aux->prox)
		printf("Info = %d\n",aux->info);
}
