#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
	int x;
	int y;
} Ponto;
int main() {
	srand(time(0));
	int i;
	Ponto *vet = (Ponto*) malloc(10*sizeof(Ponto));
	for(i=0;i<10;i++) {
		vet[i].x = rand()%100;
		vet[i].y = rand()%100;
		printf("[%d] %2d %2d\n",i,vet[i].x,vet[i].y);
	}
}
