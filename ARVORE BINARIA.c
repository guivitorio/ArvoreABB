#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

typedef struct No {
    int rgm;
    char nome[50];
    struct No* esquerda;
    struct No* direita;
} No;

No* criarNo(int rgm, const char* nome) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->rgm = rgm;
    strcpy(novoNo->nome, nome);
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

No* inserirNo(No* raiz, int rgm, const char* nome) {
    if (raiz == NULL) {
        return criarNo(rgm, nome);
    }
    
    if (rgm < raiz->rgm) {
        raiz->esquerda = inserirNo(raiz->esquerda, rgm, nome);
    } else if (rgm > raiz->rgm) {
        raiz->direita = inserirNo(raiz->direita, rgm, nome);
    }
    
    return raiz;
}

No* buscarNo(No* raiz, int rgm) {
    if (raiz == NULL || raiz->rgm == rgm) {
        return raiz;
    }
    
    if (rgm < raiz->rgm) {
        return buscarNo(raiz->esquerda, rgm);
    } else {
        return buscarNo(raiz->direita, rgm);
    }
}

No* encontrarNoMinimo(No* raiz) {
    No* atual = raiz;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

No* removerNo(No* raiz, int rgm) {
    if (raiz == NULL) {
        return raiz;
    }
    
    if (rgm < raiz->rgm) {
        raiz->esquerda = removerNo(raiz->esquerda, rgm);
    } else if (rgm > raiz->rgm) {
        raiz->direita = removerNo(raiz->direita, rgm);
    } else {
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        
        No* temp = encontrarNoMinimo(raiz->direita);
        raiz->rgm = temp->rgm;
        strcpy(raiz->nome, temp->nome);
        raiz->direita = removerNo(raiz->direita, temp->rgm);
    }
    
    return raiz;
}

void exibir(No* raiz, int opcao) {
    switch (opcao) {
        case 1:
            exibirPreOrdem(raiz);
            break;	
        case 2:
            exibirInOrdem(raiz);
            break;
        case 3:
            exibirPosOrdem(raiz);
            break;
        case 4:
			exibirGraficamente(raiz, 0);
            break;
        default:
            printf("Opcao invalida!\n");
    }
}

void exibirPreOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("\nRGM: %d - Nome: %s\n", raiz->rgm, raiz->nome);
        exibirPreOrdem(raiz->esquerda);
        exibirPreOrdem(raiz->direita);
    }
}

void exibirInOrdem(No* raiz) {
    if (raiz != NULL) {
        exibirInOrdem(raiz->esquerda);
        printf("\nRGM: %d - Nome: %s\n", raiz->rgm, raiz->nome);
        exibirInOrdem(raiz->direita);
    }
}

void exibirPosOrdem(No* raiz) {
    if (raiz != NULL) {
        exibirPosOrdem(raiz->esquerda);
        exibirPosOrdem(raiz->direita);
        printf("\nRGM: %d - Nome: %s\n", raiz->rgm, raiz->nome);
    }
}

void exibirGraficamente(No* raiz, int espaco) {
    if (raiz == NULL) {
        return;
    }
    
    espaco += 10;
    
    exibirGraficamente(raiz->direita, espaco);
    
    printf("\n");
    for (int i = 10; i < espaco; i++) {
        printf(" ");
    }
    printf("%d  %s\n", raiz->rgm, raiz->nome);
    
    exibirGraficamente(raiz->esquerda, espaco);
}

void esvaziarArvore(No* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    esvaziarArvore(raiz->esquerda);
    esvaziarArvore(raiz->direita);
    
    free(raiz);
}

void pausarPrograma() {
    printf("\nPressione Enter para continuar...");
    getchar();
}

void exibirCreditos() {
    printf("\nDesenvolvido por: Arthur Pimentel, Guilherme Vitório, Renan Sena, Marcely Costa\n");
}

void exibirMenu() {
    printf("\n----- MENU -----\n");
    printf("1. Inserir aluno\n");
    printf("2. Remover aluno\n");
    printf("3. Pesquisar aluno\n");
    printf("4. Esvaziar a arvore\n");
    printf("5. Exibir arvore\n");
    printf("0. Sair do programa\n");
    printf("\nEscolha uma opcao: ");
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    No* arvore = NULL;
    FILE* arquivo;
    
    // Ler dados dos alunos de um arquivo de texto e inserir na árvore
    arquivo = fopen("arquivo.txt", "r");
    if (arquivo != NULL) {
        int rgm;
        char nome[50];
        
        while (fscanf(arquivo, "%d %[^\n]", &rgm, nome) != EOF) {
            arvore = inserirNo(arvore, rgm, nome);
        }
        
        fclose(arquivo);
    }
    
	printf("ESTRUTURA DE DADOS I\n");
	printf("Professor: WALACE BONFIM\n");
    
    int opcao;
    
    while (true) {
        exibirMenu();
        scanf("%d", &opcao);
        fflush(stdin);
        
        switch (opcao) {
            case 1: {
                int rgm;
                char nome[50];
                
                printf("Digite o RGM do aluno: ");
                scanf("%d", &rgm);
                fflush(stdin);
                
                printf("Digite o nome do aluno: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                
                arvore = inserirNo(arvore, rgm, nome);
                printf("Aluno inserido com sucesso...\n");
                pausarPrograma();
                break;
            }
            case 2: {
                int rgm;
                
                printf("Digite o RGM do aluno a ser removido: ");
                scanf("%d", &rgm);
                fflush(stdin);
                
                arvore = removerNo(arvore, rgm);
                printf("Aluno removido com sucesso...\n");
                pausarPrograma();
                break;
            }
            case 3: {
                int rgm;
                
                printf("Digite o RGM do aluno a ser pesquisado: ");
                scanf("%d", &rgm);
                fflush(stdin);
                
                No* aluno = buscarNo(arvore, rgm);
                if (aluno != NULL) {
                    printf("Aluno encontrado...\n");
                    printf("RGM: %d - Nome: %s\n", aluno->rgm, aluno->nome);
                } else {
                    printf("Aluno nao encontrado...\n");
                }
                pausarPrograma();
                break;
            }
            case 4: {
                esvaziarArvore(arvore);
                arvore = NULL;
                printf("Árvore esvaziada com sucesso...\n");
                pausarPrograma();
                break;
            }
            case 5: {
			    if (arvore == NULL) {
			        printf("Arvore vazia...\n");
			    } else {
			        printf("1 - Pré-Ordem\n");
			        printf("2 - In-Ordem\n");
			        printf("3 - Pós-Ordem\n");
			        printf("4 - Graficamente \n");
			        printf("Escolha a opção de exibição: ");
			        int opcaoExibicao;
			        scanf("%d", &opcaoExibicao);
			        fflush(stdin);
			
			        switch (opcaoExibicao) {
			            case 1: {
			                printf("Exibição Pré-Ordem:\n");
			                exibir(arvore, 1);
			                break;
			            }
			            case 2: {
			                printf("Exibição In-Ordem:\n");
			                exibir(arvore, 2);
			                break;
			            }
			            case 3: {
			                printf("Exibição Pós-Ordem:\n");
			                exibir(arvore, 3);
			                break;
			            }
			            case 4: {
			                printf("Exibição gráfica: \n");
							exibirGraficamente(arvore, 0);
			                break;
			            }
			            default: {
			                printf("Opção inválida!\n");
			                break;
			            }
			        }
			    }
			    pausarPrograma();
			    break;
			}
            case 0: {
                printf("\nEncerrando o programa...\n");
                exibirCreditos();
                esvaziarArvore(arvore);
                exit(0);
            }
            default: {
                printf("\nOpcao invalida. Tente novamente.\n");
                pausarPrograma();
                break;
            }
        }
    }
    
    return 0;
}

