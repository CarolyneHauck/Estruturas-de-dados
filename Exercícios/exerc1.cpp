#include <stdio.h>
typedef struct data { // Data == struct data
	int dia;
	int mes;
	int ano;
} Data;

Data entradaData(int, int, int); // entrada de dados (protótipo)
void saidaData(Data);   // saída de dados (protótipo)
int verificaData(Data); // verifica se data válida

int main() {
	int dia, mes, ano;
	Data hoje;
	printf("DD/MM/AA: ");
	scanf("%2d/%2d/%2d",&dia,&mes,&ano);
	hoje = entradaData(dia,mes,ano);
	if(verificaData(hoje)) {
		printf("Hoje: ");
		saidaData(hoje);
	} else
		printf("Data invalida.");
}

Data entradaData(int d, int m, int a) {
	Data data; // cria uma variável do tipo Data
	data.dia = d;  // aloca valor no campo dia
	data.mes = m;
	data.ano = a;
	return data;  // retorna a variável data (tipo Data)
}

void saidaData(Data dt) {
	printf("%02d/%02d/20%02d",
		dt.dia,dt.mes,dt.ano);
}

int verificaData(Data dt) {
	int teste = 1;
	// 0 -> data invalida; 1 -> data valida
	if(dt.dia<1 || dt.dia>31)
		teste=0;
	else if(dt.mes<1 || dt.mes>12)
		teste=0;
	else if(dt.ano<0)
		teste=0;
	else if(dt.mes==2 && dt.dia>29)
		teste=0;
	else if(dt.dia==31 && (dt.mes==4 || dt.mes==6 ||
	    dt.mes==9 || dt.mes==11))
	    teste=0;
	return teste;	
}
