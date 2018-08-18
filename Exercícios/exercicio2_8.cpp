// Exercício 2.8
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct lista {
	int info;
	struct lista* prox;
} Lista;

Lista* lst_cria(void);
Lista* lst_insere(Lista*, int);
void lst_exibe(Lista*);
Lista* lst_retira(Lista*, int);

int main() {
	
	srand(time(0));
	int i, j, n;
	Lista* lst = lst_cria();
	
	for (i=0; i<10; i++) {
		j = rand()%100;
		lst = lst_insere(lst, j);
	}
	
	lst_exibe(lst);
	
	printf("\nDigite um elemento para excluir: ");
	scanf("%d", &n);
	
	while (n >= 0 && n <= 99) {
		
		lst = lst_retira(lst, n);
		printf("\n");
		
		lst_exibe(lst);
		
		printf("\nDigite mais um elemento para excluir: ");
		scanf("%d", &n);
	}
	
	printf("\nLista Final:\n");
	lst_exibe(lst);
	return 0;
}

Lista* lst_cria(void) {
	return NULL;
}

Lista* lst_insere(Lista* lst, int i) {
	Lista* novo = (Lista*)malloc(sizeof(Lista));
	novo->info = i;
	novo->prox = lst;
	return novo;
}

void lst_exibe(Lista* lst) {
	Lista* aux;
	for(aux=lst;aux!=NULL;aux=aux->prox)
		printf("Info: %2d\n",aux->info);
}

Lista* lst_retira(Lista* lst, int v) {
	Lista* ant = NULL; /* ponteiro para elemento anterior */
	Lista* p = lst; /* ponteiro para percorrer a lista */
	
	/* Procura elemento na lista, guardando anterior */
	while(p!=NULL && p->info!=v) {
		ant = p;
		p = p->prox;
	}
	
	/* Verifica se encontrou o elemento */
	if(p==NULL)
		return lst; /* Retorna lista original (n~ao achou) */
		
	/* Retira elemento */
	if(ant==NULL) {
		/* O elemento ´e o primeiro da lista */
		lst = p->prox;
	} else {
		/* O elemento n~ao ´e o primeiro da lista */
		ant->prox = p->prox;
	}
	
	free(p);
	return lst;
}
