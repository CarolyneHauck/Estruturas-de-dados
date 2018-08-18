/* Implementação do exemplo: 
 * Lista duplamente encadeada - deque
 */

#include <stdio.h>
#include <stdlib.h>

struct lista2{
	float info;
	struct lista2* ant;
	struct lista2* prox;
};
typedef struct lista2 Lista2;

struct fila2{
	Lista2* ini;
	Lista2* fim;
};
typedef struct fila2 Fila2;

/* funcao auxiliar: para inserir elemento no inicio */
static Lista2* ins2_ini(Lista2* ini, float v){
	Lista2* novo = (Lista2*) malloc(sizeof(Lista2));
	novo->info = v;
	novo->prox = ini;
	novo->ant  = NULL;
	if(ini!=NULL) /*verifica se a lista esta vazia*/
		ini->ant=novo;
	return novo;
}
/* funcao auxiliar: para inserir elemento no fim */
static Lista2* ins2_fim(Lista2* fim, float v){
	Lista2* novo = (Lista2*) malloc(sizeof(Lista2));
	novo->info = v;
	novo->prox = NULL;
 	novo->ant  = fim;
	if(fim!=NULL)/*verifica se a lista esta vazia*/
		fim->prox = novo;
	return novo;
}

/* funcao auxiliar: para retirar elemento do inicio */
static Lista2* ret2_ini(Lista2* ini){
	Lista2* p = ini->prox;
	if(p!=NULL)/*verifica se a lista nao ficou vazia*/
		p->ant = NULL;
	free(ini);
	return p;
}
	
/* funcao auxiliar: para retirar elemento do fim */
static Lista2* ret2_fim(Lista2* fim){
	Lista2* p = fim->ant;
	if(p!=NULL)/*verifica se a lista nao ficou vazia*/
		p->prox = NULL;
	free(fim);
	return p;
}

/* funcao para inserir no inicio */
void fila2_insere_ini(Fila2* f, float v){
	f->ini = ins2_ini(f->ini, v);
	if(f->fim == NULL) /* se fila estava vazia */
		f->fim = f->ini; 
}		

/* funcao para inserir no fim */
void fila2_insere_fim(Fila2* f, float v){
	f->fim = ins2_fim(f->fim, v);
	if(f->ini == NULL) /* se fila estava vazia */
		f->ini = f->fim; 
}		

int fila2_vazia(Fila2* f2){
	return (f2->ini==NULL);
}

/* funcao para retirar do inicio*/
float fila2_retira_ini(Fila2* f2){
	float v;
	if (fila2_vazia(f2)){
		printf("Fila vazia!\n");
		exit(1); /* aborta programa */
	}
	v = f2->ini->info;
	f2->ini = ret2_ini(f2->ini);
	if(f2->ini == NULL) /* se fila ficou vazia */
		f2->fim = NULL;
	return v;
}	

float fila2_retira_fim(Fila2* f2){
	float v;
	if(fila2_vazia(f2)){
		printf("Fila vazia!\n");
		exit(1); /* aborta programa */
	}
	v = f2->fim->info;
	f2->fim = ret2_fim(f2->fim);
	if(f2->fim == NULL) /* se ficou vazia */
		f2->ini = NULL;
	return v;
}	

Fila2* fila2_cria(void){
	Fila2* f2 = (Fila2*) malloc(sizeof(Fila2));
	f2->ini = f2->fim = NULL;
	return f2;
}

void fila2_libera(Fila2* f2){
	Lista2* q = f2->ini;
	while (q!= NULL){
		Lista2* t = q->prox;
		free(q);
		q = t;
	}
	free(f2);
}

void fila2_imprime(Fila2* f2){
	Lista2* q;
	for (q=f2->ini; q!=NULL;q=q->prox)
		printf("%.2f\t",q->info);
	printf("\n");
}

int main(){

	Fila2* f2 = fila2_cria();
	fila2_insere_ini(f2,20.8);
	fila2_insere_ini(f2,20.0);
	fila2_imprime(f2);
	fila2_insere_fim(f2,21.2);
	fila2_insere_fim(f2,24.3);
	fila2_imprime(f2);
	fila2_retira_fim(f2);
	fila2_imprime(f2);
	fila2_retira_ini(f2);
	fila2_imprime(f2);

	fila2_libera(f2);
	
	return 0;
}
