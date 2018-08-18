#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	
	srand(time(0));
	
	int i;
	int *vet;
	
	vet = (int*) malloc(10 * sizeof(int));
	
	for (i = 0; i < 10; i++) {
		
		*(vet + i) = rand() % 100;
		printf("%02d ", *(vet + i));
		
	}
	
}
