// Exercício 2.4
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
void lst_busca(Lista*, int);

int main(void) {
	
	srand(time(0));
	int i, j, n;
	Lista* lst = lst_cria();
	
	for (i=0; i<10; i++) {
		j = rand()%100;
		lst = lst_insere(lst, j);
	}
	
	lst_exibe(lst);
	
	printf("Digite um valor n[0 99]: ");
	scanf("%d", &n);
	
	lst_busca(lst, n);
	
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

void lst_busca(Lista* lst, int v) {
	Lista* p;
	for(p=lst; p!=NULL; p=p->prox)
		if (p->info > v)
			printf("%2d ", p->info);
}
