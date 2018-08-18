#include <stdio.h>
int main() {
	int a = 2, b = 3, c;
	int *p = NULL; // declara um ponteiro de int 
	int **r; // declara pointer de pointer de int
	p = &a; // atribui o endereço de a a p
	r = &p; // atribui o endereço de p a r
	c = **r + b; // **r = a	
	printf("%d",c);
}
