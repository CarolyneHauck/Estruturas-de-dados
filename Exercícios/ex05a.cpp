#include <stdio.h>
#include <stdlib.h>
int main() {
	int *p = (int*) malloc(sizeof(int));
	printf("Inteiro: ");
	scanf("%d",p);
	printf("%d %d %d", &p, p, *p);
	
	float *q = (float*) malloc(sizeof(float));
	printf("\nFloat: ");
	scanf("%f",q);
	printf("%d %d %.1f", &q, q, *q);
}
