#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arv { 
    int info; 
    struct arv *f1, *f2, *f3;
}arv;

arv *cria_arvore( int ); 
arv *cria_no( ); 
void pos_insere (arv *, int ); 
int arv_vazia(arv* a);
void arv_imprime(arv* a);
void arv_imprime_sim(arv* a);
void arv_imprime_pos(arv* a);
void arv_libera(arv* a);
void pertence(arv *, int );
//int arv_altura(arv* );

arv* cria_arvore (int x) { 
  arv *p = (arv*) malloc(sizeof(arv)); 
  p->info = x;
  p->f1 = NULL;
  p->f2 = NULL;
  p->f3 = NULL;
  return p; 
}

void pos_insere(arv *p, int x) { 
  arv *q;
  q = cria_arvore(x); 

  if (p->f1 == NULL) {
  	p->f1 = q; 
  }
  else if (p->f2 == NULL) { 
    p->f2 = q; 
  } 
  else if (p->f3 == NULL) { 
    p->f3 = q; 
  }
} 
 

int arv_vazia(arv* a){
	return a == NULL;
}

void arv_imprime(arv* a){
	if (!arv_vazia(a)){
		printf("%d\t", a->info); /*imprime raiz*/
		arv_imprime(a->f1);
		arv_imprime(a->f2);
		arv_imprime(a->f3);
	}
}

void arv_libera(arv* a){
	if(!arv_vazia(a)){
		arv_libera(a->f1);
		arv_libera(a->f2);
		arv_libera(a->f3);
		free(a);
	}
}

void pertence(arv* a, int n){
	if(!arv_vazia(a)){
		if (a->info == n) {
			printf("\n%d pertence a arvore.\n", n);
		}
		else {
			pertence(a->f1, n);
			pertence(a->f2, n);
			pertence(a->f3, n);
		}
	}
}

//int arv_altura(arv* a) {
//	if (a == NULL) {
//		return -1;
//	}
//	else {
//		return (arv_altura(a->dir) >= arv_altura(a->esq) ? arv_altura(a->dir) : arv_altura(a->esq)) + 1;
//	}
//}
