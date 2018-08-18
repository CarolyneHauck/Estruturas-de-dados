/*Lista duplamente encadeada*/

#include <stdio.h>
#include <stdlib.h>

struct lista2{
	int info;
	struct lista2* ant;
	struct lista2* prox;
};
typedef struct lista2 Lista2;

/*Inserção no inicio*/
Lista2* lst2_insere(Lista2** l, int v){
	Lista2* novo = (Lista2*) malloc (sizeof(Lista2));
	novo->info = v;
	novo->prox = (*l);
	novo->ant = NULL;
	if((*l) != NULL)
		(*l)->ant = novo;
	return novo;
}

/*Busca um elemento na lista*/
Lista2* lst2_busca(Lista2* l, int v){
	Lista2* p;
	for(p = l; p != NULL; p=p->prox)
		if(p->info == v)
			return p;
	return NULL;
}

/*Retira elemento da lista*/
Lista2* lst2_retira(Lista2* l , int v){
	Lista2* p = lst2_busca(l,v);

	if(p==NULL)
		return l; /*nao achou, retorna lista*/

	if(l == p)
		l = p->prox;
	else
		p->ant->prox = p->prox;

	if(p->prox != NULL)
		p->prox->ant = p->ant;

	free(p);

	return l;

}

void lst2_imprime(Lista2* l) {
	Lista2* p;
	printf("Lista -> ");
	for (p=l; p != NULL; p = p->prox)
		printf("%d\t", p->info);
	printf("\n");
}

void lst2_leiaLista(Lista2** l) {
	int i, n, val;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d", &val);
		lst2_insere((*l), val);
	}
}

int main() {
	Lista2* l2 = NULL;
	
	lst2_leiaLista(&l2);
	lst2_imprime(l2);
	
	return 0;
}
