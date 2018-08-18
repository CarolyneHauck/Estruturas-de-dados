#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv_n.h"

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
 		q = p->f1;               /* passa para arvore esquerda */ 
      else 
		q = p->f2;               /* passa para direita */ 
    } 
    if (num == p->info) 
      printf("O numero %d ja existe na arvore.\n", num); 
    else {  /* vou inserir o numero na arvore */ 
		 pos_insere(p, num); 
    } 
    numero = strtok(NULL, " "); 
  } /* fim do while (numero) */ 

  /* imprime o conjunto de nos da arvore */
  printf("Pre-ordem: \n");
  arv_imprime(raiz);
  printf("\n\n");
  
  printf("Informe um valor: \n");
  scanf("%d", &n);
  
  pertence(raiz, n);
  
  arv_libera(raiz);
}
