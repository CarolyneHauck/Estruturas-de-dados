#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
	srand(time(0));
	int i;
	float *vet;
	vet = (float*) malloc(10*sizeof(float));
	for(i=0;i<10;i++) {
		*(vet+i) = rand()%10/10.;
		printf("%3.1f ",*(vet+i));
	}
}
