/*  TAD: Ponto (x, y)
	Representar um ponto abstrato em R2.
	Definir uma estrutura de dados (Ponto) e o conjunto
	de funções que operam sobre essa estrutura.
	
	1. pto_cria: criar um ponto com coordenadas x e y.
	2. pto_libera: libera a memória alocada para o ponto.
	3. pto_acessa: retorna as coordenadas de um ponto.
	4. pto_atribui: atribui novos valores às coordenadas.
	5. pto_distancia: calcula a distância entre 2 pontos.  */
	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
	
	srand(time(0));
	
	float* x;
	float* y;
	
	x = (float*) malloc(sizeof(float));
	y = (float*) malloc(sizeof(float));
	
	Ponto* p = pto_cria(2.0, 1.0);
	Ponto* q = pto_cria(3.4, 2.1);
	
	pto_acessa(p, x, y);
	printf("Ponto: (%.1f, %.1f)\n", *x, *y);
	
	printf("Novas coordenadas do ponto: ");
	scanf("%f%f", x, y);
	
	pto_atribui(p, *x, *y);
	pto_acessa(p, x, y);
	printf("Ponto: (%.1f, %.1f)\n", *x, *y);
	
	float d = pto_distancia(p, q);
	
	printf("Distancia entre pontos: %.2f", d);
	pto_libera(p);
	pto_libera(q);
	
	return 0;
}

Ponto* pto_cria(float x, float y) {
	
	Ponto* pt = (Ponto*) malloc(sizeof(Ponto));
	
	if (pt == NULL) {
		printf("Error!");
		exit(1);
	}
	
	pt->x = x;
	pt->x = y;
	
	return pt;
}

void pto_libera(Ponto* pt) {
	
	free(pt);
	
}

void pto_acessa(Ponto* pt, float* x, float* y) {
	
	*x = pt->x;
	*y = pt->y;
	
}

void pto_atribui(Ponto* pt, float x, float y) {
	
	pt->x = x;
	pt->x = y;
	
}

float pto_distancia(Ponto* pt1, Ponto* pt2) {
	
	float dx = pt1->x - pt2->x;
	float dy = pt1->y - pt2->y;
	
	return sqrt(dx*dx + dy*dy);
	
}
