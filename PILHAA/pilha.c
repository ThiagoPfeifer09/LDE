#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

struct descp* CriaDesc() {
    struct descp *Pilha = (struct descp*)malloc(sizeof(struct descp));
    Pilha->tamanho = 0;
    Pilha->topo = NULL;
    return Pilha;
}

struct nodo* CriaNodo(struct musica *NovaMusica) {
    struct nodo *novoNodo = (struct nodo*)malloc(sizeof(struct nodo));
    novoNodo->music = NovaMusica;
    novoNodo->prox = NULL;
    return novoNodo;
}

struct musica* CriaMusica() {
    struct musica* MUSIC = (struct musica*)malloc(sizeof(struct musica));

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

    strcpy(MUSIC->titulo, titulo);
    strcpy(MUSIC->artista, artista);
    strcpy(MUSIC->letra, letra);
    MUSIC->execucoes = execucoes;
    MUSIC->codigo = codigo;

    return MUSIC;
}

void push(struct nodo *NovoElement, struct descp *NovaPilha) {
    NovoElement->prox = NovaPilha->topo;
    NovaPilha->topo = NovoElement;
    NovaPilha->tamanho++;
}

void imprime(struct descp *NovaPilha) {
    struct nodo *aux = NovaPilha->topo;
    while (aux != NULL) {
        ImprimeMusica(aux->music);
        aux = aux->prox;
    }
    printf("\n");
}

void ConsultaMusica(struct descp* NovaPilha, char* titulo) {
    struct nodo *aux = NovaPilha->topo;
    while (aux != NULL) {
        if (strcasecmp(aux->music->titulo, titulo) == 0) {
            ImprimeMusica(aux->music);
        }
        aux = aux->prox;
    }
}

struct nodo* pop(struct descp *NovaPilha) {
    if (NovaPilha->tamanho == 0) {
        return NULL;
    }
    struct nodo *aux = NovaPilha->topo;
    printf("\nMÚSICA REMOVIDA");
    ImprimeMusica(NovaPilha->topo->music);
    NovaPilha->topo = NovaPilha->topo->prox;
    NovaPilha->tamanho--;
    return aux;
}

void LiberaPilha(struct descp *NovaPilha) {
    struct nodo *aux;
    while (NovaPilha->topo != NULL) {
        aux = pop(NovaPilha);
        free(aux->music);
        free(aux);
    }
    free(NovaPilha);
}

void ImprimeMusica(struct musica *music) {
    printf("\n\nTITULO: %s ", music->titulo);
    printf("\tARTISTA: %s", music->artista);
    printf("\nLETRA: %s", music->letra);
    printf("\nCÓDIGO: %d", music->codigo);
    printf("\tEXECUÇÕES: %d\n\n", music->execucoes);
}
