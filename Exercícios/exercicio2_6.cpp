// Exercício 2.6
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct lista {
	int info;
	struct lista* prox;
} Lista;

Lista* lst_cria(void);
Lista* lst_insere(Lista*, int);
int lst_vazia(Lista* lst);
void lst_exibe(Lista*);
Lista* lst_impares(Lista*);
Lista* lst_pares(Lista*);

int main(void) {
	
	srand(time(0));
	int i, j;
	Lista* lst = lst_cria();
	Lista* lstImpar;
	Lista* lstPar;
	
	for (i=0; i<10; i++) {
		j = rand()%100;
		lst = lst_insere(lst, j);
	}
	
	printf("Lista padrao:\n");
	lst_exibe(lst);
	
	printf("\n\nImpares:\n");
	lstImpar = lst_impares(lst);
	lst_exibe(lstImpar);
	
	printf("\n\nPares:\n");
	lstPar = lst_pares(lst);
	lst_exibe(lstPar);
	
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

int lst_vazia(Lista* lst) {
	if (lst==NULL)
		return 1;
	else
		return 0;
}

void lst_exibe(Lista* lst) {
	Lista* aux;
	for(aux=lst;aux!=NULL;aux=aux->prox)
		printf("Info: %2d\n",aux->info);
}

Lista* lst_impares(Lista* lst) {
	Lista* p;
	Lista* lstImpar = lst_cria();
	for(p=lst; p!=NULL; p=p->prox)
		if (p->info%2 == 1)
			lstImpar = lst_insere(lstImpar, p->info);
			
	return lstImpar;
}

Lista* lst_pares(Lista* lst) {
	Lista* p;
	Lista* lstPar = lst_cria();
	for(p=lst; p!=NULL; p=p->prox)
		if (p->info%2 == 0)
			lstPar = lst_insere(lstPar, p->info);
			
	return lstPar;
}
