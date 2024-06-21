#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lse.h"


// Funções
struct desc_LSE *criarLista() {
    struct desc_LSE *lista = malloc(sizeof(struct desc_LSE));

    lista->inicio = NULL;
    lista->tamanho = 0;
    
    return lista;
}

struct music *criarMusica(const char *titulo, const char *artista, const char *letra, int codigo, int execucoes) {
    struct music *novaMusica = malloc(sizeof(struct music));
    if (novaMusica != NULL) {
        strcpy(novaMusica->titulo, titulo);
        strcpy(novaMusica->artista, artista);
        strcpy(novaMusica->letra, letra);
        novaMusica->codigo = codigo;
        novaMusica->execucoes = execucoes;
    }
    return novaMusica;
}

void inserirMusica(struct desc_LSE *minhaLista, struct music *novaMusica, int posicao) {
    struct nodo_LSE *novoNodo = malloc(sizeof(struct nodo_LSE));
    if (novoNodo == NULL) {
        printf("\nErro ao alocar memória para novo nó.\n");
        return;
    }

    novoNodo->info = novaMusica;
    novoNodo->prox = NULL;

    if (posicao < 0) {
        printf("Posição inválida.\n");
        free(novoNodo);
        return;
    }

    if (minhaLista->inicio == NULL || posicao == 0) {
        novoNodo->prox = minhaLista->inicio;
        minhaLista->inicio = novoNodo;
        minhaLista->tamanho++;
        return;
    }

    if (posicao >= minhaLista->tamanho) {
        posicao = minhaLista->tamanho;
    }

    struct nodo_LSE *anterior = NULL;
    struct nodo_LSE *atual = minhaLista->inicio;
    int posicaoAtual = 0;

    while (atual != NULL && posicaoAtual < posicao) {
        anterior = atual;
        atual = atual->prox;
        posicaoAtual++;
    }

    anterior->prox = novoNodo;
    novoNodo->prox = atual;
    minhaLista->tamanho++;
}   
 
void imprimirLista(struct desc_LSE *minhaLista) {
    if (minhaLista == NULL || minhaLista->inicio == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    struct nodo_LSE *atual = minhaLista->inicio;
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

struct music *consultarMusica(struct desc_LSE *minhaLista, int codigo) {
    struct nodo_LSE *atual = minhaLista->inicio;
    while (atual != NULL) {
        if (atual->info->codigo == codigo) {
            return atual->info;
        }
        atual = atual->prox;
    }
    return NULL;
}
 
void removerMusica(struct desc_LSE *minhaLista, int posicao) {

    struct nodo_LSE *aux = minhaLista->inicio;
     int listaPos=0;

    if((minhaLista->tamanho ==0)||(posicao > minhaLista->tamanho)){ 
		printf("posicao não existe OU LISTA VAZIA!\n");
		return ;
	}
	else{
		if(posicao==0){ 
			struct nodo_LSE *aux = minhaLista->inicio;
			minhaLista->inicio = minhaLista->inicio->prox;
			minhaLista->tamanho--;
			return aux; 
		}
		else{
			struct nodo_LSE *anterior;
			struct nodo_LSE *aux = minhaLista->inicio;
			while(aux != NULL){
				anterior = aux;
				aux = aux->prox;
				listaPos++;
				if(listaPos == posicao){
					anterior->prox = aux->prox;
					minhaLista->tamanho--;
					return aux;
				}
			}	
		}
	}
}

void liberarLista(struct desc_LSE *minhaLista) {
    struct nodo_LSE *atual = minhaLista->inicio;
    while (atual != NULL) {
        struct nodo_LSE *proximo = atual->prox;
        free(atual->info);
        free(atual);
        atual = proximo;
    }
    free(minhaLista);
}
