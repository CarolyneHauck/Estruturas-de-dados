/* Implementacao de estrutura do tipo grafo *
 * Listas Encadeadas                        */

#include <stdio.h>
#include <stdlib.h>
#define MaxNumVertices 100

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

typedef struct TipoTempoTermino{
	int t[MaxNumVertices+1];
	int restantes[MaxNumVertices+1];
	int numRestantes;
}TipoTempoTermino;

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
/* Busca em Profundidade */
void visitaDFS(int u, TipoGrafo *grafo, int *tempo, int *d, int *t, char *cor, int *ant);
void buscaEmProfundidade(TipoGrafo *grafo, int *t);
/* Componentes Fortemente Conectados */
void grafoTransposto(TipoGrafo *grafo, TipoGrafo *grafoT);
void visitaDFS2(int u, TipoGrafo *grafo, TipoTempoTermino *tt, int *tempo, int *d, int *t, char *cor, int *ant);
void buscaEmProfundidadeCFC(TipoGrafo *grafo, TipoTempoTermino *tt);
int maxTT(TipoTempoTermino *tt, TipoGrafo *grafo);
/* exercicios */
int grauEntradaGrafo(int v, TipoGrafo *grafo);
int grauSaidaGrafo(int v, TipoGrafo *grafo);

int main(){
	/* Exemplo: */
	TipoGrafo* grafo = (TipoGrafo*) malloc(sizeof(TipoGrafo));
	// inicializa vertices e arestas
	grafo->numVertices = 4;
	grafo->numArestas = 5;
	FGVazio(grafo);	
	//Preenche lista de adjacencias do exemplo de grafo dirigido (direcionado)
	insereAresta(0,1,1,grafo);
	insereAresta(0,3,1,grafo);
	insereAresta(1,2,1,grafo);
	insereAresta(2,0,1,grafo);
	insereAresta(2,3,1,grafo);
	//printf("Lista de adjacentes do grafo dirigido:\n");
	//imprimeGrafo(grafo);

	//chama busca em profundidade e salva os tempos
	TipoTempoTermino *tt = (TipoTempoTermino*) malloc(sizeof(TipoTempoTermino));
	buscaEmProfundidade(grafo,tt->t);

	//Gera o grafo transposto:
	TipoGrafo* grafoT = (TipoGrafo*) malloc(sizeof(TipoGrafo));
	grafoTransposto(grafo,grafoT);
	//printf("Lista de adjacentes do Grafo Transposto: \n");
	//imprimeGrafo(grafoT);

	//calcula os componentes fortemente conectados
	buscaEmProfundidadeCFC(grafoT, tt);

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

void visitaDFS(int u, TipoGrafo *grafo, int *tempo, int *d, int *t, char *cor, int *ant){
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

void buscaEmProfundidade(TipoGrafo *grafo, int *t){
	int x, tempo = 0;
	char cor[MaxNumVertices+1]; /* cores: b - branco, c - cinza, p - preto*/
	int ant[MaxNumVertices+1], d[MaxNumVertices+1];
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

void grafoTransposto(TipoGrafo *grafo, TipoGrafo *grafoT){
	int v, adj, peso, fimListaAdj = 0;
	No *aux;
	grafoT->numVertices = grafo->numVertices;
	grafoT->numArestas  = grafo->numArestas;
	FGVazio(grafoT);
	for(v = 0; v < grafo->numVertices; v++){
		if(!listaAdjVazia(v,grafo)){
			aux = primeiroListaAdj(v,grafo);
			fimListaAdj = 0;
			while(!fimListaAdj){
				proxAdj(v,grafo,&adj,&peso,aux,&fimListaAdj);
				aux = aux->prox;
				insereAresta(adj, v, peso, grafoT);
			}
		}
	}
}

int maxTT(TipoTempoTermino *tt, TipoGrafo *grafo){
	int result, i = 0, temp;
	while(!tt->restantes[i])i++;
	temp = tt->t[i];
	result = i;
	for(i=0; i<grafo->numVertices;i++){
		if(tt->restantes[i])
			if(temp < tt->t[i]){
				temp = tt->t[i];
				result = i;
			}
	}
	return result;
}
void visitaDFS2(int u, TipoGrafo *grafo, TipoTempoTermino *tt, int *tempo, int *d, int *t, char *cor, int *ant){
	int fimListaAdj, peso, v;
	No *aux;
	cor[u] = 'c';
	(*tempo)++; 
	d[u] = (*tempo);
	tt->restantes[u] = 0;
	tt->numRestantes--;
	printf("Visita %2d Tempo descoberta: %2d cinza\n",u,d[u]);
	if(!listaAdjVazia(u, grafo)){
		aux = primeiroListaAdj(u,grafo);
		fimListaAdj = 0;
		while(!fimListaAdj){
			proxAdj(u,grafo,&v,&peso,aux,&fimListaAdj);
			aux = aux->prox;
			if(cor[v]=='b'){
				ant[v] = u;
				visitaDFS2(v,grafo,tt,tempo,d,t,cor,ant);
			}
		}
	}
	cor[u] = 'p';
	(*tempo)++;
	t[u] = (*tempo);
	printf("Visita %2d Tempo termino %2d preto\n", u, t[u]);
}


void buscaEmProfundidadeCFC(TipoGrafo *grafo, TipoTempoTermino *tt){
	int tempo = 0;
	int d[MaxNumVertices+1], t[MaxNumVertices+1];
	int x,vRaiz,ant[MaxNumVertices+1];
	char cor[MaxNumVertices+1];	
	for(x=0; x<grafo->numVertices; x++){	
		cor[x] = 'b';
		ant[x] = -1;
	}
	tt->numRestantes = grafo->numVertices;
	for(x=0; x<grafo->numVertices; x++){	
		tt->restantes[x] = 1;
	}
	while(tt->numRestantes > 0){
		vRaiz = maxTT(tt, grafo);
		printf("Raiz da proxima arvore: %2d\n", vRaiz);
		visitaDFS2(vRaiz, grafo,tt,&tempo,d,t,cor,ant);
	}
}



/* Possivel resultado para os exercicios da parte 1 */
int grauEntradaGrafo(int v, TipoGrafo *grafo){
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

int grauSaidaGrafo(int v, TipoGrafo *grafo){
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

