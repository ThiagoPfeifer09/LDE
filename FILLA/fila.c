#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fila.h"


struct descp* CriaFila(){

struct descp *FILA = (struct descp* )malloc(sizeof(struct descp));

  FILA->tamanho=0;
  FILA->inicio=NULL;
  FILA->fim=NULL;

return FILA;
}


struct nodo* CriaNodo(struct musica *NovaMusica){

struct nodo *novoNodo = (struct nodo *)malloc(sizeof(struct nodo));

novoNodo->music=NovaMusica;
novoNodo->prox=NULL;
novoNodo->ant=NULL;

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


void InsereFila(struct nodo *NovoElement, struct descp *NovaFila){
struct nodo *aux=NovaFila->fim;
  if(NovaFila->fim == NULL){
    NovaFila->fim=NovoElement;
    NovaFila->inicio=NovoElement;
  }
  else{
    NovaFila->fim->prox=NovoElement;
    NovaFila->fim=NovoElement;
  }
  NovaFila->tamanho++;
}




void imprime(struct descp *NovaFila){

  struct nodo *aux = NovaFila->inicio;

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

void ConsultaMusic(struct descp* NovaFila, int code){
  struct nodo *aux = NovaFila->inicio; 

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

struct nodo *RemoveFila(struct descp *NovaFila){
struct nodo *aux = NovaFila->inicio;
  NovaFila->inicio=NovaFila->inicio->prox;
  NovaFila->tamanho--;
  return aux;
}

void LiberaFila(struct descp *NovaFila){
struct nodo *aux;
    while (NovaFila->inicio != NULL) {
        aux = RemoveFila(NovaFila);
        free(aux->music);
        free(aux);
    }
    free(NovaFila);
}