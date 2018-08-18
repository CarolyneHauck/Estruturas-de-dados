#include <stdio.h>
#include <stdlib.h>
typedef struct ponto {
	int x;
	int y;
} Ponto;
int main() {
	Ponto *pt = (Ponto*) malloc(sizeof(Ponto));
	pt->x = 4;
	pt->y = 3;
	printf("%d %d\n",pt->x,pt->y);
	printf("%d %d",&pt->x,&pt->y);
}
