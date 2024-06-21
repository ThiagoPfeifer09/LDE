#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

int main() {

struct descp *NovaPilha = NULL;
int op, code=0;
struct musica *NovaMusica = NULL;
struct nodo *NovoElement = NULL;

while(op!=0){

printf("\n=================");
printf("\n1-Criar pilha\n");
printf("2-Inserir música\n");
printf("3-Consultar música\n");
printf("4-Imprimir pilha\n");
printf("5-Remover da pilha\n");
printf("6-Libera\n");
printf("0-Sair\n");
printf("=================\n");
scanf("%d", &op);

switch(op){
case 1:
if(NovaPilha == NULL){
NovaPilha=CriaDesc();
  if(NovaPilha!=NULL){
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
if(NovaPilha != NULL){
NovaMusica=CriaMusica();
NovoElement = CriaNodo(NovaMusica);
push(NovoElement, NovaPilha);
}
  else{
    printf("Crie a lista antes!");
  }

  
break;

case 3:
  if(NovaPilha!=NULL){
  printf("Digite o código da música para buscar na lista: ");
  scanf("%d", &code);
  ConsultaMusic(NovaPilha, code);
  }
  else{
    printf("Crie a lista antes!");
  }
break;

  
case 4:
  if(NovaPilha == NULL){
    printf("Crie a lista antes!");
  }
  else{
  imprime(NovaPilha);
  }
  
break;

case 5:
  if(NovaPilha!=NULL){
  pop(NovaPilha);
  }
else{
  printf("Lista não alocada");
}
  
break;

case 6:
  LiberaPilha(NovaPilha);
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
