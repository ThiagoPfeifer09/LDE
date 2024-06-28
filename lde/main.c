#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LDE.h"

int main() {

    int escolha = -1, posicao;
    struct nodo_LDE *novoNodo = NULL;
    struct desc_LDE *minhaLista = NULL;
    struct music *novaMusica = NULL;

    while (escolha != 0) {
        setbuf(stdin, NULL);
        printf("\n\n-------MENU-------\n");
        printf("1- Criar lista\n");
        printf("2- Inserir música\n");
        printf("3- Remover música\n");
        printf("4- Consultar música\n");
        printf("5- Imprimir\n");
        printf("6- Liberar\n");
        printf("0- Sair\n");
        printf("------------------\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &escolha);

        switch (escolha) {

        case 1:
            if (minhaLista == NULL) {
                minhaLista = criarLista();
                printf("Lista criada com sucesso!\n");
            } else {
                printf("A lista já foi criada!\n");
            }
            break;

        case 2:
            if (minhaLista != NULL) {
                char titulo[256], artista[256], letra[256];
                int codigo, execucoes;
                printf("Digite o título da música: ");
                getchar(); 
                fgets(titulo, 256, stdin);
                titulo[strcspn(titulo, "\n")] = '\0'; 

                printf("Digite o artista da música: ");
                fgets(artista, 256, stdin);
                artista[strcspn(artista, "\n")] = '\0'; 

                printf("Digite a letra da música: ");
                fgets(letra, 256, stdin);
                letra[strcspn(letra, "\n")] = '\0'; 

                printf("Digite o código da música: ");
                scanf("%d", &codigo);

                printf("Digite o número de execuções da música: ");
                scanf("%d", &execucoes);

                novaMusica = criarMusica(titulo, artista, letra, codigo, execucoes);                
                novoNodo = CriaNodo(novaMusica);

                printf("Digite a posição que deseja inserir a música: ");
                scanf("%d", &posicao);

                
                inserirMusica(minhaLista, novoNodo, posicao);

                printf("\nMúsica inserida com sucesso!\n\n");
            } else {
                printf("\nA lista não foi criada ainda! Por favor, crie a lista primeiro.\n");
            }
            break;

        case 3:
            if (minhaLista != NULL && minhaLista->tamanho != 0) {
                int codigo;
                printf("Digite a posicao da música que deseja remover: ");
                scanf("%d", &codigo);
                removerMusica(minhaLista, codigo);
            } else {
                printf("\nA lista não foi criada ainda! Por favor, crie a lista primeiro.\n");
            }
            break;

        case 4:
            if (minhaLista != NULL && minhaLista->tamanho != 0) {
                char titulo[256];
                printf("Digite o título da música que deseja consultar: ");
                getchar(); // Limpar o buffer do teclado
                fgets(titulo, 256, stdin);
                titulo[strcspn(titulo, "\n")] = '\0'; 

                struct music *musica = consultarMusicaPorTitulo(minhaLista, titulo);
                if (musica != NULL) {
                    printf("\n\nMúsica encontrada:\n");
                    printf("Título: %s\n", musica->titulo);
                    printf("Artista: %s\n", musica->artista);
                    printf("Letra: %s\n", musica->letra);
                    printf("Código: %d\n", musica->codigo);
                    printf("Execuções: %d\n\n", musica->execucoes);
                } else {
                    printf("Música não encontrada!\n");
                }
            } else {
                printf("\nA lista não foi criada ainda! Por favor, crie a lista primeiro.\n");
            }
            break;

        case 5:
            if (minhaLista != NULL && minhaLista->tamanho != 0) {
                imprimirLista(minhaLista);
            } else {
                printf("A lista não foi criada ainda! Por favor, crie a lista primeiro.\n");
            }
            break;

        case 6:
            if (minhaLista != NULL && minhaLista->tamanho != 0) {
                liberarLista(minhaLista);
                minhaLista = NULL;
                printf("Lista liberada!\n");
            } else {
                printf("A lista já está vazia!\n");
            }
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida! tente uma das opcoes do menu\n");
            break;
        }
    }

    return 0;
}
