// Pilha com Lista
#include <stdio.h>
#include <stdlib.h>

// nó da lista para armazenar valores
typedef struct {
	float info;
	Lista* prox;
} Lista;

// estrutura da pilha
typedef struct {
	Lista* prim;
} Pilha;

Pilha* pilha_cria(void);
void pilha_push(Pilha*, float);
float pilha_pop(Pilha*);
int pilha_vazia(Pilha*);
void pilha_exibe(Pilha*);
void pilha_libera(Pilha*);

int main(void) {
	
	printf("Criacao de pilha com lista \n");
	Pilha* p = pilha_cria();
	
	printf("Insere e imprime elementos \n");
	pilha_push(p, 10);
	pilha_push(p, 1);
	pilha_push(p, 10);
	pilha_push(p, 10);
	pilha_push(p, 10);
}

/* Função para alocar a estrutura da pilha e inicializar a lista como vazia */
Pilha* pilha_cria(void) {
	Pilha* p = (Pilha*)malloc(sizeof(Pilha));
	p->prim = NULL;
	return p;
}

/* Função para inserir elemento no topo da pilha, no caso, no início da lista */
void pilha_push(Pilha* p, float v) {
	Lista* n = (Lista*)malloc(sizeof(Lista));
	n->info = v;
	n->prox	= p->prim;
	p->prim = n;
}

/* Função para retirar o elemento do topo da pilha, no caso, do início da lista */
float pilha_pop(Pilha* p) {
	Lista* t;
	float v;
	
	if (pilha_vazia(p)) {
		printf("Pilha vazia.\n");
		exit(1);
	}
	
	t = p->prim; // ponteiro para início da lista
	v = t->info; // valor do primeiro elemento da lista
	p->prim = t->prox; // ponteiro para início da lista
	free(t);
	
	return v;
}

/* Função para verificar se a pilha está vazia */
int pilha_vazia(Pilha* p) {
	return (p->prim==NULL);
}

/* Função para exibir o conteúdo da pilha */
void pilha_exibe(Pilha* p) {
	Lista* q;
	
	for (q=p->prim;q!=NULL;q=q->prox)
		printf("%f\n", q->info);
}

/* Função que libera a pilha deve liberar a lista primeiro */
void pilha_libera(Pilha* p) {
	Lista* q = p->prim;
	
	while (q != NULL) {
		Lista* t = q->prox;
		free(q);
		q = t;
	}
	
	free(p);
}
