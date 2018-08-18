/* Programa que recebe um conjunto de nos e *
 * monta uma arvore binaria                 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv_char.h"

void main() { 
  arv *raiz, *p, *q; 
  char linha[80], *caracter; 
  char c, n;

  scanf("\%[0-9 ]",linha);

  caracter = strtok(linha, " "); /* pega o primeiro char da lista */ 
  raiz = cria_arvore(c); /* insere na raiz */ 
  caracter = strtok(NULL, " "); 

  while (caracter) { 
    q = raiz; p = raiz; 
    printf("Li char %c\n", c); /* le novo char */ 
    while (c != p->info && q) { /* procura na arvore */ 
      p = q; 
      if (c < p->info) 
 		q = p->esq;               /* passa para arvore esquerda */ 
      else 
		q = p->dir;               /* passa para direita */ 
    } 
    if (c == p->info) 
      printf("O char %c ja existe na arvore.\n", c); 
    else {  /* vou inserir o char na arvore */ 
      if (c < p->info) 
		 pos_esq(p, c); 
      else 
		 pos_dir(p, c); 
    } 
    caracter = strtok(NULL, " "); 
  } /* fim do while (caracter) */ 

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
  scanf("%c", &n);
  
  pertence(raiz, n);

  arv_libera(raiz);
}
