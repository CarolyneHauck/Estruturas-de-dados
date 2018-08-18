/* Implementacao de estrutura do tipo grafo *
 * Matriz de adjacencia                     */

#include <stdio.h>
#include <stdlib.h>
#define MaxNumVertices 100
#define MaxNumArestas 4500

typedef struct TipoGrafo{
	int mat[MaxNumVertices+1][MaxNumVertices+1];
	int numVertices;
	int numArestas;
}TipoGrafo;

typedef struct TipoItem{
	char vertice;
	int peso;
}TipoItem;

typedef struct No{
	TipoItem item;
	struct No *prox;
}No;

/* funcoes para manipular o grafo*/
void FGVazio(TipoGrafo *grafo);
void insereAresta(int v1, int v2, int peso, TipoGrafo *grafo);
short existeAresta(int v1, int v2, TipoGrafo *grafo);
void retiraAresta(int *v1, int *v2, int *peso, TipoGrafo *grafo);
void imprimeGrafo(TipoGrafo *grafo);
/* -- funcoes auxiliares para obter lista de adjacentes -- */
short listaAdjVazia(int v, TipoGrafo *grafo);
int primeiroListaAdj(int v, TipoGrafo * grafo);
void proxAdj(int v, TipoGrafo *grafo, int *adj, int *peso, int *prox, short *fimListaAdj);
/* exercicios */
int grauEntradaGrafo(int v, TipoGrafo *grafo);
int grauSaidaGrafo(int v, TipoGrafo *grafo);

/* Busca em Profundidade */
void visitaDFS(char u, TipoGrafo *grafo, int *tempo, int *d, int *t, char
*cor, char *ant);
void buscaEmProfundidade(TipoGrafo *grafo);

int main(){

	/* Exemplos: */

	TipoGrafo* grafo = (TipoGrafo*) malloc(sizeof(TipoGrafo));
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

	buscaEmProfundidade(grafo);

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

	return 0;
}

/* inicializa matriz de adjacentes com zeros */
void FGVazio(TipoGrafo *grafo){
	int i,j;
	for (i=0; i<=grafo->numVertices; i++)
		for(j=0; j<= grafo->numVertices; j++)
			grafo->mat[i][j]='0';
}

/* Insere o peso na posicao referente a    *
 * linha e coluna dos vertices adjacentes. *
 * Nos exemplos usamos peso 1              */
void insereAresta(int v1, int v2, int peso, TipoGrafo *grafo){
	grafo->mat[v1][v2] = peso;
}

/* retorna verdadeiro (peso > 0) se existe aresta *
 * ligando os dois vertices                       */
short existeAresta(int v1, int v2, TipoGrafo *grafo){
	return grafo->mat[v1][v2]>0;
}

/* retorna verdadeiro se nao tem adjacentes para o *
 * vertice passado como parametro                  */
short listaAdjVazia(int v, TipoGrafo *grafo){
	int result;
	int aux = 0;
	short listaVazia = 1;
	while(aux < grafo->numVertices && listaVazia){
		if(grafo->mat[v][aux]>0){
			result = aux;
			listaVazia = 0;
		}else{
			aux++;
		}
	}
	return (listaVazia==1);
}

/* retorna o primeiro vertice adjacente */
int primeiroListaAdj(int v, TipoGrafo * grafo){
	int result;
	int aux = 0;
	short listaVazia = 1;
	while(aux < grafo->numVertices && listaVazia){
		if(grafo->mat[v][aux]>0){
			result = aux;
			listaVazia = 0;
		}else{
			aux++;
		}
	}
	if(aux==grafo->numVertices)
		printf("Erro! Lista adjacencia vazia (primeiroListaAdj)\n");
	return result;
}

/* Retorna adj apontado por prox*/
void proxAdj(int v, TipoGrafo *grafo, int *adj, int *peso, int *prox, short *fimListaAdj){
	*adj = *prox;
	*peso = grafo->mat[v][*prox];
	(*prox)++;
	while(*prox<grafo->numVertices && grafo->mat[v][*prox]==0){
		(*prox)++;
	}
	if(*prox == grafo->numVertices)
		*fimListaAdj = 1;
}

void retiraAresta(int *v1, int *v2, int *peso, TipoGrafo *grafo){
	if(grafo->mat[*v1][*v2]==0)
		printf("Aresta nao existe \n");
	else {
		*peso = grafo->mat[*v1][*v2];
		grafo->mat[*v1][*v2] = 0;
	}
}

void imprimeGrafo(TipoGrafo *grafo){
	int i,j;
	printf("   ");
	for(i=0; i<grafo->numVertices;i++)
		printf("%3d",i);
	printf("\n");
	for(i=0; i<grafo->numVertices;i++){
		printf("%3d",i);
		for(j=0;j<grafo->numVertices;j++){
			printf("%3d", grafo->mat[i][j]);
		}
		printf("\n");
	}
}

/* Possivel resultado para os exercicios da parte 1 */
int grauEntradaGrafo(int v, TipoGrafo *grafo){
	int i, grau = 0;
	for (i=0;i<grafo->numVertices;i++){
		if (grafo->mat[i][v] != 0){
			grau++;
		}
	}
	return grau;
}

int grauSaidaGrafo(int v, TipoGrafo *grafo){
	int i, grau = 0;
	for (i=0;i<grafo->numVertices;i++){
		if (grafo->mat[v][i] != 0){
			grau++;
		}
	}

	return grau;
}

void visitaDFS(char u, TipoGrafo *grafo, int *tempo, int *d, int *t, char
*cor, char *ant){
	int fimListaAdj;
	int p; //peso
	No *aux;
	char v;
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
	char ant[MaxNumVertices+1];
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
