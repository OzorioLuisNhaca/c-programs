#include <stdio.h>
#include <conio.h>

void mtT(int mat[][4], int mtrzTrspst[][4]){
    int i, j;
    for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			mtrzTrspst[i][j] = mat[j][i];
		}
    }
    printf("\nTransposta: \n");
    for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			printf("%d ", mtrzTrspst[i][j]);
		}
		printf("\n");
    }
}
void mtTI(int mat[][4], int mtrTrnglrI[][4]){
    int i, j;

    for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			mtrTrnglrI[i][j] = mat[i][j];
			if (j > i){
				mtrTrnglrI[i][j] = 0;
			}
		}
    }
    printf("\nMatriz Original: \n");
    for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			printf("%d ", mat[i][j]);
		}
		printf("\n");
    }
    printf("\nTriangular Inferior: \n");
    for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			printf("%d ", mtrTrnglrI[i][j]);
		}
		printf("\n");
    }
}
void maioresQueCinco(int mat[][4]){
    int i, j;
    printf("\nMaiores que 5 e menores que 20: \n");
    for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if (mat[i][j] > 5 && mat[i][j] < 20){
				printf("%d  ", mat[i][j]);
			}
		}
    }
}
void maiorCinco(int mat[][4]){
    int i, j, soma = 0;

    for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if (j != i){
				soma += mat[i][j];
			}
		}
    }
    printf("\nSoma dos triangulos: %d", soma);
}
void medDiag(int mat[][4]){
    int i, j, soma = 0, cont = 0;

    for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if ((j + i) == 5 || i == j){
				soma += mat[i][j];
				cont++;
			}
		}
    }
    printf("\nA media dos elementos: %f", (float) soma/cont);
}
void somaColpar(int mat[][4]){
    int i, j, soma = 0;

    for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if (j%2 == 0){
				soma += mat[i][j];
			}
		}
    }
    printf("\nSoma dos elementos das colunas pares: %d", soma);
}
void maiMenLi(int mat[][4]){
    int maior, menor, i, j, c = 0;
    for(i = 0; i < 4; i++){
		maior = mat[i][0];
		menor = mat[i][0];
		for(j = 0; j < 4; j++){
			if (mat[i][j] > maior){
				maior = mat[i][j];
			}
			if (mat[i][j] < menor){
				menor = mat[i][j];
			}
		}
		printf("\n\n%d Linha\nMaior Elemento: %d \n Menor Elemento: %d", ++c, maior, menor);
    }
}

void main(){
    clrscr();
    int mat[4][4] = {{9, 12, 0, 1},{0, 3, 8, 4},{1, -3, 5, 6},{0, -1, 8, -3}},
    mtrzTrspst[4][4],
    mtrTrnglrI[4][4],
    mtrzIde[4][4];

    mtT(mat, mtrzTrspst);
    mtTI(mat, mtrTrnglrI);
    maioresQueCinco(mat);
    maiorCinco(mat);
    medDiag(mat);
    somaColpar(mat);
    maiMenLi(mat);
    getch();
}
