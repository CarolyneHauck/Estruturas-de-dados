#include <stdio.h>

# define TAM 5

float fila[TAM]; //fila propriamente dita
int inicio, //armazena indice do inicio da fila
    fim, //armazena indice do elemento no fim da fila
    nItens; //armazena a quantidade de elementos que existem na fila
    
void enqueue(float f[], float valor, int *fim, int *nItens);  
void dequeue(float f[], int *inicio, int *nItens);
void displayQueue(float f[], int inicio, int fim, int nItens);
    
int main(){
	float valor;
	//inicializacoes
	inicio = 0;
	fim = -1;
	nItens = 0;
	valor = 1.0;
	//enfileirar 
	enqueue(fila,valor,&fim,&nItens);
	displayQueue(fila,inicio,fim,nItens);
	
	valor = 2.5;
	enqueue(fila,valor,&fim,&nItens);
	displayQueue(fila,inicio,fim,nItens);
	
	valor = 3.2;
	enqueue(fila,valor,&fim,&nItens);
	displayQueue(fila,inicio,fim,nItens);
	
	valor = 3.0;	
	enqueue(fila,valor,&fim,&nItens);
	displayQueue(fila,inicio,fim,nItens);
	
	//desenfileirar
	dequeue(fila,&inicio,&nItens);
	displayQueue(fila,inicio,fim,nItens);
	
	dequeue(fila,&inicio,&nItens);
	displayQueue(fila,inicio,fim,nItens);
	
	valor = 7.3;	
	enqueue(fila,valor,&fim,&nItens);
	displayQueue(fila,inicio,fim,nItens);
	
	valor = 5.4;	
	enqueue(fila,valor,&fim,&nItens);
	displayQueue(fila,inicio,fim,nItens);
}    
    
void enqueue (float f[], float valor, int *fim, int *nItens) {
	if (*nItens == TAM) { // testa fila cheia
		printf("ERRO: Fila cheia!\n");
		return; // sai da função
	}
	
	(*fim)++; // ajusta fim
	
	if ((*fim) == TAM) { // estourou o vetor
		(*fim) = 0;
	}
	
	f[(*fim)] = valor; // armazena o valor fim da fila
	(*nItens)++;
}

void dequeue (float f[], int *inicio, int *nItens) {
	if((*nItens) == 0) { // testa se a fila está vazia
		printf("ERRO: Fila fazia.\n");
		return; // sai da função
	}
	
	(*inicio)++; // ajusta o inicio
	
	if((*inicio) == TAM) { // se estourou o vetor...
		(*inicio) = 0; // vai para o primeira posição da fila
	}
	
	(*nItens)--;
}

void displayQueue(float f[], int inicio, int fim, int nItens) {
	if(nItens == 0) { // testa se a fila está vazia
		printf("ERRO: fila vazia!\n");
		return; // sai da função
	}
	
	int cont, i;
	
	for(cont = 0, i = inicio; cont < nItens; cont++) {
		printf("%.2f ", f[i++]);
		
		if(i == TAM)
			i = 0;
	}
	
	printf("\n\n");
}
