#include <stdio.h>
#include <stdlib.h>


// noh da lista para armazenar valores
struct lista{
	float info;
	struct lista* prox;
};
typedef struct lista Lista;

// estrutura da pilha
struct pilha{
	Lista* prim;
};
typedef struct pilha Pilha;


Pilha* pilha_cria (void);
void pilha_imprime(Pilha* p);
void pilha_push(Pilha* p, float v);
int pilha_vazia (Pilha* p);
float pilha_pop(Pilha* p);
void pilha_libera(Pilha* p);

int main(void){
	
	printf("Criacao de pilha com lista \n");

	Pilha* p = pilha_cria();

	printf("Insere e imprime elementos \n");

	pilha_push(p, 10);	
	pilha_push(p, 1);	
	pilha_push(p, 20);	
	pilha_push(p, 2);	

	pilha_imprime(p);

	printf("Remove e imprime elementos \n");

	pilha_pop(p);
	pilha_pop(p);
	pilha_imprime(p);

	pilha_libera(p);

	return 0;
}

// funcao para alocar estrutura da pilha e inicializar
// a lista como vazia
Pilha* pilha_cria (void){
	Pilha* p = (Pilha*) malloc(sizeof(Pilha));
	p->prim = NULL;
	return p;
}

// funcao para inserir elemento no topo da pilha
// no caso, no inicio da lista
void pilha_push(Pilha* p, float v){
	Lista* n = (Lista*) malloc(sizeof(Lista));
	n->info = v;
	n->prox = p->prim;
	p->prim = n;
}

// funcao para testar se a pilha esta vazia
// a pilha esta vazia se a lista esta vazia
int pilha_vazia (Pilha* p){
	return(p->prim==NULL);
}

// funcao para retirar elemento do topo da pilha
// no caso, do inicio da lista
float pilha_pop(Pilha* p){
	Lista* t;
	float v;
	if (pilha_vazia(p)){
		printf("pilha vazia.\n");
		exit(1);
	}
	t = p->prim; // ponteiro para inicio da lista
	v = t->info; // valor do primeiro elemento da lista
	p->prim = t->prox; // ponteiro para inicio da lista passa a ser o proximo elemento
	free(t);
	return v;
}

// funcao que libera a pilha deve liberar a lista primeiro
void pilha_libera(Pilha* p){
	Lista* q = p->prim;
	while (q!=NULL){
		Lista* t = q->prox;
		free(q);
		q = t;
	}
	free(p);
}

// funcao para imprimir a pilha
void pilha_imprime(Pilha* p){
	Lista* q;
	for(q=p->prim;q!=NULL;q=q->prox)
		printf("%f\n",q->info);
	


}


