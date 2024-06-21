#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lde.h"


int main() {

    int escolha = -1, posicao;
    struct nodo_LDE *novoNodo = NULL;
    struct desc_LDE *minhaLista = NULL;
    struct musica *novaMusica = NULL;

    while (escolha != 0) {
        setbuf(stdin, NULL);
        printf("-------MENU-------\n");
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

                printf("Digite a posição que deseja inserir a música: ");
                scanf("%d", &posicao);

                novaMusica = criarMusica(titulo, artista, letra, codigo, execucoes);
                
                novoNodo = CriaNodo(novaMusica);
                
                inserirMusica(minhaLista, novoNodo, posicao);

                printf("Música inserida com sucesso!\n");
            } else {
                printf("A lista não foi criada ainda! Por favor, crie a lista primeiro.\n");
            }
            break;

        case 3:
            if (minhaLista != NULL) {
                int codigo;
                printf("Digite a posicao da música que deseja remover: ");
                scanf("%d", &codigo);
                removerMusica(minhaLista, codigo);
            } else {
                printf("A lista não foi criada ainda! Por favor, crie a lista primeiro.\n");
            }
            break;

        case 4:
            if (minhaLista != NULL) {
                int codigo;
                printf("Digite o código da música que deseja consultar: ");
                scanf("%d", &codigo);
                struct music *musica = consultarMusica(minhaLista, codigo);
                if (musica != NULL) {
                    printf("Música encontrada: %s - %s\n", musica->titulo, musica->artista);
                } else {
                    printf("Música não encontrada!\n");
                }
            } else {
                printf("A lista não foi criada ainda! Por favor, crie a lista primeiro.\n");
            }
            break;

        case 5:
            if (minhaLista != NULL) {
                imprimirLista(minhaLista);
            } else {
                printf("A lista não foi criada ainda! Por favor, crie a lista primeiro.\n");
            }
            break;

        case 6:
            if (minhaLista != NULL) {
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
