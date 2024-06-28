#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spotyfom.h"

int main() {
  int op = -1;
  int menu = -1;
  int quant = 0;
  int start = 0;
  int pl, tam;
  
  //DECLARAÇÃO DA LISTA
  struct desc *MinhaLista = CriaLista();
  struct nodo *Novo_Element = NULL;
  struct musica *Nova_Musica = NULL;
  
  //DECLARAÇÃO DA FILA
  struct nodo_fila *NodoFila = NULL; 
  struct desc_fila *NovaFila = NULL;

  while (op != 0) {
    printf("\n");
    printf("****************************************\n");
    printf("*          MENU PRINCIPAL              *\n");
    printf("****************************************\n");
    printf("*    \t1. Carregar Acervo             *\n");
    printf("*    \t2. Imprimir Acervo             *\n");
    printf("*    \t3. Procurar música no Acervo   *\n");
    printf("*    \t4. Criar Playlist              *\n");
    printf("*    \t5. Imprimir Playlist           *\n");
    printf("*    \t6. Relatórios                  *\n");
    printf("*    \t7. Back-Up                     *\n");
    printf("*    \t0. Sair                        *\n");
    printf("****************************************\n");
    printf("Digite a opção desejada: ");
    scanf("%d", &op);

    switch (op) {
    case 1:
      if (MinhaLista != NULL)
        carregarAcervo(MinhaLista, "musica.txt");
      else
        printf("Erro ao alocar memória para a lista.\n");
      break;

    case 2:
      //SUB MENU PARA IMPRESSÃO PERSONALIZADA 
      menu = -1;
      while (menu != 0) {
        printf("\n\n****************************************\n");
        printf("*          MENU DE IMPRESSÃO           *\n");
        printf("****************************************\n");
        printf("*    \t1. Imprimir Acervo Completo    *\n");
        printf("*    \t2. Imprimir Acervo 500 itens   *\n");
        printf("*    \t3. Imprimir 'x' itens          *\n");
        printf("*    \t4. Imprimir intervalo          *\n");
        printf("*    \t0. VOLTAR PARA O MENU          *\n");
        printf("****************************************\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &menu);

        switch (menu) {
        case 1:
          imprimirLista(MinhaLista);
          break;
        case 2:
          start = 0;
          imprimirMenu(MinhaLista, 500, start);
          break;
        case 3:
          printf("\n*********************************************\n");
          printf("*Quantos itens gostaria que fossem impressos*\n");
          scanf("%d", &quant);
          printf("*********************************************\n");
          start = 0;
          imprimirMenu(MinhaLista, quant, start);
          break;
        case 4:
          {
            int inicio, fim;
            printf("\n****************************************\n");
            printf("*\tDigite o intervalo (inicio e fim)  *\n");
            printf("*\tInicio:");            
            scanf("%d", &inicio);
            printf("*\tFim:");
            scanf("%d", &fim);
            printf("****************************************\n\n");
            imprimirRange(MinhaLista, inicio, fim);
          }
          break;
        case 0:
          break;
        default:
          printf("Opção inválida! Tente novamente.\n");
          break;
        }
      }
      break;



      
    case 3:
      if (MinhaLista != NULL && MinhaLista->tamanho != 0) {
        char titulo[256];
        printf("Digite o título da música que deseja consultar: ");
        getchar(); 
        fgets(titulo, 256, stdin);
        titulo[strcspn(titulo, "\n")] = '\0'; 

        struct musica *musica = consultarMusicaPorTitulo(MinhaLista, titulo);
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
        printf("\nAcervo não carregado, por favor carregue o acervo antes!\n");
      }
      break;

      
    case 4:
      if(MinhaLista->tamanho > 0 && MinhaLista!=NULL){
      printf("\n");
      printf("****************************************\n");
      printf("*         CRIAR PLAYLIST               *\n");
      printf("****************************************\n");
      printf("*    \t1. CRIAR PLAYLIST A ESCOLHA    *\n");
      printf("*    \t2. CRIAR PLAYLIST ALEATÓRIA    *\n");
      printf("****************************************\n");
      printf("Digite a opção desejada: ");
      scanf("%d", &pl);

      if(pl == 1){
        
      }

      if(pl == 2){
      printf("\nDigite o tamanho que deseja para a playlist:");
      scanf("%d", &tam);
      printf("\nCRIANDO PLAYLIST ALEATORIA\n");
      void criarPlaylistAleatoria(struct desc *MinhaLista, struct desc_fila *NovaFila, int tam);
      }
        
      else{
        printf("Opção inválida!");
      }    }
      else{
        printf("\nAcervo não contem músicas, carrega músicas antes!\n");
      }
      break;

    case 5:
      imprimeFILA(NovaFila);
      break;

    case 6:
    
      break;

    case 7:
    
      break;

    case 0:
      printf("Saindo...\n");
      break;

    default:
      printf("Opção inválida! Tente novamente.\n");
      break;
    }
  }
  return 0;
}
