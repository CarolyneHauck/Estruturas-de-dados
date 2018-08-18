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
void concatena_pilhas(Pilha* p1, Pilha* p2);

int main(){
	Pilha* p1 = pilha_cria();
	Pilha* p2 = pilha_cria();
	printf("Insere e imprime elementos na pilha 1:\n");
	pilha_push(p1, 1);	
	pilha_push(p1, 10);	
	pilha_push(p1, 20);	
	pilha_push(p1, 30);	
	pilha_imprime(p1);
	printf("Insere e imprime elementos na pilha 2:\n");
	pilha_push(p2, 5);	
	pilha_push(p2, 15);	
	pilha_push(p2, 25);	
	pilha_push(p2, 35);	
	pilha_imprime(p2);
	printf("Insere todos na pilha 1:\n");
	concatena_pilhas(p1,p2);
//	pilha_imprime(p1);
}

/*int main(void){
	
	printf("Criação de pilha com lista \n");

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
} */

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
/* versão com vetor */
/*	int i;
	for(i=p->n-1; i>=0; i--)
		printf("%f \n", p->vet[i]);
*/

/* versao com lista*/ 
	Lista* q;
	for(q=p->prim;q!=NULL;q=q->prox)
		printf("%f\n",q->info);
	


}

void concatena_pilhas(Pilha* p1, Pilha* p2){
	float valor;
	while(p2->prim!=NULL){
		valor =  pilha_pop(p2); 
		pilha_push(p1, valor);		
	}
	pilha_imprime(p1);
}


