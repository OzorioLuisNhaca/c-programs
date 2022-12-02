#include <stdio.h>
#include <conio.h>
#include <string.h>


typedef struct{
	int id;
	char disciplina[32];
}Disciplina;
typedef struct{
	Disciplina disciplina;
	float notas[3];
}Pauta;
typedef struct{
	char cidade[32];
	char avenida[32];
	int numeroDacasa;
}Endereco;
typedef struct{
	int id;
	char departamento[32];
}Departamento;
typedef struct{
	int id;
	char faculdade[32];
}Faculdade;
typedef struct{
	int username;
	int senha;
	int codigoDoUsuario;
	char nome[32];
	int dataDeNascimento[3];
	Faculdade faculdade;
	Departamento departamento;
	Endereco endereco;
}Usuario;
typedef struct{
	Disciplina disciplina;
	char grau[32];
}Docente;
typedef struct{
	char curso[32];
	Pauta pauta[4];
}Estudante;
typedef struct{
	char areaDeFormacao[32];
}Tecnico;

//Funcoes a serem executadas pelo sistema

void cadastrarUsuario(Usuario *usuario, Usuario user, int *totalUsuarios, int qtdUsuarios, int codigo, Faculdade *faculdade, Departamento *departamento, FILE *arquivoUsuarios);
void cadastrarDocente(Usuario *usuario, Usuario user, Docente *docente, int codigo, int *totalUsuarios, int *totalDocentes, int *id, Faculdade *faculdade, Departamento *departamento, Disciplina *disciplina, FILE *arquivoUsuarios, FILE *arquivoDocentes);
void cadastrarEstudante(Usuario *usuario, Usuario user, Estudante *estudante, Docente *docente, int codigo, int *totalUsuarios, int *totalEstudantes, int totalDocentes, Faculdade *faculdade, Departamento *departamento, Disciplina *disciplina, FILE *arquivoUsuarios, FILE *arquivoEstudantes);
void cadastrarTecnico(Usuario *usuario, Usuario user, Tecnico  *tecnico, int codigo, int *totalUsuarios, int *totalTecnicos, Faculdade *faculdade, Departamento *departamento, FILE *arquivoUsuarios, FILE *arquivoTecnicos);
void mostrarUsuarios(Usuario *usuario, Usuario user, int totalUsuarios, FILE *arquivoUsuarios);
void pesquisarUsuario(Usuario *usuario, Usuario user, int totalUsuarios, FILE *arquivoUsuarios);
void lancarNotas(Usuario *usuario, Usuario user, Estudante *estudante, Estudante estudant, Docente *docente, Docente docent, int totalUsuarios, int docenteId, FILE *arquivoUsuarios, FILE *arquivoDocentes, FILE *arquivoEstudantes, FILE *pauta);
void verPauta(Usuario *usuario, Usuario user, Estudante *estudante, Estudante estudant, Docente *docente, Docente docent, int totalUsuarios, int totalDocentes, int totalEstudantes, int usuarioId, int codigo, FILE *arquivoUsuarios, FILE *arquivoDocentes, FILE *arquivoEstudantes, FILE *pauta);
void estatisticas(Estudante *estudante);
void dataBase();
void listaDeDisciplinas(Disciplina *disciplina);
void login(Usuario *usuario, Usuario user, Docente *docente, Docente docent, Estudante *estudante, Estudante estudant, Tecnico *tecnico, Faculdade *faculdade, Departamento *departamento, Disciplina *disciplina, FILE *arquivoUsuarios, FILE *arquivoDocentes, FILE *arquivoEstudantes, FILE *arquivoTecnicos, FILE *pauta);
void opcoes(int codigo, char *nomeDoUsuario, char *tipoDeUsuario);
void inicio(int username, Usuario *usuario, Usuario user, Docente *docente, Docente docent, Estudante *estudante, Estudante estudant, Tecnico *tecnico, Faculdade *faculdade, Departamento *departamento, Disciplina *disciplina, FILE *arquivoUsuarios, FILE *arquivoDocentes, FILE *arquivoEstudantes, FILE *arquivoTecnicos, FILE *pauta);

void main(){
	clrscr();
	dataBase();
	getch();
}
void dataBase(){

	FILE *arquivoUsuarios;
	FILE *arquivoDocentes;
	FILE *arquivoEstudantes;
	FILE *arquivoTecnicos;
	FILE *pauta;

	Usuario user;
	Docente docent;
	Estudante estudant;
	Usuario usuario[20];
	Docente docente[5];
	Estudante estudante[10] = {
		"Engenharia Informatica", {1, "Programacao Imperativa", {19, 20, 20}},
		"Engenharia Informatica", {1, "Programacao Imperativa", {16, 9, 19}},
		"Engenharia Informatica", {1, "Programacao Imperativa", {16, 9, 19}},
	};
	Tecnico tecnico[5];
	Faculdade faculdade[5] = {
		1, "FET",
		2, "FCNM",
		3, "FCL",
		4, "FCSF",
		5, "FEP"
	};
	Departamento departamento[4] = {
		1, "Informatica",
		2, "Matematica",
		3, "Engenharia Electronica",
		4, "Fisica"
	};
	Disciplina disciplina[5] = {
		1, "Programacao Imperativa",
		2, "PTP-1",
		3, "Calculo Integral",
		4, "Filosofia Africana",
		5, "Algebra Linear"

	};
	login(usuario, user, docente, docent, estudante, estudant, tecnico, faculdade, departamento, disciplina, &arquivoUsuarios, &arquivoDocentes, &arquivoEstudantes, &arquivoTecnicos, &pauta);
}
void login(Usuario *usuario, Usuario user, Docente *docente, Docente docent, Estudante *estudante, Estudante estudant, Tecnico *tecnico, Faculdade *faculdade, Departamento *departamento, Disciplina *disciplina, FILE *arquivoUsuarios, FILE *arquivoDocentes, FILE *arquivoEstudantes, FILE *arquivoTecnicos, FILE *pauta){
	int username, senha, tentativas = 0, i, entrou = 0;
	arquivoUsuarios = fopen("usuarios.txt", "r");
	if(arquivoUsuarios != NULL){
		while(tentativas < 3){
			clrscr();
			printf("\n============================== LOGIN ==================================\n");
			printf("Digite o seu username: ");
			scanf("%d", &username);
			printf("Digite a sua senha: ");
			scanf("%d", &senha);
			while(fread(&user, sizeof(Usuario), 1, arquivoUsuarios)){
				if(username == user.username && senha == user.senha){
					tentativas = 3;
					entrou = 1;
				}
			}
			tentativas++;
		}
		clrscr();
		if(entrou){
			inicio(username, usuario, user, docente, docent, estudante, estudant, tecnico, faculdade, departamento, disciplina, &arquivoUsuarios, &arquivoDocentes, &arquivoEstudantes, &arquivoTecnicos, &pauta);
		}else{
			printf("Excedeu o numero de tentativas maxima! A sua conta foi bloqueiada.");
		}
		fclose(arquivoUsuarios);
	}
}
void inicio(int username, Usuario *usuario, Usuario user, Docente *docente, Docente docent, Estudante *estudante, Estudante estudant, Tecnico *tecnico, Faculdade *faculdade, Departamento *departamento, Disciplina *disciplina, FILE *arquivoUsuarios, FILE *arquivoDocentes, FILE *arquivoEstudantes, FILE *arquivoTecnicos, FILE *pauta){
	int naoSair, i, codigo, totalUsuarios = 3, totalDocentes = 1, totalEstudantes = 1, totalTecnicos = 1, idDisciplina = 1;
	char tipoDeUsuario[10], name[32];
	arquivoUsuarios = fopen("usuarios.txt", "r");
	while(fread(&user, sizeof(Usuario), 1, arquivoUsuarios)){
		if(username == user.username){
			codigo = user.codigoDoUsuario;
			strcpy(name, user.nome);
			break;
		}
	}

	if(codigo == 1212)
		strcpy(tipoDeUsuario, "Tecnico");
	else if(codigo == 1122)
		strcpy(tipoDeUsuario, "Docente");
	else if(codigo == 2211)
		strcpy(tipoDeUsuario, "Estudante");
	do{
		opcoes(codigo, name, tipoDeUsuario);
		printf("Escolha a opcao: ");
		scanf("%d", &naoSair);
		clrscr();
		switch(naoSair){
			case 1: cadastrarDocente(usuario, user, docente, 1122, &totalUsuarios, &totalDocentes, &idDisciplina, faculdade, departamento, disciplina, &arquivoUsuarios, &arquivoDocentes); break;
			case 2: cadastrarEstudante(usuario, user, estudante, docente, 2211, &totalUsuarios, &totalEstudantes, totalDocentes, faculdade, departamento, disciplina, &arquivoUsuarios, &arquivoEstudantes); break;
			case 3: cadastrarTecnico(usuario, user, tecnico, 1212, &totalUsuarios, &totalTecnicos, faculdade, departamento, &arquivoUsuarios, &arquivoTecnicos); break;
			case 4: mostrarUsuarios(usuario, user, totalUsuarios, &arquivoUsuarios); break;
			case 5: pesquisarUsuario(usuario, user, totalUsuarios, &arquivoUsuarios); break;
			case 6: lancarNotas(usuario, user, estudante, estudant, docente, docent, totalUsuarios, username, &arquivoUsuarios, &arquivoDocentes, &arquivoEstudantes, &pauta); break;
			case 7: verPauta(usuario, user, estudante, estudant, docente, docent, totalUsuarios, totalDocentes, totalEstudantes, username, codigo, &arquivoUsuarios, &arquivoDocentes, &arquivoEstudantes, &pauta); break;
			case 8: estatisticas(estudante); break;
			case 9: verPauta(usuario, user, estudante, estudant, docente, docent, totalUsuarios, totalDocentes, totalEstudantes, username, codigo, &arquivoUsuarios, &arquivoDocentes, &arquivoEstudantes, &pauta); break;
			case 10: estatisticas(estudante); break;
			case 11: naoSair = 11; break;
			default: printf("Escolha invalida!\n\n"); break;
		}
	}while(naoSair && naoSair != 11);
	clrscr();
	if(naoSair == 11){
		login(usuario, user, docente, docent, estudante, estudant, tecnico, faculdade, departamento, disciplina, &arquivoUsuarios, &arquivoDocentes, &arquivoEstudantes, &arquivoTecnicos, pauta);
	}else{
		printf("SAIU DO SISTEMA...");
	}
}

void listaDeDisciplinas(Disciplina *disciplina){
	int i;
	printf("\n========================= Lista de Cadeiras ========================\n\n");
	for(i = 0; i < 5; i++){
		printf("[%d]. %s\n", (*(disciplina + i)).id, (*(disciplina + i)).disciplina);
	}
}
void cadastrarDocente(Usuario *usuario, Usuario user, Docente *docente, int codigo, int *totalUsuarios, int *totalDocentes, int *id, Faculdade *faculdade, Departamento *departamento, Disciplina *disciplina, FILE *arquivoUsuarios, FILE *arquivoDocentes){
	int qtdUsuarios, i;
	arquivoDocentes = fopen("docentes.txt", "a");
	printf("Numero de docentes a cadastrar: ");
	scanf("%d", &qtdUsuarios);

	cadastrarUsuario(usuario, user, &*totalUsuarios, qtdUsuarios, codigo, faculdade, departamento, &arquivoUsuarios);
	for(i = 0; i < qtdUsuarios; i++){	
		printf("Disciplina: ");
		listaDeDisciplinas(disciplina);
		scanf("%s", &(*(docente + i)).disciplina.id);
		strcpy((*(docente + i)).disciplina.disciplina, (*(disciplina + ((*(docente + i)).disciplina.id - 1))).disciplina);
		printf("Grau academico: ");
		scanf("%s", &(*(docente + i)).grau);
		fwrite(&(*(docente + i)), sizeof(Docente), 1, arquivoDocentes);
	}
	fclose(arquivoDocentes);
	clrscr();
}
void cadastrarEstudante(Usuario *usuario, Usuario user, Estudante *estudante, Docente *docente, int codigo, int *totalUsuarios, int *totalEstudantes, int totalDocentes, Faculdade *faculdade, Departamento *departamento, Disciplina *disciplina, FILE *arquivoUsuarios, FILE *arquivoEstudantes){
	int qtdUsuarios, i, j;
	arquivoEstudantes = fopen("estudant.txt", "a");
	printf("Numero de estudantes a cadastrar: ");
	scanf("%d", &qtdUsuarios);

	cadastrarUsuario(usuario, user, &*totalUsuarios, qtdUsuarios, codigo, faculdade, departamento, &arquivoUsuarios);
	for(i = 0; i < qtdUsuarios; i++){
		printf("Curso: ");
		scanf("%s", &(*(estudante + i)).curso);
		listaDeDisciplinas(disciplina);
		for(j = 0; j < totalDocentes; j++){
			printf("Cadeira-%d: ", j+1);
			scanf("%d", &(*(estudante + i)).pauta[j].disciplina.id);
		}
		fwrite(&(*(estudante + i)), sizeof(Estudante), 1, arquivoEstudantes);
	}
	fclose(arquivoEstudantes);
	clrscr();

}

void cadastrarTecnico(Usuario *usuario, Usuario user, Tecnico  *tecnico, int codigo, int *totalUsuarios, int *totalTecnicos, Faculdade *faculdade, Departamento *departamento, FILE *arquivoUsuarios, FILE *arquivoTecnicos){
	int qtdUsuarios, i, j;
	arquivoTecnicos = fopen("tecnicos.txt", "a");
	printf("Numero de tecnicos a cadastrar: ");
	scanf("%d", &qtdUsuarios);

	cadastrarUsuario(usuario, user, &*totalUsuarios, qtdUsuarios, codigo, faculdade, departamento, &arquivoUsuarios);
	for(i = 0; i < qtdUsuarios; i++){
		printf("Area de formacao: ");
		scanf("%s", &(*(tecnico + i)).areaDeFormacao);
		fwrite(&(*(tecnico + i)), sizeof(Tecnico), 1, arquivoTecnicos);
	}
	fclose(arquivoTecnicos);
	clrscr();
}
void mostrarUsuarios(Usuario *usuario, Usuario user, int totalUsuarios, FILE *arquivoUsuarios){
	int i = 0;
	arquivoUsuarios = fopen("usuarios.txt", "r");
	// printf("Total Usuarios: %d\n", totalUsuarios);
	printf("===================== Lista de Usuarios do Sistema ====================\n\n");
	if(arquivoUsuarios != NULL){
		printf("#\tNome\t\tFaculdade\tDepartamento\t\tDat. Nascimento\n");
		while(fread(&user, sizeof(Usuario), 1, arquivoUsuarios))
			printf("%d\t%s\t\t%s\t%s\t\t%d-%d-%d\n", ++i, user.nome, user.faculdade.faculdade, user.departamento.departamento, user.dataDeNascimento[0], user.dataDeNascimento[1], user.dataDeNascimento[2]);
	}
	fclose(arquivoUsuarios);
}
void pesquisarUsuario(Usuario *usuario, Usuario user, int totalUsuarios, FILE *arquivoUsuarios){
	int i = 0, opcao, haResultados = 0;
	arquivoUsuarios = fopen("usuarios.txt", "r");
	printf("\n====================== Lista de Faculdade e Departamentos ====================\n");
	printf("[1]. FET\n[2]. FCNM\n[3]. FEP\n[4]. CIUP\n[5]. Departamento de Informatica\n[6]. Departamento de Matematica\n\n");
	printf("Faculdade/Departamento: ");
	scanf("%d", &opcao);

	if(arquivoUsuarios != NULL){
		printf("#\tNome\t\tFaculdade\tDepartamento\t\tDat. Nascimento\n");
		while(fread(&user, sizeof(Usuario), 1, arquivoUsuarios))
			if(user.faculdade.id ==  opcao || user.departamento.id == opcao){
				printf("%d\t%s\t\t%s\t%s\t\t%d-%d-%d\n", ++i, user.nome, user.faculdade.faculdade, user.departamento.departamento, user.dataDeNascimento[0], user.dataDeNascimento[1], user.dataDeNascimento[2]);
				haResultados = 1;
			}
	}
	if(!haResultados){
		printf("Nenhum resultado encontrado...!\n");
	}
	fclose(arquivoUsuarios);
}
void lancarNotas(Usuario *usuario, Usuario user,  Estudante *estudante, Estudante estudant, Docente *docente, Docente docent, int totalUsuarios, int docenteId, FILE *arquivoUsuarios, FILE *arquivoDocentes, FILE *arquivoEstudantes, FILE *pauta){
	int i = 0, contaDocentes = -1, contaEstudantes = -1, disciplinaId, j;
	arquivoUsuarios = fopen("usuarios.txt", "r");
	arquivoDocentes = fopen("docentes.txt", "r");
	arquivoEstudantes = fopen("estudant.txt", "r");
	pauta = fopen("pauta.txt", "a");
	while(fread(&docent, sizeof(Docente), 1, arquivoDocentes)){
		(*(docente + i)).disciplina.id = docent.disciplina.id;
		i++;
	}
	i = 0;
	if(arquivoUsuarios != NULL){
		while(fread(&user, sizeof(Usuario), 1, arquivoUsuarios)){
			if(user.codigoDoUsuario == 1122){
				contaDocentes++;
			}
			if(docenteId == user.username){
				disciplinaId = (*(docente + contaDocentes)).disciplina.id;
				break;
			}
		}
	}
	while(fread(&estudant, sizeof(Estudante), 1, arquivoEstudantes)){
		(*(estudante + i)).pauta[disciplinaId-1].disciplina.id = estudant.pauta[disciplinaId-1].disciplina.id;
		i++;
	}
	while(fread(&user, sizeof(Usuario), 1, arquivoUsuarios)){
		if(user.codigoDoUsuario == 2211){
			contaEstudantes++;
			if((*(estudante + contaEstudantes)).pauta[disciplinaId-1].disciplina.id == disciplinaId){
				printf("Notas de %s\n", user.nome);
				for(j = 0; j < 3; j++){
					printf("%d .o Teste: ", j+1);
					scanf("%d", &(*(estudante + contaEstudantes)).pauta[disciplinaId-1].notas[j]);
					fwrite(&(*(estudante + contaEstudantes)).pauta[disciplinaId-1], sizeof(Estudante), 1, pauta);
				}
			}
		}
	}
	fclose(arquivoUsuarios);
	fclose(arquivoDocentes);
	fclose(arquivoEstudantes);
	fclose(pauta);
}
void verPauta(Usuario *usuario, Usuario user, Estudante *estudante, Estudante estudant, Docente *docente, Docente docent, int totalUsuarios, int totalDocentes, int usuarioId, int totalEstudantes, int codigo, FILE *arquivoUsuarios, FILE *arquivoDocentes, FILE *arquivoEstudantes, FILE *pauta){
	int i, j, cont = 0, k = 0, escolha, mostrarPauta = 0, disciplinas[5], disciplinaId, contaDocentes = -1, contaEstudantes = -1, soma = 0;
	float maiorMedia = 0, piorMedia = 20, notasMaximas[3] = {0, 0, 0};
	char estudantes[3][32], estudanteMaiorMedia[32], estudantePiorMedia[32], estudantesSemNegativas[10][32];
	arquivoUsuarios = fopen("usuarios.txt", "r");
	arquivoDocentes = fopen("docentes.txt", "r");
	arquivoEstudantes = fopen("estudant.txt", "r");
	pauta = fopen("pauta.txt", "r");

	while(fread(&docent, sizeof(Docente), 1, arquivoDocentes)){
		totalDocentes++;
		(*(docente + i)).disciplina.id = docent.disciplina.id;
		strcpy((*(docente + i)).disciplina.disciplina, docent.disciplina.disciplina);
		i++;
	}
	i = 0;
	while(fread(&estudant, sizeof(Estudante), 1, pauta)){
		totalEstudantes++;
		for(j = 0; j < 5; j++){
			(*(estudante + i)).pauta[j].disciplina.id = estudant.pauta[j].disciplina.id;
		}
		i++;
	}
	

	for(i = 0; i < totalUsuarios; i++){
		if((*(usuario + i)).codigoDoUsuario == 2211){
			contaEstudantes++;
		}else if((*(usuario + i)).codigoDoUsuario == 1122){
			contaDocentes++;
		}
		if(usuarioId == (*(usuario + i)).username){
			if(codigo == 1122){
				disciplinaId = (*(docente + contaDocentes)).disciplina.id;
				mostrarPauta = 1;
				break;
			}else if(codigo == 2211){
				for(j = 0; j < 5; j++){
					disciplinas[j] = (*(estudante + contaEstudantes)).pauta[j].disciplina.id;
				}
				break;
			}
		}
	}
	if(codigo == 2211){
		printf("Escolhe a Disciplina: \n\n");
		for(i = 0; i < totalDocentes; i++){
			printf("[%d]. %s\n", i+1, (*(docente + i)).disciplina.disciplina);
		}
		printf("Escolha: ");
		scanf("%d", &disciplinaId);
		for(i = 0; i < 5; i++){
			if(disciplinaId == disciplinas[i]){
				mostrarPauta = 1;
				break;
			}
		}
	}
	i = 0;
	while(fread(&estudant.pauta[disciplinaId-1], sizeof(Estudante), 1, pauta)){
		for(j = 0; j < 3; j++){
			(*(estudante + i)).pauta[disciplinaId-1].notas[j] = estudant.pauta[disciplinaId-1].notas[j];
		}
		i++;
	}
	i = 0;
	contaEstudantes = -1;
	if(mostrarPauta){
		printf("#\tNome\t\tNota1\tNota2\tNota3\tMedia\n\n");
		while(fread(&user, sizeof(Usuario), 1, arquivoUsuarios)){
			if(user.codigoDoUsuario == 2211){
				contaEstudantes++;
				if((*(estudante + contaEstudantes)).pauta[disciplinaId-1].disciplina.id == disciplinaId){
					printf("%d\t%s\t\t%.1f\t%.1f\t%.1f\t", contaEstudantes+1, user.nome, (*(estudante + contaEstudantes)).pauta[disciplinaId-1].notas[0], (*(estudante + contaEstudantes)).pauta[disciplinaId-1].notas[1], (*(estudante + contaEstudantes)).pauta[disciplinaId-1].notas[2]);
					for(j = 0; j < 3; j++){
						soma += (*(estudante + contaEstudantes)).pauta[disciplinaId-1].notas[j];

						if((*(estudante + contaEstudantes)).pauta[disciplinaId-1].notas[j] > notasMaximas[j]){
							notasMaximas[j] = (*(estudante + contaEstudantes)).pauta[disciplinaId-1].notas[j];
							strcpy(estudantes[j], user.nome);
						}

						if((*(estudante + contaEstudantes)).pauta[disciplinaId-1].notas[j] >= 10){
							cont++;
						}
					}
					if(cont == 3){
						strcpy(estudantesSemNegativas[k], user.nome);
						k++;
					}
					cont = 0;
					if((float) soma/j > maiorMedia){
						maiorMedia = (float) soma/j;
						strcpy(estudanteMaiorMedia, user.nome);
					}
					if((float) soma/j < piorMedia){
						piorMedia = (float) soma/j;
						strcpy(estudantePiorMedia, user.nome);
					}
					printf("%.1f\n", (float) soma/j);
					soma = 0;
				}
			}
		}
		printf("\n");
		printf("PRIMEIRA NOTA MAIOR: %s com %.1f\n", estudantes[0], notasMaximas[0]);
		printf("SEGUNDA NOTA MAIOR: %s com %.1f\n", estudantes[1], notasMaximas[1]);
		printf("TERCEIRA NOTA MAIOR: %s com %.1f\n", estudantes[2], notasMaximas[2]);
		printf("MAIOR MEDIA: %s com %.1f\n", estudanteMaiorMedia, maiorMedia);
		printf("PIOR MEDIA: %s com %.1f\n", estudantePiorMedia, piorMedia);
		printf("ESTUDANTES DEM NEGATIVAS\n");
		for(j = 0; j < k; j++){
			printf("Nome: %s\n", estudantesSemNegativas[j]);
		}
	}
	fclose(arquivoUsuarios);
	fclose(arquivoDocentes);
	fclose(arquivoEstudantes);
	fclose(pauta);
}

void estatisticas(Estudante *estudante){

}
void cadastrarUsuario(Usuario *usuario, Usuario user, int *totalUsuarios, int qtdUsuarios, int codigo, Faculdade *faculdade, Departamento *departamento, FILE *arquivoUsuarios){
	int totUsuarios = *totalUsuarios + qtdUsuarios, i, j, categoria, faculdadeId, departamentoId;
	arquivoUsuarios = fopen("usuarios.txt", "a");
	for(i = *totalUsuarios; i < totUsuarios; i++){
		(*(usuario + i)).senha = 8252;
		(*(usuario + i)).codigoDoUsuario = codigo;
			printf("Username: ");
			scanf("%d", &(*(usuario + i)).username);
			printf("Nome: ");
			scanf("%s", &(*(usuario + i)).nome);
			printf("Data de nascimento (dd-mm-yy) \n");
			for(j = 0; j < 3; j++){
				scanf("%d", &(*(usuario + i)).dataDeNascimento[j]);
			}
			printf("Faculdade: \n");
			for(j = 0; j < 5; j++){
				printf("[%d]. %s\n", (*(faculdade + j)).id, (*(faculdade + j)).faculdade);
			}
			scanf("%d", &faculdadeId);
			(*(usuario + i)).faculdade.id = faculdadeId;
			strcpy((*(usuario + i)).faculdade.faculdade, (*(faculdade + (faculdadeId - 1))).faculdade);
			printf("Departamento: \n");
			for(j = 0; j < 4; j++){
				printf("[%d]. %s\n", (*(departamento + j)).id, (*(departamento + j)).departamento);
			}
			scanf("%d", &departamentoId);
			(*(usuario + i)).departamento.id = departamentoId;
			strcpy((*(usuario + i)).departamento.departamento, (*(departamento + (departamentoId - 1))).departamento);
			printf("Endereco (ciade-avenida-numero_da_casa): \n");
			scanf("%s", &(*(usuario + i)).endereco.cidade);
			scanf("%s", &(*(usuario + i)).endereco.avenida);
			scanf("%s", &(*(usuario + i)).endereco.numeroDacasa);
			fwrite(&(*(usuario + i)), sizeof(Usuario), 1, arquivoUsuarios);
	}
	fclose(arquivoUsuarios);
	*totalUsuarios += qtdUsuarios;
}
void opcoes(int codigo, char *nomeDoUsuario, char *tipoDeUsuario){
	int i;
	printf("\n======================== ESCOLHA UMA OPCAO ============================\n\n");
	printf("Usuario: %s\n", tipoDeUsuario);
	printf("Nome do usuario logado: %s\n\n", nomeDoUsuario);
	if(codigo == 1212){
		printf("[1]. CADASTRAR DOCENTE\n");
		printf("[2]. CADASTRAR ESTUDANTE\n");
		printf("[3]. CADASTRAR TECNICO\n");
		printf("[4]. VISUALIZAR OS CADSTROS\n");
		printf("[5]. PESQUISAR USUARIOS\n");
	}else if(codigo == 1122){
		printf("[6]. LANCAR NOTAS\n");
		printf("[7]. IMPRIMIR PAUTA\n");
		printf("[8]. ESTATISTICAS\n");
	}else if(codigo == 2211){
		printf("[9]. IMPRIMIR PAUTA\n");
		printf("[10]. ESTATISTICAS\n");
	}
    printf("[11]. LOGOUT\n");
	printf("[0]. SAIR\n\n");
}