#include <stdio.h>
#include <stdlib.h>

struct no {
	int dado;
	struct no *prox;
};
typedef struct no No;

No *inicio, *fim;


void enfileirar(int valor) {
    // cria um novo no
	No* novo = (No*)malloc(sizeof(No)); 	
	novo->dado = valor;
    novo->prox = NULL;
	if (inicio == NULL) { // se lista está vazia
		inicio = novo; // novo no será o primeiro elemento da lista
	}
	else { // se lista não estiver vazia
		   // ultimo nó aponta para novo nó
		fim->prox = novo;
	}
	fim = novo; // fim indica um novo nó
}

int desenfileirar(){
	int v = 0;	
	if (inicio==NULL){//verifica se esta vazia
		printf("Fila Vazia! \n"); 
	}else{
		v = inicio->dado;
		inicio = inicio->prox;
	}
	return v;
}

void percorrer () {
    No *atual; // ponteiro para percorrer a fila
	if (inicio==NULL){//verifica se esta vazia
		printf("Fila Vazia! \n"); 
	}else{
    	atual = inicio;
	    printf("\nFila=> ");
    	while (atual != NULL) {
    	    printf("%d \t", atual->dado);
        	atual = atual->prox;
    	}
    	printf("\n");
	}
}


int main(){

	inicio = fim = NULL;

	enfileirar(10);
	percorrer();
	enfileirar(20);
	percorrer();
	desenfileirar();
	percorrer();
	desenfileirar();
	percorrer();

}

