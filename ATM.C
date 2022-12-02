#include <stdio.h>
#include <conio.h>

void deposito(float sld[], int id, float dpst[][20], int qtdTrsces[][3]);
void levantamento(float sld[], int id, float lvntmnt[][20], int qtdTrsces[][3], float tx);
void transferencia(int nmCntaRec[], float sld[], int id, float trsfrcia[][20], int qtdTrsces[][3], float tx);
void verSaldo(float sld);
void historico(float dpst[][20], float lvntmnt[][20], float trsfrcia[][20], int id, int qtdTrsces[][3]);
void usersDataBase();
void entrar(int nmCnt[], char nm[][32], int senha[], float sld[], float trsfrcia[][20], float dpst[][20], float lvntmnt[][20]);
void transacoes(char nm[]);

void main(){
	clrscr();
	usersDataBase();
	getch();
}
void usersDataBase(){
	int numeroDaConta[] = {
		128252,
		128447,
		128453
	};
	char nome[][32] = {
		"Ozorio De Brito Luis Nhaca",
		"Luis Gungo Nhaca",
		"Dercia Americo Sambo"
	};
	int senha[] = {
		8252,
		8447,
		8453
	};
	float saldo[] = {
		100,
		100,
		100
	};
	float transferencias[][20] = {
		{2345},
		{674},
		{3353}
	};
	float depositos[][20] = {
		{0},
		{0},
		{0}
	};
	float levantamentos[][20] = {
		{0},
		{0},
		{0}
	};

	entrar(numeroDaConta, nome, senha, saldo, transferencias, depositos, levantamentos);
}

void entrar(int ndCnta[], char nm[][32], int senha[], float sld[], float trsfrcia[][20], float dpst[][20], float lvntmnt[][20]){
	int sair = 0, qtdTentativas = 0, userId = -1, i, psswdCorrecto = 0, transacao, psswd;
	const float TAXA = 8;
	int qtdTransacoes[][3] = {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	};
	do{
		do{
			printf("Digite a sua senha: ");
			scanf("%d", &psswd);
			for (i = 0; i < 3; i++){
				if (psswd == senha[i]){
					userId = i;
					psswdCorrecto = 1;
					qtdTentativas = 3;
					break;
				}
			}
			if (!psswdCorrecto){
				printf("SENHA INCORRECTA! TENTE NOVAMENTE!...\n");
			}
			qtdTentativas++;
		}while(qtdTentativas < 3);

		if (psswdCorrecto){
			transacoes(nm[userId]);
			scanf("%d", &transacao);
			clrscr();
			switch(transacao){
				case 1: deposito(sld, userId, dpst, qtdTransacoes); break;
				case 2: levantamento(sld, userId, lvntmnt, qtdTransacoes, TAXA); break;
				case 3: transferencia(ndCnta, sld, userId, lvntmnt, qtdTransacoes, TAXA); break;
				case 4: historico(dpst, lvntmnt, trsfrcia, userId, qtdTransacoes); break;
				case 5: verSaldo(sld[userId]); break;
			}
			psswdCorrecto = 0;
			qtdTentativas = 0;
		}else{
			printf("\nEXCEDEU O NUMERO DE TENTATIVAS DA SENHA. O SEU CARTAO FOI BLOQUEADO!");
			sair = 1;
		}
		if(!sair){
			printf("\n[1]. SAIR\n[0]. EFECTUAR OUTRA TRANSACAO\nOpcao: ");
			scanf("%d", &sair);
			clrscr();
		}
	}while(!sair);
}
void transacoes(char nm[]){
	clrscr();
	printf("\t=================== BEM VINDO A UPBANK ======================\n");
	printf("\n\tNOME DO CLIENTE: %s\n\n", nm);
	printf("\tOPERACOES COM A SUA CONTA\n\n");
	printf("\t[1]. DEPOSITAR\n\t[2]. LEVANTAR DINHEIRO\n\t[3]. TRANFERIR\n\t[4]. VER HISTORICO\n\t[5]. Ver saldo");
	printf("\n\tEscolha a opcao: ");
}
void deposito(float sld[], int id, float dpst[][20], int qtdTrsces[][3]){
	float valor;
	clrscr();
	do{
		printf("Valor a depositar: ");
		scanf("%f", &valor);
		if(valor <= 0){
			clrscr();
			printf("Operacao Invalida...\n\n");
		}
	}while(valor <= 0);
	dpst[id][qtdTrsces[id][0]++] = valor;
	sld[id] = sld[id] + valor;

	printf("Deposito de %.2f MZN efectuado com sucesso!\nO seu novo saldo e %.2f MZN", valor, sld[id]);
}
void levantamento(float sld[], int id, float lvntmnt[][20], int qtdTrsces[][3], float tx){
	float valor;
	int levantou = 1, tentativas = 0;
	clrscr();
	do{
		printf("Valor a levantar: ");
		scanf("%f", &valor);
		if(valor <= 0){
			clrscr();
			printf("Operacao Invalida...");
			levantou = 0;
		}else{
			if ((valor + tx) > sld[id]){
				printf("\nO Seu saldo e insuficiente!\n");
				levantou = 0;
			}else{
				tentativas = 2;
			}
		}
		tentativas++;
	}while(tentativas < 3);
	if (levantou){
		lvntmnt[id][qtdTrsces[id][1]++] = valor;
		sld[id] = sld[id] - valor;
		printf("Levantamento de %.2f MZN efectuado com sucesso!\nO Seu novo saldo e %.2f MZN", valor, sld[id]);
	}
}
void transferencia(int nmCntaRec[], float sld[], int id, float trfrcia[][20], int qtdTrsces[][3], float tx){
	int tentativas = 0, nmCnt, transferiu = 0, i;
	float valor;
	do{
		printf("Valor a transferir: ");
		scanf("%f", &valor);
		printf("Numero da conta: ");
		scanf("%d", &nmCnt);
		if (valor <= 0){
			printf("\nOperacao Invalida...!\n");
		} else if ((valor + tx) > sld[id]){
			printf("\nO Seu saldo e insuficiente...\n");
			transferiu = 0;
		}else{
			for (i = 0; i < 3; i++){
				if (nmCnt == nmCntaRec[i]){
					transferiu = 1;
					tentativas = 2;
					break;
				}
			}
			if (!transferiu){
				clrscr();
				printf("Numero de conta invalida! Tente novamente\n");
			}
		}
		tentativas++;
	}while(tentativas < 3);
	if (transferiu){
		trfrcia[id][qtdTrsces[id][2]++] = valor;
		sld[id] = sld[id] - valor;
		sld[i] = sld[i] + valor;
	}
}
void verSaldo(float sld){
	clrscr();
	printf("Saldo da Sua conta: %.2f MZN\n", sld);
}
void historico(float dpst[][20], float lvntmnt[][20], float trsfrcia[][20], int id, int qtdTrsces[][3]){
	float maiorLvntmnt = 0.0, menorTrsfrcia = 11000000.0;
	int i;
	printf("\t=================== HISTORICO DAS TRANSACOES DO CLIENTE =============\n");
	printf("\n\tNumero de depositos: %d\n", qtdTrsces[id][0]);
	for(i = 0; i <= qtdTrsces[id][1]; i++){
		if (lvntmnt[id][i] > maiorLvntmnt){
			maiorLvntmnt = lvntmnt[id][i];
		}
	}
	for(i = 0; i <= qtdTrsces[id][2]; i++){
		if (trsfrcia[id][i] < menorTrsfrcia){
			menorTrsfrcia = trsfrcia[id][i];
		}
	}
	printf("\tMaior levantamento: %.2f MZN\n", maiorLvntmnt);
	printf("\tMenor transferencia: %.2f MZN\n", menorTrsfrcia);
}
