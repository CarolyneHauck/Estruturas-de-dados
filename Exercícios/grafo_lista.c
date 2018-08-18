/* Implementacao de estrutura do tipo grafo *
 * Listas Encadeadas                        */

#include <stdio.h>
#include <stdlib.h>
#define MaxNumVertices 100

typedef struct TipoItem{
	char vertice;
	int peso;
}TipoItem;

typedef struct No{
	TipoItem item;
	struct No *prox;
}No;

typedef struct TipoLista{
	No *prim, *ult;
}TipoLista;

typedef struct TipoGrafo{
	TipoLista adj[MaxNumVertices+1];
	char numVertices;
	int numArestas;
}TipoGrafo;

/* funcoes para manipular a lista */
void FLVazia(TipoLista *lista);
int vazia(TipoLista *lista);
void insere(TipoItem it, TipoLista *lista);
/* funcoes para manipular o grafo */
void FGVazio(TipoGrafo *grafo);
void insereAresta(char v1, char v2, int peso, TipoGrafo *grafo);
short existeAresta(char v1, char v2, TipoGrafo grafo);
void retira(No *p, TipoLista *lista, TipoItem it);
void retiraAresta(char v1,char v2, int peso, TipoGrafo *grafo);
void imprimeGrafo(TipoGrafo *grafo);
void liberaGrafo(TipoGrafo *grafo);
/* exercicios */
int grauEntradaGrafo(char v, TipoGrafo *grafo);
int grauSaidaGrafo(char v, TipoGrafo *grafo);

int main(){

	/* Exemplos: */
	// cria um grafo
	TipoGrafo* grafo = (TipoGrafo*) malloc(sizeof(TipoGrafo));
	// inicializa vertices e arestas
	grafo->numVertices = 5;
	grafo->numArestas = 7;
	FGVazio(grafo);
	imprimeGrafo(grafo); //imprime matriz vazia

	//Preenche matriz de adjacencias do exemplo de grafo nao dirigido (direcionado)
	insereAresta(0,1,1,grafo);
	insereAresta(0,4,1,grafo);
	insereAresta(1,0,1,grafo);
	insereAresta(1,2,1,grafo);
	insereAresta(1,3,1,grafo);
	insereAresta(1,4,1,grafo);
	insereAresta(2,1,1,grafo);
	insereAresta(2,3,1,grafo);
	insereAresta(3,1,1,grafo);
	insereAresta(3,2,1,grafo);
	insereAresta(3,4,1,grafo);
	insereAresta(4,0,1,grafo);
	insereAresta(4,1,1,grafo);
	insereAresta(4,3,1,grafo);
	printf("Imprime matriz adjacencia do grafo nao dirigido:\n");
	imprimeGrafo(grafo);

	//Cria outro grafo:
	TipoGrafo* grafo1 = (TipoGrafo*) malloc(sizeof(TipoGrafo));
	grafo1->numVertices = 6;
	grafo1->numArestas = 8;
	FGVazio(grafo1);

	//Preenche matriz de adjacencias do exemplo de grafo dirigido
	insereAresta(0,1,1,grafo1);
	insereAresta(0,3,1,grafo1);
	insereAresta(1,4,1,grafo1);
	insereAresta(2,4,1,grafo1);
	insereAresta(2,5,1,grafo1);
	insereAresta(3,1,1,grafo1);
	insereAresta(4,3,1,grafo1);
	insereAresta(5,5,1,grafo1);
	printf("Imprime matriz adjacencia do grafo dirigido:\n");
	imprimeGrafo(grafo1);

	printf("Grau de Entrada do vertice %d = %d\n", 2, grauEntradaGrafo(2,grafo1));
	printf("Grau de Saida do vertice %d = %d\n", 2, grauSaidaGrafo(2,grafo1));

	liberaGrafo(grafo);
	liberaGrafo(grafo1);

	return 0;
}

/* cria lista vazia */
void FLVazia(TipoLista *lista){
	lista->prim = (No*) malloc(sizeof(No));
	lista->ult = lista->prim;
	lista->prim->prox = NULL;
}

/* retorna verdadeiro (1) se a lista for vazia */
int vazia(TipoLista *lista){
	return (lista->prim==lista->ult);
}

/* insere item no final da lista */
void insere(TipoItem it, TipoLista *lista){
	lista->ult->prox = (No*) malloc(sizeof(No));
	lista->ult = lista->ult->prox;
	lista->ult->item = it;
	lista->ult->prox = NULL;
}

/* Cria grafo com listas de adjacencia vazias para *
 * cada vertice                                    */
void FGVazio(TipoGrafo *grafo){
	int i;
	for(i=0;i<grafo->numVertices;i++){
		FLVazia(&grafo->adj[i]);
	}
}

/* Insere aresta entre dois vertices *
 * atualizando a lista de adjacentes */
void insereAresta(char v1, char v2, int peso, TipoGrafo *grafo){
	TipoItem it;
	it.vertice = v2;
	it.peso = peso;
	insere(it,&grafo->adj[v1]);
}

/* retorna verdadeiro se existe aresta entre dois vertices */
short existeAresta(char v1, char v2, TipoGrafo grafo){
	No *aux;
	short encontrouAresta = 0;
	aux = grafo.adj[v1].prim->prox;
	while(aux!= NULL && encontrouAresta == 0){
		if(v2 == aux->item.vertice)
			encontrouAresta = 1;
		aux = aux->prox;
	}
	return encontrouAresta;
}

void retira(No *p, TipoLista *lista, TipoItem it){
/* o item a ser retirado eh o seguinte ao apontado por p*/
	No *q;
	if(vazia(lista) || p==NULL || p->prox==NULL ){
		printf("Erro: lista vazia ou posicao nao existe!\n");
		return;
	}
	q = p->prox;
	it = q->item;
	p->prox = q ->prox;
	if (p->prox == NULL)
		lista->ult = p;
	free(q);
}

void retiraAresta(char v1,char v2, int peso, TipoGrafo *grafo){
	No *auxAnt, *aux;
	short encontrouAresta = 0;
	TipoItem it;
	auxAnt = grafo->adj[v1].prim;
	aux = grafo->adj[v1].prim->prox;
	while(aux != NULL && encontrouAresta == 0){
		if (v2==aux->item.vertice){
			retira(auxAnt, &grafo->adj[v1], it);
			grafo->numArestas--;
			encontrouAresta = 1;
		}
		auxAnt = aux;
		aux = aux->prox;
	}
}

void liberaGrafo(TipoGrafo *grafo){
	No *auxAnt, *aux;
	int i;
	for(i = 0; i<grafo->numVertices;i++){
		aux = grafo->adj[i].prim->prox;
		free(grafo->adj[i].prim);/*libera primeiro no*/
		grafo->adj[i].prim=NULL;
		while(aux!=NULL){
			auxAnt = aux;
			aux = aux->prox;
			free(auxAnt);
		}
	}
	grafo->numVertices = 0;
}

void imprimeGrafo(TipoGrafo *grafo){
	int i;
	No *aux;
	for(i=0;i<grafo->numVertices;i++){
		printf("Vertice %2d: ",i);
		if(!vazia(&grafo->adj[i])){
			aux = grafo->adj[i].prim->prox;
			while(aux!=NULL){
				printf(" %3d (%d)",aux->item.vertice,aux->item.peso);
				aux=aux->prox;
			}
		}
		putchar('\n');
	}
}

/* Possivel resultado para os exercicios da parte 1 */
int grauEntradaGrafo(char v, TipoGrafo *grafo){
	int i, grau = 0;
	No *aux;
	for (i=0;i<grafo->numVertices;i++){
		if(!vazia(&grafo->adj[i])){
			aux = grafo->adj[i].prim->prox;
			while(aux!=NULL){
				if(aux->item.vertice==v){
					grau++;
				}
				aux=aux->prox;
			}
		}
	}
	return grau;
}

int grauSaidaGrafo(char v, TipoGrafo *grafo){
	int i, grau = 0;
	No *aux;
	if(!vazia(&grafo->adj[v])){
		aux = grafo->adj[v].prim->prox;
		while(aux!=NULL){
			grau++;
			aux=aux->prox;
		}
	}
	return grau;
}

