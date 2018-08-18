#include <stdio.h>
#include <string.h>

typedef struct data {
	
	int dia;
	int mes;
	int ano;
	
} Data;

Data entradaData(int, int, int); // entrada de dados   (protótipo)
void saidaData(Data);   		 // saída de dados     (protótipo)
int validaData(Data);   		 // validação de dados (protótipo)

int main() {
	
	Data dt;
	
	int dia;
	int mes;
	int ano;
	
	printf("DD/MM/AA: ");
	scanf("%2d/%2d/%2d", &dia, &mes, &ano);
	
	dt = entradaData(dia, mes, ano);
	
	if (validaData(dt)) {
		
		printf("Data: %02d/%02d/20%02d", dt.dia, dt.mes, dt.ano);
	
	}
	else {
		
		printf("Data invalida!!!");
		
	}
}

int validaData(Data dt) {
	
	int flag = 1;
	
	// 0 -> data inválida
	// 1 -> data válida
	
	if (dt.dia < 1 || dt.dia > 31)
		flag = 0;
		
	else if (dt.mes < 1 || dt.mes > 12)
		flag = 0;
		
	else if (dt.ano < 0)
		flag = 0;
		
	else if (dt.mes == 2 && dt.dia > 29)
		flag = 0;
		
	else if (dt.dia == 31 && (dt.mes == 4 || dt.mes == 6 ||
		dt.mes == 9 || dt.mes == 11))
		flag = 0;
		
	return flag;
	
}

Data entradaData(int dia, int mes, int ano) {
	
	Data dt;
	dt.dia = dia;
	dt.mes = mes;
	dt.ano = ano;
	
	return dt;
	
}
