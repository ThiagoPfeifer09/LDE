#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LDE.h"

// Funções
struct desc_LDE *criarLista() {
    struct desc_LDE *lista = malloc(sizeof(struct desc_LDE));
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }
    return lista;
}


struct music *criarMusica(const char *titulo, const char *artista, const char *letra, int codigo, int execucoes) {
    struct music* novaMusica = (struct music*)malloc(sizeof(struct music));
    if (novaMusica != NULL) {
        strcpy(novaMusica->titulo, titulo);
        strcpy(novaMusica->artista, artista);
        strcpy(novaMusica->letra, letra);
        novaMusica->codigo = codigo;
        novaMusica->execucoes = execucoes;
    }
    return novaMusica;
}

struct nodo_LDE* CriaNodo(struct music *novaMusica){
struct nodo_LDE *NovoNodo = (struct nodo_LDE*)malloc(sizeof(struct nodo_LDE));

NovoNodo->info = novaMusica;
NovoNodo->prox=NULL;
NovoNodo->ante=NULL;

return NovoNodo;
}



void inserirMusica(struct desc_LDE *minhaLista, struct nodo_LDE *novoNodo, int posicao) {
    if (minhaLista == NULL || novoNodo == NULL) {
        return;
    }

    if (posicao <= 0 || minhaLista->inicio == NULL) { // Insere no início
        novoNodo->prox = minhaLista->inicio;
        novoNodo->ante = NULL;
        if (minhaLista->inicio != NULL) {
            minhaLista->inicio->ante = novoNodo;
        }
        minhaLista->inicio = novoNodo;
        if (minhaLista->fim == NULL) {
            minhaLista->fim = novoNodo;
        }
    } else {
        struct nodo_LDE *atual = minhaLista->inicio;
        int pos = 0;

        while (atual->prox != NULL && pos < posicao - 1) {
            atual = atual->prox;
            pos++;
        }

        novoNodo->prox = atual->prox;
        novoNodo->ante = atual;

        if (atual->prox != NULL) {
            atual->prox->ante = novoNodo;
        }
        atual->prox = novoNodo;

        if (novoNodo->prox == NULL) { // Se inserido no final, atualiza o fim da lista
            minhaLista->fim = novoNodo;
        }
    }
    minhaLista->tamanho++;
}   



void imprimirLista(struct desc_LDE *minhaLista) {
    if (minhaLista == NULL || minhaLista->inicio == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    struct nodo_LDE *atual = minhaLista->inicio;
    int posicao = 0;

    printf("=== Lista de Músicas ===\n");
    while (atual != NULL) {
        printf("Posição: %d\n", posicao);
        printf("Título: %s\n", atual->info->titulo);
        printf("Artista: %s\n", atual->info->artista);
        printf("Letra: %s\n", atual->info->letra);
        printf("Código: %d\n", atual->info->codigo);
        printf("Execuções: %d\n", atual->info->execucoes);
        printf("\n");
        atual = atual->prox;
        posicao++;
    }
}

struct music *consultarMusica(struct desc_LDE *minhaLista, int codigo) {
    struct nodo_LDE *atual = minhaLista->inicio;
    while (atual != NULL) {
        if (atual->info->codigo == codigo) {
            return atual->info;
        }
        atual = atual->prox;
    }
    return NULL;
}


void removerMusica(struct desc_LDE *minhaLista, int posicao) {
    if (minhaLista == NULL || minhaLista->inicio == NULL) {
        printf("A lista está vazia ou não existe.\n");
        return;
    }

    if (posicao < 0 || posicao >= minhaLista->tamanho) {
        printf("Posição inválida.\n");
        return;
    }

    struct nodo_LDE *aux = minhaLista->inicio;
    struct nodo_LDE *auxant = NULL;
    int pos = 0;

    // Encontrar o nodo na posição desejada
    while (pos < posicao && aux != NULL) {
        auxant = aux;
        aux = aux->prox;
        pos++;
    }

    if (aux == NULL) {
        printf("Erro ao encontrar a posição na lista.\n");
        return;
    }

    // Caso a lista tenha apenas um item
    if (minhaLista->inicio == minhaLista->fim) {
        minhaLista->inicio = NULL;
        minhaLista->fim = NULL;
    } else if (aux == minhaLista->inicio) { // Remove do começo
        minhaLista->inicio = minhaLista->inicio->prox;
        if (minhaLista->inicio != NULL) {
            minhaLista->inicio->ante = NULL;
        }
    } else if (aux == minhaLista->fim) { // Remove do fim
        minhaLista->fim = auxant;
        if (minhaLista->fim != NULL) {
            minhaLista->fim->prox = NULL;
        }
    } else { // Remove no meio
        auxant->prox = aux->prox;
        if (aux->prox != NULL) {
            aux->prox->ante = auxant;
        }
    }

    printf("Removido: Título: %s, Artista: %s\n", aux->info->titulo, aux->info->artista);

    free(aux->info);
    free(aux);
    minhaLista->tamanho--;
}



void liberarLista(struct desc_LDE *minhaLista) {
    struct nodo_LDE *atual = minhaLista->inicio;
    while (atual != NULL) {
        struct nodo_LDE *proximo = atual->prox;
        free(atual->info);
        free(atual);
        atual = proximo;
    }
    free(minhaLista);
}
