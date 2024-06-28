#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

int main() {

struct descp *NovaPilha = NULL;
int op, code=0;
struct musica *NovaMusica = NULL;
struct nodo *NovoElement = NULL;
char titulo[256];

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
  if (NovaPilha != NULL && NovaPilha->tamanho > 0) {
    printf("Digite o título da música para buscar na pilha: ");
    getchar(); // Limpar o buffer
    fgets(titulo, 256, stdin);
    titulo[strcspn(titulo, "\n")] = '\0'; // Remover nova linha
    ConsultaMusica(NovaPilha, titulo);
  } else {
    printf("\nCrie a pilha e adicione músicas antes!\n");
  }
break;


case 4:
  if(NovaPilha == NULL){
    printf("\nCrie a lista antes!\n");
  }
  else if (NovaPilha->tamanho == 0){
    printf("\nNão há itens na PILHA\n");
  }
  else{
  imprime(NovaPilha);
  }

break;

case 5:
  if(NovaPilha!=NULL && NovaPilha->tamanho!=0){
  pop(NovaPilha);
  }
else{
  printf("Lista não alocada ou sem músicas!");
}

break;

case 6:
  if(NovaPilha != NULL && NovaPilha->tamanho>0)
  LiberaPilha(NovaPilha);
  else{
    printf("Lista não alocada");
  }
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
