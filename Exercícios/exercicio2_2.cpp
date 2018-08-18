// Exercício 2.2
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct lista {
	float info;
	struct lista* prox;
} Lista;

Lista* lst_cria(void);
Lista* lst_insere(Lista*,float);
void lst_exibe(Lista*);

int main(void) {
	srand(time(0));
	int i;
	float j;
	Lista* lst = lst_cria();
	for(i=0;i<10;i++) {
		j = rand()%100/10.;
		lst = lst_insere(lst, j);
	}
	lst_exibe(lst);
}

/* Função de criação: cria uma lista vazia */
Lista* lst_cria(void) {
	return NULL;
}

/* Função de inserção no início da lista */
Lista* lst_insere(Lista* lst, float i) {
	Lista* novo = (Lista*)malloc(sizeof(Lista));
	novo->info = i;
	novo->prox = lst;
	return novo;
}

/* Função de exibição da lista */
void lst_exibe(Lista* lst) {
	Lista* aux;  // variável auxiliar
	for(aux=lst;aux!=NULL;aux=aux->prox)
		printf("%.1f  ",aux->info);
}
