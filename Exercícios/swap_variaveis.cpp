#include <stdio.h>

int main() {
	
	float a;
	float b;
	float c;
	
	float *pa;
	float *pb;
	
	scanf("%f %f", &a, &b);
	
	pa = &a;
	pb = &b;
	
	c = *pa;
	a = *pb;
	b = c;
	
	printf("a=%.1f\n", a);
	printf("b=%.1f", b);
	
}
