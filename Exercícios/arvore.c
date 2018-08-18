/* Programa que recebe um conjunto de nos e *
 * monta uma arvore binaria                 */

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

void main() { 
  arv *raiz, *p, *q; 
  char linha[80], *numero; 
  int num, n;

  scanf("\%[0-9 ]",linha); 

  numero = strtok(linha, " "); /* pega o primeiro numero da lista */ 
  num = atoi(numero); 
  raiz = cria_arvore(num); /* insere na raiz */ 
  numero = strtok(NULL, " "); 

  while (numero) { 
    q = raiz; p = raiz; 
    printf("Li numero %d\n", num); /* le novo numero */ 
    num = atoi(numero); 
    while (num != p->info && q) { /* procura na arvore */ 
      p = q; 
      if (num < p->info) 
 		q = p->esq;               /* passa para arvore esquerda */ 
      else 
		q = p->dir;               /* passa para direita */ 
    } 
    if (num == p->info) 
      printf("O numero %d ja existe na arvore.\n", num); 
    else {  /* vou inserir o numero na arvore */ 
      if (num < p->info) 
		 pos_esq(p, num); 
      else 
		 pos_dir(p, num); 
    } 
    numero = strtok(NULL, " "); 
  } /* fim do while (numero) */ 

  /* imprime o conjunto de nos da arvore */
  printf("Pre-ordem: \n");
  arv_imprime(raiz);
  printf("\n\n");
  
  printf("Simetrica: \n");
  arv_imprime_sim(raiz);
  printf("\n\n");
  
  printf("Pos-ordem: \n");
  arv_imprime_pos(raiz);
  printf("\n\n");
  
  printf("Informe um valor: \n");
  scanf("%d", &n);
  
  pertence(raiz, n);

  arv_libera(raiz);
}

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
