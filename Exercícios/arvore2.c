/* Programa que recebe um conjunto de nos e *
 * monta uma arvore binaria                 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv.h"

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
