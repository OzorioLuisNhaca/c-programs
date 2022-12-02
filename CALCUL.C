#include <stdio.h>
#include <conio.h>

float somar(float *x, float b){
	*x = (float) *x + b;
	return *x;
}
float subtrair(float *x, float b){
	*x = (float) *x - b;
	return *x;
}
float multiplicar(float *x, float b){
	*x = (float) *x * b;
	return *x;
}
float dividir(float *x, float b, int *tes){
	if (b != 0){
		*x = (float) *x/b;
		return *x;
	}else{
		*tes = 0;
		*x = 0;
		return *tes;
	}
}

void igual(float *x, float b, float c, int op, int tes){
	int resp;
	printf("\n\n");
	switch(op){
		case 1: printf("%f + %f = %f",c, b, somar(&*x, b)); break;
		case 2: printf("%f - %f = %f",c, b, subtrair(&*x, b)); break;
		case 3: printf("%f * %f = %f",c, b, multiplicar(&*x, b)); break;
		case 4:
			resp = dividir(&*x, b, &tes);
			if (tes == 0)
				printf("Impossivel!");
			else
				printf("%f / %f = %f", c, b, resp);
		break;
	}
}

void main(){
	float n1, n2, aux;
	int escolha, sinal, c = 1, tes;
	clrscr();
	do{
		tes = 1;
		clrscr();
		printf("Calculadora\n\n");
		if (c != 2){
			printf("primeiro numero: ");
			scanf("%f", &n1);
		}
		printf("\n[1]. Adicao [+]\n[2]. Subtracao [-]\n[3]. Multiplicacao [x]\n[4]. Divisao [/]\n");
		scanf("%d", &sinal);
		printf("\nsegundo numero: ");
		scanf("%f", &n2);
		printf("\n[1]. Igual\n[2]. Cancelar\n");
		scanf("%d", &escolha);
		aux = n1;
		if (escolha == 1){
			igual(&n1, n2, aux, sinal, tes);
			printf("\nEsolha uma opcao\n");
			printf("[1]. Continuar\n[2]. Calcular no anterior\n[0]. Sair\n");
			scanf("%d", &c);
			clrscr();
		}

	}while(c == 1 || c == 2);
	getch();
}
