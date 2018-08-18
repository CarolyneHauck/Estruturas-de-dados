#include <stdio.h>

# define TAM 5

float fila[TAM]; //fila propriamente dita
int inicio, //armazena indice do inicio da fila
    fim; //armazena indice do elemento no fim da fila
    
void enqueue (float f[], float valor, int *fim);  
int dequeue (float f[], int *inicio, int *fim, float *valor);  
void mostrar(float f[], int inicio, int fim);
    
int main(){
	float valor;
	//inicializacoes
	inicio = 0;
	fim =-1;	
	valor = 1.0;
	//enfileirar 
	enqueue(fila,valor,&fim);
	mostrar(fila,inicio,fim);
	
	valor = 2.5;
	enqueue(fila,valor,&fim);
	mostrar(fila,inicio,fim);
	
	valor = 3.2;
	enqueue(fila,valor,&fim);
	mostrar(fila,inicio,fim);
	
	valor = 3.0;	
	enqueue(fila,valor,&fim);
	mostrar(fila,inicio,fim);	
	
	//desenfileirar
	dequeue(fila,&inicio,&fim,&valor);	
	mostrar(fila,inicio,fim);		
	
	dequeue(fila,&inicio,&fim,&valor);	
	mostrar(fila,inicio,fim);
	
	valor = 7.3;	
	enqueue(fila,valor,&fim);
	mostrar(fila,inicio,fim);
	
	valor = 5.4;	
	enqueue(fila,valor,&fim);
	mostrar(fila,inicio,fim);		
}    
    
void enqueue (float f[], float valor, int *fim) {
	if ((*fim) == TAM - 1) { // testa fila cheia – é uma operação
		printf("ERRO: Fila cheia.\n");
		return; // sai da função
	}
	(*fim)++; // ajusta fim
	f[(*fim)] = valor; // armazena o valor fim da fila
}    

int dequeue (float f[], int *inicio, int *fim, float *valor) {
	if ((*inicio) > (*fim)) { // testa fila vazia - operação
		printf("ERRO: Fila fazia.\n");
		return 0; // sinaliza fracasso
	}
	(*valor) = f[(*inicio)]; // retira do início
	(*inicio)++; //ajusta o início
	return 1; // sinaliza sucesso
}

void mostrar(float f[], int inicio, int fim){
	int i;
	for(i= inicio; i <= fim; i++){
		printf("[%d] %.2f ", i, f[i]);
	}
	printf("\n");

}
