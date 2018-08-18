#include <stdio.h>
#include <stdlib.h>

typedef struct ponto {
	
	int x;
	int y;
	
} Ponto;

int main() {
	
	// Bytes
	printf("sizeof(char)  = %d\n", sizeof(char));
	printf("sizeof(int)   = %d\n", sizeof(int));
	printf("sizeof(float) = %d\n", sizeof(float));
	printf("sizeof(Ponto) = %d\n\n", sizeof(Ponto));
	
	int i = 1;
	int a = 2;
	int b = 3;
	int c;
	
	// Exibindo conteúdo e endereço da variável i
	printf("%d: %d\n\n", &i, i);
	
	// Ponteiros do tipo inteiro
	int *p;
	int *q;
	
	// p aponta para o endereço de a
	p = &a;
	// q aponta para o endereço de b
	q = &b;
	
	// c = a + b
	c = *p + *q;
	
	printf("c = %d \n\n", c);
	
	// declara um ponteiro de ponteiro de int
	int **r;
	
	// r aponta para o endereço de p
	r = &p;
	
	// **r = a
	c = **r + b;
	
	printf("c = %d \n\n", c);
	
	int *vet;
	
	// vet aponta para o primeiro elemento
	vet = (int*) malloc(100 * sizeof(int));
	
	// vet aponta para o i-ésimo elemento
	vet[i] = 87; // equivale a *(vet + i) = 87
	
	printf("%d", vet);
	
}
