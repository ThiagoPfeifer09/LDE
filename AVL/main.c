#include <stdio.h>
#include "avl.h"

int main() {
    descritor *avl = NULL;
    int opcao, valor;

    do {
        printf("\n*********MENU*********\n");
        printf(" 1. Criar AVL\n");
        printf(" 2. Inserir na AVL\n");
        printf(" 3. Remover da AVL\n");
        printf(" 4. Imprimir In Order\n");
        printf(" 5. Imprimir Pre Order\n");
        printf(" 6. Imprimir Post Order\n");
        printf(" 0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("**********************\n");
        switch (opcao) {
            case 1:
                if (avl == NULL) {
                    avl = CriarDescritor();
                    printf("\nAVL criada com sucesso!\n");
                } else
                    printf("AVL ja existe!\n");
                break;
            case 2:
                if (avl == NULL) {
                    printf("\nAVL não criada! Crie antes de continuar\n");
                } else {
                    printf("\nDigite o valor para inserir: ");
                    scanf("%d", &valor);
                    InserirRaiz(avl, valor);
                }
                break;
            case 3:
                if (avl == NULL) {
                    printf("\nAVL não criada! Crie antes de continuar\n");
                } else {
                    printf("Digite o valor para remover: ");
                    scanf("%d", &valor);
                    removerNo(avl, valor);
                }
                break;
            case 4:
                if (avl == NULL) {
                    printf("\nAVL não criada! Crie antes de continuar\n");
                } else {
                    printf("\nIMPRESSÃO InOrder: ");
                    imprimirInOrder(avl->topo);
                    printf("\n");
                }
                break;
            case 5:
                if (avl == NULL) {
                    printf("\nAVL não criada! Crie antes de continuar\n");
                } else {
                    printf("\nIMPRESSÃO PreOrder: ");
                    imprimirPreOrder(avl->topo);
                    printf("\n");
                }
                break;
            case 6:
                if (avl == NULL) {
                    printf("\nAVL não criada! Crie antes de continuar\n");
                } else {
                    printf("\nIMPRESSÃO PostOrder: ");
                    imprimirPostOrder(avl->topo);
                    printf("\n");
                }
                break;
            case 0:
                printf("\nSaindo\n");
                break;
            default:
                printf("\nOpcao Invalida\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}