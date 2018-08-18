/* Matrizes dinâmicas: a linguagem C só permite
   alocar dinamicamente conjuntos unidimensio-
   nais. Uma estratégia consiste em representar
   a matriz por um vetor 
   (desenho do quadro) 
   onde n representa a qtde de elementos na li-
   nha. Nessa abordagem, a alocação da matriz
   por vetor requer um espaço de mxn elementos:
   char *mat;
   mat = (char*)malloc(m*n*sizeof(char)); */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
	srand(time(0));
	char *mat;
	int i, j, m=3, n=4;
	mat = (char*) malloc(m*n*sizeof(char));
	for(i=0;i<m;i++) {
		for(j=0;j<n;j++) {
			*(mat+i*n+j) = rand()%26+65;
			printf("%c ",*(mat+i*n+j));
		}
	}
	free(mat);
}
