/*  Matriz representada por vetor de ponteiros: cada
	linha é representada por um vetor independente. A
	matriz é, então, um vetor de ponteiros, onde cada
	elemento armazena o endereço do primeiro elemento
	de cada linha.
	Deve-se primeiro alocar o vetor de ponteiros. Depois,
	alocar os vetores das linhas. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
	srand(time(0));
	char **mat; // vetor de ponteiros
	int i, j, m=3, n=4;
	// aloca memória para o vetor de ponteiros:
	mat = (char**) malloc(m*sizeof(char*));
	for(i=0;i<m;i++)
		*(mat+i) = (char*) malloc(n*sizeof(char));
	// preenchimento igual matriz dinâmica:
	for(i=0;i<m;i++) {
		for(j=0;j<n;j++) {
			mat[i][j] = rand()%26+65;
			printf("%c ",mat[i][j]);
		}
		printf("\n");
	}
	// liberar memória:
	for(i=0;i<m;i++)
		free(*(mat+i)); // libera os 3 vetores linha
	free(mat); // libera o vetor coluna (de ponteiros)
}
