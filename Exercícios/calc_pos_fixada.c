#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha_com_lista.h"

struct calc{
	char f[21]; /*formato para impressão*/
	Pilha* p;   /*pilha de operandos*/
};
typedef struct calc Calc;


/*funções*/

Calc* calc_cria(char* f);
void calc_operando(Calc* c, float v);
void calc_operador(Calc* c, char op);
void calc_libera(Calc* c);

int main(){
	char c;
	float v;
	Calc* calc;
	
	/*cria calculadora com formato de duas casas decimais*/
	calc = calc_cria("%.2f\n");

	do{
		/*le proximo caractere nao branco*/
		scanf(" %c", &c);
		/*verifica se é operador valido*/
		if(c=='+'||c=='-'||c=='*'||c=='/'){
			calc_operador(calc,c);
		}
		/*devolve caractere lido e tenta ler numero*/
		else{
			ungetc(c,stdin);
			if(scanf("%f",&v)==1)
				calc_operando(calc,v);
		}
	}while(c!='q');
	calc_libera(calc);
	return 0;
}

Calc* calc_cria(char* formato){
	Calc* c = (Calc*) malloc(sizeof(Calc));
	strcpy(c->f, formato);
	c->p = pilha_cria();/*cria pilha vazia*/
	return c;
} 

void calc_operando(Calc* c, float v){
	/*empilha operando*/
	pilha_push(c->p,v);
	/*imprime topo da pilha*/
	printf(c->f,v);
}

void calc_operador(Calc* c, char op){
	float v1, v2, v;
	/*desempilha operandos*/
	if (pilha_vazia(c->p))
		v2 = 0.0;
	else
		v2 = pilha_pop(c->p);
	if (pilha_vazia(c->p))
		v1 = 0.0;
	else
		v1 = pilha_pop(c->p);
	
	/*faz operação*/
	switch(op){
		case '+': v = v1+v2; break;
		case '-': v = v1-v2; break;
		case '*': v = v1*v2; break;
		case '/': v = v1/v2; break;	
	}
	/*empilha resultado*/
	pilha_push(c->p, v);

	/*imprime topo da pilha*/
	printf(c->f,v);
}

void calc_libera(Calc* c){
	pilha_libera(c->p);
	free(c);
}
