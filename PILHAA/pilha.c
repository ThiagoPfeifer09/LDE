#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"




struct descp* CriaDesc(){

struct descp *Pilha = (struct descp* )malloc(sizeof(struct descp));

Pilha->tamanho=0;
Pilha->topo=NULL;

return Pilha;
}


struct nodo* CriaNodo(struct musica *NovaMusica){

struct nodo *novoNodo = (struct nodo *)malloc(sizeof(struct nodo));

novoNodo->music=NovaMusica;
novoNodo->prox=NULL;

return novoNodo;
}

struct musica* CriaMusica(){

struct musica* MUSIC = (struct musica*)malloc(sizeof(struct musica));

char titulo[256], artista[256], letra[256];
int codigo, execucoe;

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
scanf("%d", &execucoe);


strcpy(MUSIC->titulo, titulo);
strcpy(MUSIC->artista, artista);
strcpy(MUSIC->letra, letra);
MUSIC->execucoes=execucoe;
MUSIC->codigo=codigo;

return MUSIC;
}

void push(struct nodo *NovoElement, struct descp *NovaPilha){

NovoElement->prox = NovaPilha->topo;
NovaPilha->topo = NovoElement;
NovaPilha->tamanho++;

}

void imprime(struct descp *NovaPilha){

  struct nodo *aux = NovaPilha->topo;
  
  while(aux !=NULL){
    printf("\n\nTITULO: %s ",aux->music->titulo);
    printf("\t ARTISTA: %s",aux->music->artista);
    printf("\nLETRA: %s",aux->music->letra);
    printf("\nCÓDIGO: %d",aux->music->codigo);
    printf("\tEXECUÇÕES: %d",aux->music->execucoes);
    aux = aux->prox;
  }
  printf("\n");
}

void ConsultaMusic(struct descp* NovaPilha, int code){
  struct nodo *aux = NovaPilha->topo; 

  while(aux != NULL){
    if(aux->music->codigo == code){
      printf("\n\nTITULO: %s ",aux->music->titulo);
      printf("\t ARTISTA: %s",aux->music->artista);
      printf("\nLETRA: %s",aux->music->letra);
      printf("\nCÓDIGO: %d",aux->music->codigo);
      printf("\tEXECUÇÕES: %d",aux->music->execucoes);
    }
    aux=aux->prox;
  }
  
}

struct nodo *pop(struct descp *NovaPilha){
struct nodo *aux = NovaPilha->topo;
  NovaPilha->topo=NovaPilha->topo->prox;
  NovaPilha->tamanho--;
  return aux;
}

void LiberaPilha(struct descp *NovaPilha){
struct nodo *aux;
    while (NovaPilha->topo != NULL) {
        aux = pop(NovaPilha);
        free(aux->music);
        free(aux);
    }
    free(NovaPilha);
}
