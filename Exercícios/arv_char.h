#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arv { 
    char info; 
    struct arv *esq, *dir; 
}arv;

arv *cria_arvore( char ); 
arv *cria_no( ); 
void pos_esq (arv *, char ); 
void pos_dir (arv *, char );
int arv_vazia(arv* a);
void arv_imprime(arv* a);
void arv_imprime_sim(arv* a);
void arv_imprime_pos(arv* a);
void arv_libera(arv* a);
void pertence(arv *, char );

arv* cria_arvore (char x) { 
  arv *p = (arv*) malloc(sizeof(arv)); 
  p->info = x;
  p->esq = NULL;
  p->dir = NULL;
  return p; 
}
 

void pos_esq(arv *p, char x) { 
  arv *q;

  if (p->esq) 
    puts("Operacao de insercao a esquerda ilegal."); 
  else { 
    q = cria_arvore(x); 
    p->esq = q; 
  } 
} 
 

void pos_dir(arv *p, char x) { 
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
		printf("%c\t", a->info); /*imprime raiz*/
		arv_imprime(a->esq);     /*imprime arvore esquerda*/
		arv_imprime(a->dir);     /*imprime arvore direita */
	}
}

void arv_imprime_sim(arv* a){
	if (!arv_vazia(a)){
		arv_imprime(a->esq);     /*imprime arvore esquerda*/
		printf("%c\t", a->info); /*imprime raiz*/
		arv_imprime(a->dir);     /*imprime arvore direita */
	}
}

void arv_imprime_pos(arv* a){
	if (!arv_vazia(a)){
		arv_imprime(a->esq);     /*imprime arvore esquerda*/
		arv_imprime(a->dir);     /*imprime arvore direita */
		printf("%c\t", a->info); /*imprime raiz*/
	}
}

void arv_libera(arv* a){
	if(!arv_vazia(a)){
		arv_libera(a->esq);
		arv_libera(a->dir);
		free(a);
	}
}

void pertence(arv* a, char n){
	if(!arv_vazia(a)){
		if (a->info == n) {
			printf("\n%c pertence a arvore.\n", n);
		}
		else {
			pertence(a->esq, n);
			pertence(a->dir, n);
		}
	}
}
