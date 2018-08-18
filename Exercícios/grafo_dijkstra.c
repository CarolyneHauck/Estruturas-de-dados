/* Implementacao de estrutura do tipo grafo *
 * Listas Encadeadas                        *
 * Dijkstra                                 */

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

/* Heap */
struct Item{
	int chave;
};

/* funcoes para manipular a lista */
void FLVazia(TipoLista *lista);
int vazia(TipoLista *lista);
void insere(TipoItem it, TipoLista *lista);
/* funcoes para manipular o grafo */
void FGVazio(TipoGrafo *grafo);
void insereAresta(int v1, int v2, int peso, TipoGrafo *grafo);
int existeAresta(int v1, int v2, TipoGrafo grafo);
void retira(No *p, TipoLista *lista, TipoItem it);
void retiraAresta(int v1,int v2, int peso, TipoGrafo *grafo);
void imprimeGrafo(TipoGrafo *grafo);
void liberaGrafo(TipoGrafo *grafo);
/* para obter lista de adjacentes */
short listaAdjVazia(int v, TipoGrafo *grafo);
No* primeiroListaAdj(int v, TipoGrafo *grafo);
void proxAdj(int v, TipoGrafo *grafo, int *adj, int *peso, No *aux, int *fimListaAdj);
/* Dijkstra*/
void dijkstra(TipoGrafo *grafo, int raiz);

int main(){

	/* Exemplos: */
/*	// cria um grafo
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
*/
	

/*	//Cria outro grafo:
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
*/

	// cria um grafo
	TipoGrafo* grafod = (TipoGrafo*) malloc(sizeof(TipoGrafo));
	// inicializa vertices e arestas
	grafod->numVertices = 5;
	grafod->numArestas = 7;
	FGVazio(grafod);	

	//Preenche matriz de adjacencias do exemplo de grafo nao dirigido (direcionado)
	insereAresta(0,1,1,grafod);
	insereAresta(0,3,3,grafod);
	insereAresta(0,4,10,grafod);
	insereAresta(1,2,5,grafod);
	insereAresta(2,4,1,grafod);
	insereAresta(3,2,2,grafod);
	insereAresta(3,4,6,grafod);
	imprimeGrafo(grafod); //imprime lista adj

	int raiz;
	printf("Informe o vertice raiz: \n");
	scanf("%d", &raiz);

	dijkstra(grafod,raiz);

//	liberaGrafo(grafo);
//	liberaGrafo(grafo1);

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
int existeAresta(int v1, int v2, TipoGrafo grafo){
	No *aux;
	int encontrouAresta = 0;
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
	int encontrouAresta = 0;
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


void refazInd(int esq, int dir, struct Item *a, int *p, int *pos){
	int i = esq;
	int j;
	struct Item x;
	j = i * 2;
	x = a[i];
	while(j <= dir){
		if (j<dir){
			if (p[a[j].chave] > p[a[j+1].chave]){
				j++;
			}
		}
		if(p[x.chave]<=p[a[j].chave]){
			a[i] = x;
			pos[x.chave] = i;
			return;
		}
		a[i] = a[j];
		pos[a[j].chave]=i;
		i = j;
		j = i*2;
	}
}

void constroi(struct Item *a, int *n, int *p, int *pos){
	int esq;
	esq = *n / 2 + 1;
	while(esq>1){
		esq--;
		refazInd(esq, *n, a, p, pos);
	}
}

struct Item retiraMinInd(struct Item *a, int n, int *p, int *pos){
	struct Item result;
	if(n<1){
		printf("Erro: heap vazio!\n");
		return result;
	}
	result = a[1];
	a[1] = a[n];
	pos[a[n].chave] = 1;
	n--;
	refazInd(1,n,a,p,pos);
	return result;
}

void diminuiChaveInd(int i, int chaveNova, struct Item *a, int *p, int *pos){
	struct Item x;
	if (chaveNova > p[a[i].chave]){
		printf("Erro: Chave nova maior que a chave atual!\n");
		return;
	}
	p[a[i].chave] = chaveNova;
	while (i>1 && p[a[i/2].chave] > p[a[i].chave]){
		x = a[i/2];
		a[i/2] = a[i];
		pos[a[i].chave] = 1/2;
		a[i] = x;
		pos[x.chave] = i;
		i = i/2;
	}
}

void imprimeCaminho(int origem, int v, TipoGrafo *grafo, int *ant){
	if (origem==v) {
		printf("%d \t", origem);
		return;
	}
	if (ant[v]==-1){
		printf("Não existe caminho de %d ate %d\n", origem, v);
	}else{
		imprimeCaminho(origem, ant[v], grafo, ant);
		printf("%d \t", v);
	}
}

void dijkstra(TipoGrafo *grafo, int raiz){
	int ant[MaxNumVertices+1];
	int p[MaxNumVertices+1];
	int pos[MaxNumVertices+1];
	int u,v,n;
	int itensheap[MaxNumVertices+1];
	struct Item temp, a[MaxNumVertices+1];
	No *aux;
	int peso = INFINITO, fimListaAdj;
	for(u = 0;u<=grafo->numVertices;u++){
		ant[u] = -1;
		p[u] = INFINITO;
		a[u+1].chave = u; /*heap a ser construido*/
		itensheap[u] = 1; /*true*/
		pos[u] = u+1;
	}
	p[raiz] = 0;
	n = grafo->numVertices;
	constroi(a,&n,p,pos);
	while (n>=1){
		temp = retiraMinInd(a,n,p,pos);
		n--;
		u = temp.chave;
		itensheap[u] = 0; /*false*/
		if(!listaAdjVazia(u,grafo)){
			aux = primeiroListaAdj(u,grafo);
			fimListaAdj = 0;
			while(!fimListaAdj){
				proxAdj(u,grafo,&v,&peso,aux,&fimListaAdj);
				aux = aux->prox;
				if(p[v]>p[u]+peso){
					p[v] = p[u] + peso;
					ant[v] = u;
					diminuiChaveInd(pos[v], p[v],a,p,pos);
					printf("caminho: v[%d] v[%d] d[%d]\n", v,ant[v],p[v]);
				}
			}
		}
	}
}
