/* TAD: Ponto (x,y)
	Representar um ponto abstrato em R2. Definir uma
	estrutura de dados (Ponto) e o conjunto de funções
	que operam sobre essa estrutura.
	1. pto_cria: criar um ponto com coordenadas x e y
	2. pto_libera: libera a memória alocada para o ponto
	3. pto_acessa: retorna as coordenadas de um ponto
	4. pto_atribui: atribui novos valores às coordenadas
	5. pto_distancia: calcula a distância entre 2 pontos */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	float x;
	float y;
} Ponto;

Ponto* pto_cria(float, float);
void pto_libera(Ponto*);
void pto_acessa(Ponto*, float*, float*);
void pto_atribui(Ponto*, float, float);
float pto_distancia(Ponto*, Ponto*);

int main() {
	Ponto* p = pto_cria(2.0,1.0);
	Ponto* q = pto_cria(3.4,2.1);
	
	float* x = (float*)malloc(sizeof(float));
	float* y = (float*)malloc(sizeof(float));
	pto_acessa(p,x,y); 		// acessar os campos do ponto p
	printf("Ponto: (%.1f, %.1f)\n",*x,*y); // exibir os campos
	printf("Novas coordenadas do ponto: ");
    scanf("%f%f",x,y); 		// entrar com novos x e y
    pto_atribui(p,*x,*y); 	// muda x e y no ponto qp
	pto_acessa(p,x,y); 		// acessar os campos do ponto p
	printf("Ponto: (%.1f, %.1f)\n",*x,*y); // exibir os campos
    
	float d = pto_distancia(p,q);
	printf("Distancia entre pontos: %.2f",d);
	pto_libera(q);
	pto_libera(p);
	return 0;
}

Ponto* pto_cria(float x, float y) {
	Ponto* p = (Ponto*) malloc(sizeof(Ponto));
	if(p==NULL) {
		printf("Error!");
		exit(1);
	}
	p->x = x;
	p->y = y;
	return p;
}

void pto_libera(Ponto* p) {
	free(p);
}

void pto_acessa(Ponto* p, float* x, float* y) {
	*x = p->x;
	*y = p->y;
}

void pto_atribui(Ponto* p, float x, float y) {
	p->x = x;
	p->y = y;
}

float pto_distancia(Ponto* p1, Ponto* p2) {
	float dx = p1->x - p2->x;
	float dy = p1->y - p2->y;
	return sqrt(dx*dx + dy*dy);
}
