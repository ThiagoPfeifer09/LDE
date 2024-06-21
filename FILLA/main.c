#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

int main() {

struct descp *NovaFila = NULL;
int op, code=0;
struct musica *NovaMusica = NULL;
struct nodo *NovoElement = NULL;

while(op!=0){

printf("\n/////////////////");
printf("\n1-Criar fila\n");
printf("2-Inserir música\n");
printf("3-Consultar música\n");
printf("4-Imprimir fila\n");
printf("5-Remover da fila\n");
printf("6-Libera\n");
printf("7-Tamanho da fila\n");
printf("8-Verificar se está vazia a fila\n");
printf("0-Sair\n");
printf("/////////////////\n");
scanf("%d", &op);

switch(op){
case 1:
if(NovaFila == NULL){
  NovaFila=CriaFila();
  if(NovaFila!=NULL){
    printf("\nPILHA CRIADA COM SUCESSO\n");
  }
  else{
    printf("Erro ao alocar descritor\n");
  }
}
  else{
    printf("\nDescritor já alocado!\n");
  }
break;

case 2:
if(NovaFila != NULL){
NovaMusica=CriaMusica();
NovoElement = CriaNodo(NovaMusica);
InsereFila(NovoElement, NovaFila);
}
  else{
    printf("Crie a fila antes!");
  }


break;

case 3:
  if(NovaFila!=NULL){
  printf("Digite o código da música para buscar na fila: ");
  scanf("%d", &code);
  ConsultaMusic(NovaFila, code);
  }
  else{
    printf("Crie a fila antes!");
  }
break;


case 4:
  if(NovaFila == NULL){
    printf("Fila não criada!\n");
  }
  
  else if(NovaFila->tamanho==0){printf("Fila está vazia\n");}
  
  else{
  imprime(NovaFila);
  }
break;

  
case 5:
  if(NovaFila!=NULL){
  RemoveFila(NovaFila);
  }
else{
  printf("Fila não alocada");
}
break;

case 6:
  LiberaFila(NovaFila);
break;

case 7:
if(NovaFila == NULL){
  printf("Fila não existe, crie ela!");
}

else{
  printf("Tamanho da fila: %d\n", NovaFila->tamanho);
}
break;

case 8:
if(NovaFila==NULL){
 printf("\nFila não existe, crie ela!\n");
}
else if(NovaFila->tamanho==0){
  printf("\nFila está vazia, o próximo item a ser inserido será o primeiro da fila\n");
}
else{printf("\nFila não está vazia, há %d itens na fila\n", NovaFila->tamanho);}
  
break;

  case 0:
printf("\nSaindo do programa!\n");
return -1;
break;

default:
printf("\nInsira uma opção válida\n");
break;
}
}

return 0;
}
