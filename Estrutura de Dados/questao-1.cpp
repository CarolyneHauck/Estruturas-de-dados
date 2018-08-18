/* Implementacao de estrutura do tipo grafo *
 * Listas Encadeadas                        */

#include <stdio.h>
#include <stdlib.h>
#define MaxNumVertices 100
#define INFINITO 999999

typedef int TipoPeso;

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

/* Para a busca em largura*/
typedef struct TipoFila{
	No *inicio, *fim;
}TipoFila;

/* operacoes da lista */
void FLVazia(TipoLista *lista);
int vaziaLista(TipoLista *lista);
void insere(TipoItem it, TipoLista *lista);
void imprimeLista(TipoLista lista);
/* operacoes do grafo */
void FGVazio(TipoGrafo *grafo);
void insereAresta(int v1, int v2, int peso, TipoGrafo *grafo);
short existeAresta(int v1, int v2, TipoGrafo grafo);
/* para obter lista de adjacentes */
short listaAdjVazia(int v, TipoGrafo *grafo);
No* primeiroListaAdj(int v, TipoGrafo *grafo);
void proxAdj(int v, TipoGrafo *grafo, int *adj, int *peso, No *aux, int *fimListaAdj);
/* - */
void retira(No *p, TipoLista *lista, TipoItem it);
void retiraAresta(int v1,int v2, int peso, TipoGrafo *grafo);
void imprimeGrafo(TipoGrafo *grafo);
/* exercicios */
int grauEntradaGrafo(int v, TipoGrafo *grafo);
int grauSaidaGrafo(int v, TipoGrafo *grafo);
/* Busca em Profundidade */
void visitaDFS(int u, TipoGrafo *grafo, int *tempo, int *d, int *t, char 
*cor, int *ant);
void buscaEmProfundidade(TipoGrafo *grafo);
/* Busca em Largura - usa fila */
void FFVazia(TipoFila *fila);
int vaziaFila(TipoFila fila);
void enfileira(TipoItem x, TipoFila *fila);
void desenfileira(TipoFila *fila, TipoItem item);
void imprimeFila(TipoFila f);
void visitaBFS(int u, TipoGrafo *grafo, int *dist, char *cor, int *ant);
void buscaEmLargura(TipoGrafo *grafo, int u, int v);
void ImprimeCaminho (int u, int v, TipoGrafo *Grafo, int *ant);
void liberaGrafo(TipoGrafo *grafo);

int main(){

	TipoGrafo* grafo = (TipoGrafo*) malloc(sizeof(TipoGrafo));
	grafo->numVertices = 6;
	grafo->numArestas = 10;
	FGVazio(grafo);

	insereAresta(0,2,1,grafo);
	insereAresta(0,3,1,grafo);
	insereAresta(0,4,1,grafo);
	insereAresta(1,2,1,grafo);
	insereAresta(1,4,1,grafo);
	insereAresta(2,4,1,grafo);
	insereAresta(3,4,1,grafo);
	insereAresta(3,5,1,grafo);
	insereAresta(4,5,1,grafo);
	insereAresta(5,1,1,grafo);
	printf("Imprime a lista de adjacencia do grafo dirigido:\n");
	imprimeGrafo(grafo);

	printf("\n\n\n");
	buscaEmLargura(grafo, 0, 1);

	liberaGrafo(grafo);
	return 0;
}

void FLVazia(TipoLista *lista){
	lista->prim = (No*) malloc(sizeof(No));
	lista->ult = lista->prim;
	lista->prim->prox = NULL;
}

int vaziaLista(TipoLista *lista){
	return (lista->prim==lista->ult);
}

void insere(TipoItem it, TipoLista *lista){
	lista->ult->prox = (No*) malloc(sizeof(No));
	lista->ult = lista->ult->prox;
	lista->ult->item = it;
	lista->ult->prox = NULL;
}

void imprimeLista(TipoLista lista){
	No *aux;
	aux = lista.prim->prox;
	while (aux!=NULL){
		printf("%12d\n",aux->item.vertice);
		aux = aux->prox;
	}
}

void FGVazio(TipoGrafo *grafo){
	int i;
	for(i=0;i<grafo->numVertices;i++){
		FLVazia(&grafo->adj[i]);
	}
}

void insereAresta(int v1, int v2, int peso, TipoGrafo *grafo){
	TipoItem it;
	it.vertice = v2;
	it.peso = peso;
	insere(it,&grafo->adj[v1]);
}

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

/* para obter lista de adjacentes */
short listaAdjVazia(int v, TipoGrafo *grafo){
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

void retira(No *p, TipoLista *lista, TipoItem it){
/* o item a ser retirado eh o seguinte ao apontado por p*/
	No *q;
	if(vaziaLista(lista) || p==NULL || p->prox==NULL ){
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

void imprimeGrafo(TipoGrafo *grafo){
	int i;
	No *aux;
	for(i=0;i<grafo->numVertices;i++){
		printf("Vertice %2d: ",i);
		if(!vaziaLista(&grafo->adj[i])){
			aux = grafo->adj[i].prim->prox;
			while(aux!=NULL){
				printf(" %3d (%d)",aux->item.vertice,aux->item.peso);
				aux=aux->prox;
			}
		}
		putchar('\n');
	}
}

int grauEntradaGrafo(int v, TipoGrafo *grafo){
	int i, grau = 0;
	No *aux;
	for (i=0;i<grafo->numVertices;i++){
		if(!vaziaLista(&grafo->adj[i])){
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

int grauSaidaGrafo(int v, TipoGrafo *grafo){
	int i, grau = 0;
	No *aux;
	if(!vaziaLista(&grafo->adj[v])){
		aux = grafo->adj[v].prim->prox;
		while(aux!=NULL){
			grau++;
			aux=aux->prox;
		}
	}
	return grau;
}


void visitaDFS(int u, TipoGrafo *grafo, int *tempo, int *d, int *t, char
*cor, int *ant){
	int fimListaAdj;
	int p; //peso
	No *aux;
	int v;
	cor[u] = 'c';	
	(*tempo)++;
	d[u] = (*tempo);
	printf("Visita %2d tempo descoberta: %2d cinza %c \n",u,d[u],cor[u]);
	if(!listaAdjVazia(u,grafo)){
		aux = primeiroListaAdj(u, grafo);
		fimListaAdj = 0;		
		while (!fimListaAdj){
			proxAdj(u,grafo,&v,&p,aux,&fimListaAdj);
			aux = aux->prox;
			if(cor[v]=='b'){				
				ant[v] = u;
				visitaDFS(v,grafo,tempo,d,t,cor,ant);
			}
		}
	}
	cor[u] = 'p';
	(*tempo)++;
	t[u] = (*tempo); 
	printf("Visita %2d tempo termino: %2d preto\n",u,t[u]); 
}

void buscaEmProfundidade(TipoGrafo *grafo){
	int x, tempo = 0;
	int d[MaxNumVertices+1], t[MaxNumVertices+1];
	char cor[MaxNumVertices+1]; /* cores: b - branco, c - cinza, p - preto*/
	int ant[MaxNumVertices+1];
	for(x = 0; x<grafo->numVertices;x++){
		cor[x] = 'b';
		ant[x] = -1;
	}
	for(x = 0; x<grafo->numVertices;x++){
		if(cor[x]=='b'){
			visitaDFS(x, grafo,&tempo,d,t,cor,ant);
		}	
	}
}


void FFVazia(TipoFila *fila){
	fila->inicio = (No*) malloc(sizeof(No));
	fila->fim = fila->inicio;
	fila->inicio->prox = NULL;
}

int vaziaFila(TipoFila fila){
	return (fila.inicio == fila.fim);
}

void enfileira(TipoItem x, TipoFila *fila){
	fila->fim->prox = (No*) malloc(sizeof(No));
	fila->fim = fila->fim->prox;
	fila->fim->item = x;
	fila->fim->prox = NULL;
}

void desenfileira(TipoFila *fila, TipoItem item){
	No *q;
	if (vaziaFila(*fila)){
		printf("Erro: fila vazia!\n");
		return;
	}
	q = fila->inicio;
	fila->inicio = fila->inicio->prox;
	item = fila->inicio->item;
	free(q);
}

void imprimeFila(TipoFila f) {
    No *atual; // ponteiro para percorrer a fila
	if (f.inicio==NULL){//verifica se esta vazia
		printf("Fila Vazia! \n"); 
	}else{
    	atual = f.inicio;
	    printf("\nFila=> ");
    	while (atual != NULL) {
    	    printf("%d \t", atual->item.vertice);
        	atual = atual->prox;
    	}
    	printf("\n");
	}
}


void visitaBFS(int u, TipoGrafo *grafo, int *dist, char *cor, int *ant){
	int v; 
	No *aux;
	int fimListaAdj;
	int peso;
	TipoItem item;
	TipoFila fila;
	cor[u] = 'c';
	dist[u] = 0;
	FFVazia(&fila);
	item.vertice = u;
	item.peso = 0;
	enfileira(item,&fila);	
	printf("Visita origem %2d cor: cinza F: ", u);
	imprimeFila(fila);
	while(!vaziaFila(fila)){
		desenfileira(&fila, item);
		u = item.vertice;        
		if(!listaAdjVazia(u,grafo)){			
			aux = primeiroListaAdj(u, grafo);
			fimListaAdj = 0;
			while (!fimListaAdj){
				proxAdj(u,grafo,&v,&peso,aux,&fimListaAdj);
				aux = aux->prox;
				if(cor[v] != 'b') continue;
				cor[v] = 'c';
				dist[v] = dist[u]+1;
				ant[v] = u;
				item.vertice = v;
				item.peso = peso;
				enfileira(item,&fila);
			}
		}
		cor[u] = 'p';
		printf("Visita %2d Dist %2d cor: preto F: ", u, dist[u]);
		imprimeFila(fila);
	}
}

void buscaEmLargura(TipoGrafo *grafo, int u, int v){
	int x;
	int dist[MaxNumVertices+1];
	char cor[MaxNumVertices+1];
	int ant[MaxNumVertices+1];
	for(x = 0; x<grafo->numVertices;x++){
		cor[x] = 'b';
		dist[x] = INFINITO;
		ant[x] = -1;
	}
	for(x = 0; x<grafo->numVertices;x++){
		if (cor[x]=='b')
			visitaBFS(x, grafo, dist, cor, ant);
	}
	printf("\n\n\n");
	printf("Impressao do caminho de %d a %d:\n", u, v);
	ImprimeCaminho (u, v, grafo, ant);
}

void ImprimeCaminho (int u, int v, TipoGrafo *Grafo, int *ant){
	if (u==v){
		printf("%d ", u); return;
	}
	if(ant[v] == -1){
		printf("Nao existe caminho de %d ate %d\n", u, v);
	}else {
		ImprimeCaminho(u, ant[v], Grafo, ant);
	
		printf("%d ",v);
	}
}
