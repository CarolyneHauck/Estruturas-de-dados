/*                                 *
 * Implementacao de Lista ordenada *
 *                                 */

#include <stdio.h>
#include <stdlib.h>

typedef int telem; /* tipo base da lista */

typedef struct no {
	telem dado; /* campo da informação */
	struct no* prox; /* campo do ponteiro para o próximo nó */
} tno; /* tipo do nó */

typedef tno* tlistaord; /* tipo lista */

/* cria a lista */
void criar(tlistaord *L)
{
	*L = NULL;
}

/* verifica se a lista esta vazia */
int vazia(tlistaord L)
{
	return (L == NULL);
}

/* retorna o tamanho da lista */
int tamanho(tlistaord L)
{
	tlistaord p = L;
	int n = 0;
	while (p != NULL) {
		p = p->prox;
		n++;
	}
	return n;
}

/* obtem valor do elemento em posicao dada */
int elemento(tlistaord L, int pos, telem *elem)
{
 /* O parâmetro elem irá receber o elemento encontrado */
 /* Retorna 0 se a posição for inválida. Caso contrário, retorna 1 */
	tlistaord p = L;
	int n = 1;
	if (L == NULL) return 0; /* erro: lista vazia */
	while ((p != NULL) && (n < pos)) {
		p = p->prox;
		n++;
	}
	if (p == NULL) return 0; /* erro: posição inválida */
	*elem = p->dado;
	return 1;
}

/* obtem posicao do elemento dado o valor*/
int posicao(tlistaord L, telem valor)
{
/* Retorna a posição do elemento ou 0 caso não seja encontrado */
	if (L != NULL) {
	tlistaord p = L;
	int n = 1;
	while (p != NULL) {
		if (p->dado == valor) return n;
			p = p->prox;
			n++;
		}
	}
 return 0;
}

/* insere elemento na lista */
int inserir(tlistaord *L, telem valor)
{
 /* Retorna 0 se a posição for inválida ou se a lista estiver cheia */
 /* Caso contrário, retorna 1 */
	tlistaord atual, ant, novo;
	int n;
	novo = (tlistaord) malloc(sizeof(tno));
 	if (novo == NULL) return 0; /* erro: memória insuficiente */
 	novo->dado = valor;
	novo->prox = NULL;
	ant = NULL;
	atual = *L;
	while (atual != NULL && valor >= atual->dado) {
 		if (atual->dado == valor) return 0; /* erro: valor já existente */
		ant = atual;
		atual = atual->prox;
 	}
	if (ant == NULL) {
		novo->prox = *L;
		*L = novo;
 	}else {
		ant->prox = novo;
		novo->prox = atual;
 	}
 	return 1;
}

/* remove elemento de determinada posicao*/
int remover(tlistaord *L, int pos, telem *elem)
{
 /* O parâmetro elem irá receber o elemento encontrado */
 /* Retorna 0 se a posição for inválida. Caso contrário, retorna 1 */
 	tlistaord a, p;
 	int n;
 	if (vazia(*L)) return 0; /* erro: lista vazia */
 	p = *L;
 	n = 1;
	while ((n<=pos-1) && (p!=NULL)) {
		a = p;
 		p = p->prox;
 		n++;
 	}
 	if (p == NULL) return 0; /* erro: posição inválida */
 	*elem = p->dado;
 	if (pos == 1)
 		*L = p->prox;
 	else
 		a->prox = p->prox;
 	free(p);
	return(1);
}

void exibe(tlistaord* L){
	tno* q;
	for (q=L; q!=NULL;q=q->prox)
		printf("%d\t",q->dado);
	printf("\n");
}

void preenche(tlistaord* l1, tlistaord* l2, tlistaord** l3){
	int tam1 = tamanho(l1), tam2 = tamanho(l2), i;
	telem valor;
 	for(i = 0 ; i <= tam1; i++){
		elemento(l1,i,&valor);		
		inserir(l3, valor);
	}
 	for(i = 0 ; i <= tam2; i++){
		elemento(l2,i,&valor);		
		inserir(l3, valor);
	}
}

int main(){
	tlistaord* l1, l2, l3;
	// cria a primeiram lista
	criar(&l1);
	inserir(&l1,10);
	inserir(&l1,1);
	inserir(&l1,5);
	printf("Lista 1:\n");
	exibe(l1);
	// cria a segunda lista
	criar(&l2);
	inserir(&l2,2);
	inserir(&l2,15);
	inserir(&l2,8);
	printf("Lista 2:\n");
	exibe(l2);
	// cria na terceira lista
	criar(&l3);
	preenche(l1,l2,&l3);
	printf("Lista 3:\n");
	exibe(l3);

}

/*int main(){
	tlistaord* l;
	criar(&l);
	inserir(&l,10);
	exibe(l);
	inserir(&l,1);
	exibe(l);
	inserir(&l,5);
	exibe(l);
}*/
