#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno {
    char nome[50];
    struct Aluno* proximo;
} Aluno;

typedef struct Disciplina {
    char nome[50];
    Aluno* listaAlunos;
    struct Disciplina* proximo;
} Disciplina;

Disciplina* criarDisciplina(char* nome) {
	
    Disciplina* novaDisciplina = (Disciplina*)malloc(sizeof(Disciplina));
    
    strcpy(novaDisciplina->nome, nome);
    
    novaDisciplina->listaAlunos = NULL;
    novaDisciplina->proximo = NULL;
    
    return novaDisciplina;
}

void adicionarDisciplina(Disciplina** listaDisciplinas, char* nome) {
	
    Disciplina* novaDisciplina = criarDisciplina(nome);
    novaDisciplina->proximo = *listaDisciplinas;
    *listaDisciplinas = novaDisciplina;
}

Disciplina* encontrarDisciplina(Disciplina* listaDisciplinas, char* nome) {
	
    Disciplina* disciplinaAtual = listaDisciplinas;
    
    while (disciplinaAtual != NULL && strcmp(disciplinaAtual->nome, nome) != 0) {
    	
        disciplinaAtual = disciplinaAtual->proximo;
    }
    return disciplinaAtual;
}

void matricularAluno(Disciplina* listaDisciplinas, char* nomeDisciplina, char* nomeAluno) {
	
    Disciplina* disciplina = encontrarDisciplina(listaDisciplinas, nomeDisciplina);
    
    if (disciplina != NULL) {
    	
        Aluno* novoAluno = (Aluno*)malloc(sizeof(Aluno));
        
        strcpy(novoAluno->nome, nomeAluno);
        novoAluno->proximo = disciplina->listaAlunos;
        disciplina->listaAlunos = novoAluno;
        
    } else {
        printf("Disciplina nao encontrada.\n");
    }
}

void excluirAluno(Disciplina* listaDisciplinas, char* nomeDisciplina, char* nomeAluno) {
	
    Disciplina* disciplina = encontrarDisciplina(listaDisciplinas, nomeDisciplina);
    
    if (disciplina != NULL) {
        Aluno* alunoAtual = disciplina->listaAlunos;
        Aluno* anterior = NULL;
        
        while (alunoAtual != NULL && strcmp(alunoAtual->nome, nomeAluno) != 0) {
        	
            anterior = alunoAtual;
            alunoAtual = alunoAtual->proximo;
        }
        
        if (alunoAtual != NULL) {
            if (anterior != NULL) {
            	
                anterior->proximo = alunoAtual->proximo;
                
            } else {
            	
                disciplina->listaAlunos = alunoAtual->proximo;
            }
            free(alunoAtual);
        } else {
            printf("Aluno nao encontrado.\n");
        }
    } else {
        printf("Disciplina nao encontrada.\n");
    }
}

void listarDisciplinas(Disciplina* listaDisciplinas) {
	
    Disciplina* disciplinaAtual = listaDisciplinas;
    
    while (disciplinaAtual != NULL) {
    	
        int quantidadeAlunos = 0;
        
        Aluno* alunoAtual = disciplinaAtual->listaAlunos;
        
        while (alunoAtual != NULL) {
        	
            quantidadeAlunos++;
            alunoAtual = alunoAtual->proximo;
        }
        
        printf("Disciplina: %s, Alunos matriculados: %d\n", disciplinaAtual->nome, quantidadeAlunos);
        disciplinaAtual = disciplinaAtual->proximo;
    }
}

void liberarMemoria(Disciplina* listaDisciplinas) {
    while (listaDisciplinas != NULL) {
    	
        Disciplina* tempDisciplina = listaDisciplinas;
        listaDisciplinas = listaDisciplinas->proximo;
        
        Aluno* alunoAtual = tempDisciplina->listaAlunos;
        
        while (alunoAtual != NULL) {
        	
            Aluno* tempAluno = alunoAtual;
            alunoAtual = alunoAtual->proximo;
            free(tempAluno);
        }
        
        free(tempDisciplina);
    }
}

int main() {
	
    Disciplina* listaDisciplinas = NULL;
    int escolha;
    char nomeDisciplina[50];
    char nomeAluno[50];
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Criar disciplina\n");
        printf("2. Matricular aluno em disciplina\n");
        printf("3. Excluir aluno de disciplina\n");
        printf("4. Informar lista de disciplinas com a quantidade de alunos\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        getchar(); 
        
        switch (escolha) {
            case 1:
                printf("Digite o nome da disciplina: ");
                scanf("%49s", nomeDisciplina);
                
                adicionarDisciplina(&listaDisciplinas, nomeDisciplina);
                
                printf("Disciplina criada!");
                break;
                
            case 2:
                printf("Digite o nome da disciplina: ");
                scanf("%49s", nomeDisciplina);
                printf("Digite o nome do aluno: ");
                scanf("%49s", nomeAluno);
                
                matricularAluno(listaDisciplinas, nomeDisciplina, nomeAluno);
                break;
                
            case 3:
                printf("Digite o nome da disciplina: ");
                scanf("%49s", nomeDisciplina);
                printf("Digite o nome do aluno: ");
                scanf("%49s", nomeAluno);
                
                excluirAluno(listaDisciplinas, nomeDisciplina, nomeAluno);
                break;
                
            case 4:
                listarDisciplinas(listaDisciplinas);
                break;
                
            case 5:
                liberarMemoria(listaDisciplinas);
                
                printf("Saindo...\n");
                exit(0);
                break;
                
            default:
                printf("Opção invalida. Tente novamente.\n");
                break;
        }
    }
    
    return 0;
}
