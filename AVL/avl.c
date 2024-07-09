#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

descritor *CriarDescritor() {
    descritor *avl = (descritor *)malloc(sizeof(descritor));
    avl->altura = 0;
    avl->topo = NULL;
    return avl;
}

arvore *AdicionarNo(arvore *topo, arvore *parente, int valor) {
    if (topo == NULL) {
        arvore *novo = (arvore *)malloc(sizeof(arvore));
        novo->parente = parente;
        novo->valor = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    if (valor < topo->valor) {
        topo->esquerda = AdicionarNo(topo->esquerda, topo, valor);
    } else if (valor > topo->valor) {
        topo->direita = AdicionarNo(topo->direita, topo, valor);
    }
    return ajustarBalanceamento(topo);
}

arvore *EncontrarMin(arvore *no) {
    arvore *atual = no;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

arvore *rotacionarDireita(arvore *y) {
    arvore *x = y->esquerda;
    arvore *T2 = x->direita;
    x->direita = y;
    y->esquerda = T2;
    return x;
}

arvore *rotacionarEsquerda(arvore *x) {
    arvore *y = x->direita;
    arvore *T2 = y->esquerda;
    y->esquerda = x;
    x->direita = T2;
    return y;
}

arvore *ajustarBalanceamento(arvore *no) {
    int balanceamento = calcularBalanceamento(no);

    if (balanceamento > 1 && calcularBalanceamento(no->esquerda) >= 0)
        return rotacionarDireita(no);

    if (balanceamento < -1 && calcularBalanceamento(no->direita) <= 0)
        return rotacionarEsquerda(no);

    if (balanceamento > 1 && calcularBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }

    if (balanceamento < -1 && calcularBalanceamento(no->direita) > 0) {
        no->direita = rotacionarDireita(no->direita);
        return rotacionarEsquerda(no);
    }

    return no;
}

void InserirRaiz(descritor *avl, int valor) {
    avl->topo = AdicionarNo(avl->topo, NULL, valor);
}

int maiorValor(int a, int b) {
    return (a > b) ? a : b;
}

int obterAltura(arvore *no) {
    if (no == NULL)
        return -1;
    else {
        return 1 + maiorValor(obterAltura(no->esquerda), obterAltura(no->direita));
    }
}

int calcularBalanceamento(arvore *no) {
    if (no == NULL)
        return 0;
    return obterAltura(no->esquerda) - obterAltura(no->direita);
}

arvore *removerNoAuxiliar(arvore *topo, int valor) {
    if (topo == NULL)
        return topo;

    if (valor < topo->valor) {
        topo->esquerda = removerNoAuxiliar(topo->esquerda, valor);
    } else if (valor > topo->valor) {
        topo->direita = removerNoAuxiliar(topo->direita, valor);
    } else {
        if ((topo->esquerda == NULL) || (topo->direita == NULL)) {
            arvore *temp = topo->esquerda ? topo->esquerda : topo->direita;
            if (temp == NULL) {
                temp = topo;
                topo = NULL;
            } else
                *topo = *temp;
            free(temp);
        } else {
            arvore *temp = EncontrarMin(topo->direita);
            topo->valor = temp->valor;
            topo->direita = removerNoAuxiliar(topo->direita, temp->valor);
        }
    }

    if (topo == NULL)
        return topo;

    return ajustarBalanceamento(topo);
}

void removerNo(descritor *avl, int valor) {
    avl->topo = removerNoAuxiliar(avl->topo, valor);
}

void imprimirInOrder(arvore *topo) {
    if (topo != NULL) {
        imprimirInOrder(topo->esquerda);
        printf("[%d]", topo->valor);
        imprimirInOrder(topo->direita);
    }
}

void imprimirPreOrder(arvore *topo) {
    if (topo != NULL) {
        printf("[%d]", topo->valor);
        imprimirPreOrder(topo->esquerda);
        imprimirPreOrder(topo->direita);
    }
}

void imprimirPostOrder(arvore *topo) {
    if (topo != NULL) {
        imprimirPostOrder(topo->esquerda);
        imprimirPostOrder(topo->direita);
        printf("[%d]", topo->valor);
    }
}