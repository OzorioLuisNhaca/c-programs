#include <stdio.h>
#include <conio.h>

void cadAl(char nme[32], int *numaluno){
    int quantAl, i, cadastrou = 1;
    clrscr();
    do{
        printf("Numero de alunos a cadastrar: ");
        scanf("%d", &quantAl);
        if ((quantAl + *numaluno) > 10){
            printf("Numero de alunos excedeu o limite %d\n", quantAl);
            cadastrou = 0;
        }else{
            cadastrou = 1;
        }
    }while(!cadastrou);
    clrscr();
    for(i = *numaluno; i < (*numaluno + quantAl); i++){
        printf("Nome do estudante: ");
        scanf("%s", &nm[i]);
    }
    *numaluno += quantAl;
}
void lancN(float t[][3], char nme[32], int numaluno){
    int i, j, cont = 0;
    for (i = 0; i < numaluno; i++){
        printf("Notas de %s: \n", nm[i]);
        for(j = 0; j < 3; j++){
            printf("%do. nota: ", ++cont);
            scanf("%f", &t[i][j]);
        }
        cont = 0;
        clrscr();
    }
}
void pauta(char nme[32], float t[][3], int numaluno){
    int i, cont = 0, totAprov = 0, totRep = 0, mest;
    float media, maiorMedia = 0;
    clrscr();
    printf("=========================== Puta ===========================\n\n");
    printf("N nome\tt1\tt2\tt3\tmedia\tclassificacao\n");
    for(i = 0; i < numaluno; i++){
        media = (float) (t[i][0] + t[i][1] + t[i][2])/3;
        if (media > maiorMedia){
            maiorMedia = media;
            mest = i;
        }
	if (media >= 10){
	    totAprov++;
	    printf("%d %s\t%.1f\t%.1f\t%.1f\t%.1f\t%s\n", ++cont, nm[i], t[i][0], t[i][1], t[i][2], media, "Aprovado");
	}else{
	    totRep++;
	    printf("%d %s\t%.1f\t%.1f\t%.1f\t%.1f\t%s\n", ++cont, nm[i], t[i][0], t[i][1], t[i][2], media, "Reprovado");
	}
    }
    printf("\nTotal aprovados: %d\n", totAprov);
    printf("Total reprovados: %d\n", totRep);
    printf("Melhor Estudante: %s\n", nm[mest]);
}

void main(){
    clrscr();
    char nome [10][32];
    float t[10][3];
    int numaluno = 0, naoSair;
    do{
        printf("\n[1]. CADASTRAR ESTUDANTES\n");
        printf("[2]. LANCAR NOTAS\n");
        printf("[3]. VER PAUTA\n");
        printf("[0]. SAIR\n");
        printf("Ocao: ");
        scanf("%d", &naoSair);
        clrscr();
        switch (naoSair){
            case 1: cadAl(nome, &numaluno); break;
            case 2: lancN(t, nome, numaluno); break;
            case 3: pauta(nome, t, numaluno); break;
            default: printf("Invalido"); break;
            clrscr();
            printf("Opcao Invalida!...");
            break;
        }
    }while(naoSair == 1);
    clrscr();
    getch();
}
