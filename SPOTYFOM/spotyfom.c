#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spotyfom.h"

;
    for (int j = 0; j < indice; j++) {
      atual = atual->prox;
    }

    struct nodo_fila *novoNodo = CriaNodoFila(atual->info);
    InsereFila(novoNodo, NovaFila);
  }

  free(selecionadas);
}


void imprimeFILA(struct desc_fila *NovaFila) {
  struct nodo_fila *aux = NovaFila->inicio;
  printf("\n*** PLAYLIST ALEATÓRIA ***");
  while (aux != NULL) {
    ImprimeMusica(aux->music);
    aux = aux->prox;
  }
  printf("\n");
}
void ImprimeMusica(struct musica *music){
  printf("\n\nTITULO: %s ", music->titulo);
  printf("\nARTISTA: %s", music->artista);
  printf("\nLETRA: %s", music->letra);
  printf("\nCÓDIGO: %d", music->codigo);
  printf("\nEXECUÇÕES: %d", music->execucoes);
}
