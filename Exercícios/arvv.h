#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3
struct arv3 {
	char info;
	struct arv3 *f[N];
}

struct arvvar {
	char info;
	struct arvvar *prim;
	struct arvvar *prox;
};
typedef struct arvvar ArvVar;

// void arv3_imprime (Arv3*);

// Cria um nó folha, dada a informação a ser armazenada
ArvVar* arvv_cria (char);
// Insere uma nova subárvore como filha de um dado nó
void arvv_insere (ArvVar*, ArvVar*);
// Percorre todos os nós e imprime suas informações
void arvv_imprime (ArvVar*);
// Verifica a ocorrência de uma dada informação na árvore
int arvv_pertence (ArvVar*, char);
// Libera toda a memória alocada pela árvore
void arvv_libera (ArvVar*);
// Retorna a altura da árvore
int arvv_altura (ArvVar*);
// Retorna a quantidade de folhas de uma árvore
int folhas (ArvVar*);
// Compara se duas árvores são iguais
int igual (ArvVar*, ArvVar*);

//void arv3_imprime (Arv3* a){
//	if (a != NULL){
//		int i;
//		printf(“<%c”, a->info);
//		for (i=0l i<N; i++)
//			arv3_imprime (a->f[i]);
//		printf(“>”);
//	}
//}

ArvVar* arvv_cria (char c) {
	ArvVar *a =(ArvVar *) malloc(sizeof(ArvVar));
	a->info = c;
	a->prim = NULL;
	a->prox = NULL;
	return a;
}

void arvv_insere (ArvVar* a, ArvVar* sa) {
	sa->prox = a->prim;
	a->prim = sa;
}

void arvv_imprime (ArvVar* a){
	ArvVar* p;
	printf("<%c\n",a->info);
	for (p=a->prim; p!=NULL; p=p->prox)
		arvv_imprime(p); /* imprime filhas */
	printf(">");
}

int arvv_pertence (ArvVar* a, char c) {
	ArvVar* p;
	if (a->info==c)
		return 1;
	else {
		for (p=a->prim; p!=NULL; p=p->prox) {
			if (arvv_pertence(p, c))
				return 1;
		}
	}
	return 0;
}

void arvv_libera (ArvVar* a) {
	ArvVar* p = a->prim;
	while (p!=NULL) {
		ArvVar* t = p->prox;
		arvv_libera(p);
		p = t;
	}
	free(a);
}

int arvv_altura (ArvVar* a) {
	int hmax = -1; /* -1 para arv. sem filhos */
	ArvVar* p;
	for (p=a->prim; p!=NULL; p=p->prox) {
		int h = arvv_altura(p);
		if (h > hmax)
			hmax = h;
	}
	return hmax + 1;
}

int folhas (ArvVar* a) {
	ArvVar* p;
	int n = 0;
	if (a->prim == NULL)
		return 1;
	for (p=a->prim; p!=NULL; p=p->prox) {
		n = n + folhas(p);
	}
	return n;
}

int igual (ArvVar* a, ArvVar* b) {
	ArvVar* p;
	ArvVar* q;
	if (a == NULL && b == NULL)
		return 1;
	for (p=a->prim, q=b->prim; p!=NULL && q!=NULL;p=p->prox, q=q->prox) {
		if (!igual(p,q))
		return 0;
	};
	return 1;
}