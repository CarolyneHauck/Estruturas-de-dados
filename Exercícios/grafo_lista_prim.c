/* Implementacao de estrutura do tipo grafo *
 * Listas Encadeadas                        */

#include <stdio.h>
#include <stdlib.h>
#define MaxNumVertices 100
#define INFINITO 999999

typedef struct TipoItem{
	int vertice;
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
	int numVertices;
	int numArestas;
}TipoGrafo;

/* heap */
typedef struct Item{
	int chave;
}Item;

typedef Item Vetor[MaxNumVertices+1];


/* funcoes para manipular a lista */
void FLVazia(TipoLista *lista);
int vazia(TipoLista *lista);
void insere(TipoItem it, TipoLista *lista);
/* funcoes para manipular o grafo */
void FGVazio(TipoGrafo *grafo);
void insereAresta(int v1, int v2, int peso, TipoGrafo *grafo);
short existeAresta(int v1, int v2, TipoGrafo grafo);
void retira(No *p, TipoLista *lista, TipoItem it);
void retiraAresta(int v1,int v2, int peso, TipoGrafo *grafo);
void imprimeGrafo(TipoGrafo *grafo);
void liberaGrafo(TipoGrafo *grafo);
/* para obter lista de adjacentes */
int listaAdjVazia(int v, TipoGrafo *grafo);
No* primeiroListaAdj(int v, TipoGrafo *grafo);
void proxAdj(int v, TipoGrafo *grafo, int *adj, int *peso, No *aux, int *fimListaAdj);
/* Manipular heap */
void refazInd(int esq, int dir, Item *a, int *peso, int *pos);
void constroi(Item *a, int *n, int *peso, int *pos);
Item retiraMinInd(Item *a, int *peso, int *pos, int *n);
void diminuiChaveInd(int i, int chaveNova, Item *a, int *peso, int *pos);
/* Arvore geradora minima - algoritmo de Prim */
void algPrim(TipoGrafo *grafo, int raiz);

int main(){
	/* Exemplo: */
	TipoGrafo* grafo = (TipoGrafo*) malloc(sizeof(TipoGrafo));
	// inicializa vertices e arestas
	grafo->numVertices = 6;
	grafo->numArestas = 10;
	FGVazio(grafo);	
	//Preenche lista de adjacencias do exemplo de grafo dirigido (direcionado)
	insereAresta(0,1,6,grafo);
	insereAresta(0,2,1,grafo);
	insereAresta(0,3,5,grafo);
	insereAresta(1,0,6,grafo);
	insereAresta(1,2,2,grafo);
	insereAresta(1,4,5,grafo);
	insereAresta(2,0,1,grafo);
	insereAresta(2,1,2,grafo);
	insereAresta(2,3,2,grafo);
	insereAresta(2,4,6,grafo);
	insereAresta(2,5,4,grafo);
	insereAresta(3,0,5,grafo);
	insereAresta(3,2,2,grafo);
	insereAresta(3,5,4,grafo);
	insereAresta(4,1,5,grafo);
	insereAresta(4,2,6,grafo);
	insereAresta(4,5,3,grafo);
	insereAresta(5,2,4,grafo);
	insereAresta(5,3,4,grafo);
	insereAresta(5,4,3,grafo);
	//printf("Lista de adjacentes do grafo dirigido:\n");
	imprimeGrafo(grafo);

	algPrim(grafo, 0);


/*	TipoGrafo* grafo = TipoGrafo*) malloc(sizeof(TipoGrafo));
	// inicializa vertices e arestas
	grafo->numVertices = 6;
	grafo->numArestas = 9;
	FGVazio(grafo);	
	//Preenche lista de adjacencias do exemplo de grafo dirigido (direcionado)
	insereAresta(0,1,1,grafo);
	insereAresta(0,2,5,grafo);
	insereAresta(1,0,1,grafo);
	insereAresta(1,2,2,grafo);
	insereAresta(1,3,5,grafo);
	insereAresta(1,4,2,grafo);
	insereAresta(2,0,5,grafo);
	insereAresta(2,1,2,grafo);
	insereAresta(2,4,2,grafo);
	insereAresta(3,1,5,grafo);
	insereAresta(3,4,1,grafo);
	insereAresta(3,5,2,grafo);
	insereAresta(4,1,2,grafo);
	insereAresta(4,2,2,grafo);
	insereAresta(4,3,1,grafo);
	insereAresta(4,5,4,grafo);
	insereAresta(5,3,2,grafo);
	insereAresta(5,4,4,grafo);
	//printf("Lista de adjacentes do grafo dirigido:\n");
//	imprimeGrafo(grafo);

	algPrim(grafo, 0);*/


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
void insereAresta(int v1, int v2, int peso, TipoGrafo *grafo){
	TipoItem it;
	it.vertice = v2;
	it.peso = peso;
	insere(it,&grafo->adj[v1]);
}

/* retorna verdadeiro se existe aresta entre dois vertices */
short existeAresta(int v1, int v2, TipoGrafo grafo){
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

void retiraAresta(int v1,int v2, int peso, TipoGrafo *grafo){
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

/* para obter lista de adjacentes */
int listaAdjVazia(int v, TipoGrafo *grafo){
	return (grafo->adj[v].prim == grafo->adj[v].ult);
}

No* primeiroListaAdj(int v, TipoGrafo *grafo){
	return (grafo->adj[v].prim->prox);
}

void proxAdj(int v, TipoGrafo *grafo, int *adj, int *peso, No *aux, int *fimListaAdj){/*retorna adj e peso do item apontado por prox*/
	//No *p;	
	*adj = aux->item.vertice;
	*peso = aux->item.peso;
	if(aux->prox==NULL){ 
		*fimListaAdj = 1;
	}
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

void refazInd(int esq, int dir, Item *a, int *peso, int *pos){
	int i = esq;
	int j = i*2;
	Item x = a[i];
	while(j<=dir){
		if(j<dir){
			if (peso[a[j].chave] > peso[a[j+1].chave]) j++;
		}
		if (peso[x.chave] <= peso[a[j].chave]) {
			a[i] = x;
			pos[x.chave] = i;
			break;
		}
		a[i] = a[j];
		pos[a[j].chave] = i;
		i = j;
		j = i*2;
	}	
}

void constroi(Item *a, int *n, int *peso, int *pos){
	int esq;
	esq = (*n) / 2 + 1;
	while (esq > 1){
		esq--;
		refazInd(esq, *n, a, peso, pos);
	}
}

Item retiraMinInd(Item *a, int *peso, int *pos, int *n){
	Item result;
	if((*n) < 1) {
		printf("Erro: heap vazio\n");
		return result;
	}
	result = a[1];
	a[1] = a[(*n)];
	pos[a[(*n)].chave] = 1;
	(*n)--;
	refazInd(1,(*n),a,peso,pos);
	return result;		
}

void diminuiChaveInd(int i, int chaveNova, Item *a, int *peso, int *pos){
	Item x;
	if(chaveNova > peso[a[i].chave]){
		printf("Erro: chave nova maior que chave atual. %d \n", peso[a[i].chave]);
		return;
	}
	peso[a[i].chave] = chaveNova;
	while((i > 1) && (peso[a[i/2].chave] > peso[a[i].chave])){
		x = a[i/2];
		a[i/2] = a[i];
		pos[a[i].chave] = i/2;
		a[i] = x;
		pos[x.chave] = i;
		i /= 2;
	}
}

void algPrim(TipoGrafo *grafo, int raiz){
	int ant[MaxNumVertices + 1], peso[MaxNumVertices + 1];
	int pos[MaxNumVertices + 1], itensHeap[MaxNumVertices + 1];
	Vetor a;
	Item temp;
	int u,v, fimListaAdj,n,pesoaresta;
	No *aux;
	for(u = 0 ; u< grafo->numVertices ; u++){
		/*constroi heap com valores infinito*/
		ant[u] = -1;
		peso[u] = INFINITO;
		a[u+1].chave  = u; /*heap a ser construido*/
		itensHeap[u] = 1;
		pos[u] = u+1;
	}
	n = grafo->numVertices;
	peso[raiz] = 0;
	constroi(a,&n,peso,pos);
	while(n >= 1){/* enquanto heap nao vazio */
		temp = retiraMinInd(a,peso,pos,&n);
		u=temp.chave;	
		itensHeap[u] = 0;
		if(u != raiz) 
			printf("Aresta de arvore v[%d] v[%d]\n", u, ant[u]);
		if(!listaAdjVazia(u,grafo)){
			aux = primeiroListaAdj(u, grafo);			
			fimListaAdj = 0;
			while(!fimListaAdj){
				proxAdj(u,grafo,&v,&pesoaresta,aux,&fimListaAdj);
				aux = aux->prox;
				if(itensHeap[v] && pesoaresta < peso[v]){
					ant[v] = u;
					diminuiChaveInd(pos[v],pesoaresta,a,peso,pos);
				}
			}
		}
	}
}

