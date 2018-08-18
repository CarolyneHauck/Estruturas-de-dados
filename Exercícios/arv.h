#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arv { 
    int info; 
    struct arv *esq, *dir; 
}arv;

arv *cria_arvore( int ); 
arv *cria_no( ); 
void pos_esq (arv *, int ); 
void pos_dir (arv *, int );
int arv_vazia(arv* a);
void arv_imprime(arv* a);
void arv_imprime_sim(arv* a);
void arv_imprime_pos(arv* a);
void arv_libera(arv* a);
void pertence(arv *, int );
int arv_altura(arv* );

arv* cria_arvore (int x) { 
  arv *p = (arv*) malloc(sizeof(arv)); 
  p->info = x;
  p->esq = NULL;
  p->dir = NULL;
  return p; 
}
 

void pos_esq(arv *p, int x) { 
  arv *q;

  if (p->esq) 
    puts("Operacao de insercao a esquerda ilegal."); 
  else { 
    q = cria_arvore(x); 
    p->esq = q; 
  } 
} 
 

void pos_dir(arv *p, int x) { 
  arv *q;

  if (p->dir) 
    puts("Operacao de insercao a direita ilegal."); 
  else { 
    q = cria_arvore(x); 
    p->dir = q; 
  } 
} 

int arv_vazia(arv* a){
	return a == NULL;
}

void arv_imprime(arv* a){
	if (!arv_vazia(a)){
		printf("%d\t", a->info); /*imprime raiz*/
		arv_imprime(a->esq);     /*imprime arvore esquerda*/
		arv_imprime(a->dir);     /*imprime arvore direita */
	}
}

void arv_imprime_sim(arv* a){
	if (!arv_vazia(a)){
		arv_imprime(a->esq);     /*imprime arvore esquerda*/
		printf("%d\t", a->info); /*imprime raiz*/
		arv_imprime(a->dir);     /*imprime arvore direita */
	}
}

void arv_imprime_pos(arv* a){
	if (!arv_vazia(a)){
		arv_imprime(a->esq);     /*imprime arvore esquerda*/
		arv_imprime(a->dir);     /*imprime arvore direita */
		printf("%d\t", a->info); /*imprime raiz*/
	}
}

void arv_libera(arv* a){
	if(!arv_vazia(a)){
		arv_libera(a->esq);
		arv_libera(a->dir);
		free(a);
	}
}

void pertence(arv* a, int n){
	if(!arv_vazia(a)){
		if (a->info == n) {
			printf("\n%d pertence a arvore.\n", n);
		}
		else {
			pertence(a->esq, n);
			pertence(a->dir, n);
		}
	}
}

int arv_altura(arv* a) {
	if (a == NULL) {
		return -1;
	}
	else {
		return (arv_altura(a->dir) >= arv_altura(a->esq) ? arv_altura(a->dir) : arv_altura(a->esq)) + 1;
	}
}
