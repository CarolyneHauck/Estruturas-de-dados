#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
	srand(time(0));
	char **mat;
	int i, j, m=3, n=4;
	mat = (char**) malloc(m*sizeof(char*));
	for(i=0;i<m;i++)
		mat[i] = (char*) malloc(n*sizeof(char));
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
		free(mat[i]);
	free(mat);
}
