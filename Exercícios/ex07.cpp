#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
	srand(time(0));
	int i;
	char *vet;
	vet = (char*) malloc(10*sizeof(char));
	for(i=0;i<10;i++) {
		//*(vet+i) = rand()%26+65;
		vet[i] = rand()%26+65;
		printf("%c ",*(vet+i));
	}
}
