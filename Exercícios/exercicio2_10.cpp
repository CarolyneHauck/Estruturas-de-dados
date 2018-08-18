// Exercício 2.10
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
Lista* lst_retira(Lista*);

int main(void) {
	
	srand(time(0));
	int i, num;
    Lista* lst = lst_cria();
    Lista* p = lst_cria();
    
    for(i=0;i<10;i++)
    	lst = lst_insere(lst,rand()%100);
    	
    printf("Lista inicial:\n");
    lst_exibe(lst);
    
    for(i=0;i<9;i++) {
		lst = lst_retira(lst);
	    printf("\n\nLista com %d:\n", 9-i);
	    lst_exibe(lst);
	}   
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

Lista* lst_retira(Lista* lst) {
    Lista* ant = NULL;
    Lista* del = NULL;
    Lista* p = lst;
    
    while (p != NULL) {
    	ant = del;
        del = p;
        p = p->prox;
    }
    
    ant->prox = NULL;
    free(del);
    return lst;
}
