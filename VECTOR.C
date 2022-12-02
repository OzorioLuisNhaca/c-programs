#include <stdio.h>
#include <conio.h>

void numerosPares(int numeros[]){
	int i;
	printf("Numeros pares: ");
	for(i = 0; i < 4; i++){
		if(numeros[i]%2 == 0)
			printf("%d  ", numeros[i]);
	}
}
void numerosImpares(int numeros[]){
	int i;
	printf("\nNumeros impares: ");
	for(i = 0; i < 4; i++){
		if(numeros[i]%2 != 0)
			printf("%d  ", numeros[i]);
	}
}
void numerosPrimos(int numeros[]){
	int i, j, multiplos = 0;
	printf("\nNumeros primos: ");
	for(i = 0; i < 4; i++){
		for(j = 1; j <= numeros[i]; j++){
			if (numeros[i]%j == 0)
				multiplos++;
		}
		if (multiplos == 2)
			printf("%d  ", numeros[i]);
		multiplos = 0;
	}
}
void somaAntesImpar(int numeros[]){
	int soma = 0, i;
	for(i = 0; i < 4; i++){
		if(numeros[i+1]%2 != 0 && numeros[i]%2 == 0){
			printf("%d ", numeros[i]);
			soma += numeros[i];
		}
	}
	printf("\nSoma dos numeros pares antes dos impares: %d\n", soma);
}
void mudaParaZero(int numeros[], int vector[]){
	int i;
	for(i = 0; i < 4; i++){
		vector[i] = numeros[i];
		if(numeros[i-1] > 0 && numeros[i] < 0){
			vector[i] = 0;
		}
	}
	printf("Vector antes da substituicao: [");
	for(i = 0; i < 4; i++){
		printf("%d   ", numeros[i]);
	}
	printf("]\n");
	printf("Vector depoiss da substituicao: [");
	for(i = 0; i < 4; i++){
		printf("%d   ", vector[i]);
	}
	printf("]\n");
}
void media(int numeros[]){
	int i, soma = 0, cont = 0;
	for(i = 0; i < 4; i++){
		if(numeros[i] > 10 && numeros[i]%3 == 0){
			soma += numeros[i];
			cont++;
		}
	};
	printf("Media dos numeros divisiveis por 3 maiores que 10: %d\n",  soma/cont);
}
void aumentaNumero(int numeros[]){
	int i, soma;
	printf("\nUmenta numero: ");
	for(i = 0; i < 4; i++){
		if(i%2 == 0 && i < 25)
			numeros[i] += i*2;
	}
	printf("Novo vector: [");
	for(i = 0; i < 4; i++){
		printf("%d   ", numeros[i]);
	}
	printf("]\n");
}
void inverteVector(int primeiroVctr[], int segundoVctr[], int smVctr[]){
	int i, index = 0;
	for (i = 3; i >= 0; i--){
		segundoVctr[index] = primeiroVctr[i];
		index++;
	}
	for(i = 0; i < 4; i++){
		smVctr[i] = primeiroVctr[i] + segundoVctr[i];
	}
	printf("Resultado da soma: [");
	for(i = 0; i < 4; i++){
		printf("%d   ", smVctr[i]);
	}
	printf("]\n");

}
void maiorMenorElemento(int vector[]){
	int i, maior = vector[0], menor = vector[0];
	for(i = 0; i < 4; i++){
		if (vector[i] > maior)
			maior = vector[i];
		if (vector[i] < menor)
			menor = vector[i];
	}
	printf("Maior elemento: %d  Menor elemento: %d  \n", maior, menor);
}
void segundoMaior(int vector[]){
	int maior = vector[0], segundoMaior = vector[0], i;
	for(i = 0; i < 4; i++){
		if (vector[i] > segundoMaior){
			segundoMaior = vector[i];
			if (vector[i] > maior){
				segundoMaior = maior;
				maior = vector[i];
			}
		}
	}
	printf("Segundo maior elemento: %d  \n", segundoMaior);
}

void main(){
	int numeros[4] = {5, -7, 4, 15}, vetorInverso[4], crescente[4], decrescente[4], somaVectores[4], decrecente[4], vetorComZero[4];
	clrscr();
	vectorBase(numeros);
	numerosPares(numeros);
	numerosImpares(numeros);
	numerosPrimos(numeros);
	somaAntesImpar(numeros);
	mudaParaZero(numeros, vetorComZero);
	media(numeros);
	inverteVector(numeros, vetorInverso, somaVectores);
	maiorMenorElemento(somaVectores);
	segundoMaior(somaVectores);
	getch();
}