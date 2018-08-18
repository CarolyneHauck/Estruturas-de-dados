// Exemplo 2.3
#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
	int info;
	struct lista* prox;
} Lista;

Lista* lst_cria(void);
Lista* lst_insere(Lista*, int);
void lst_exibe(Lista*);
Lista* lst_retira(Lista*, int);

int main() {
	Lista* lst; /* Declara uma lista */
	lst = lst_cria();
	lst = lst_insere(lst,23);
	lst = lst_insere(lst,36);
	lst = lst_insere(lst,45);
	printf("Lista:\n");
	lst_exibe(lst);
	lst = lst_retira(lst,36);
	printf("\nLista:\n");
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
