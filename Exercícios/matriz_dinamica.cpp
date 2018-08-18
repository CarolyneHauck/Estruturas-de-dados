#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
	
	srand(time(0));
	int i;
	int j;
	int m;
	int n;
	
	char *mat;
	
	scanf("%d %d", &m, &n);
	
	mat = (char*) malloc(m*n*sizeof(char));
	
	for(i=0; i<m; i++) {
		for(j=0; j<n; j++) {
		
			int k = i*n+j;
			mat[k] = rand()%26+65;
			printf("%c ", mat[k]);
		}
	}
	
	free(mat);
}
