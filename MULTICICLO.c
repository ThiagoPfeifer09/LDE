#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum classe_ints { tipo_R = 1, tipo_I, tipo_J, tipo_D };

struct instrucao {
  enum classe_ints tipo;
  char inst_char[17];  
  char dado_char[9];
  int opcode;
  int rs;
  int rt;
  int rd;
  int funct;
  int imm;
  int addr;
  int estados;
  char assembly[30];
  int dado;
};

struct memoria_instrucao {
  struct instrucao *mem;
  int tam;
};

struct memoria_dados {
  struct instrucao *mem_dado;
  int tamanho;
};

struct ResultadoULA {
  int flag;
  int result;
};

struct program_counter {
  int pc_decimal;
};

struct bancoRegistradores {
  struct regis *reg;
  int tamanho;
};

struct regis {
  int valor;
};

struct back {
  int regis[8];
  int pc_b;
  int memdados[256];
  int result;
  int flag;
  int dado;
  int estado_atual;
  int estado;
  int pc_temp;
  int rs, rt, rd, imm, opcode, funct, addr, A, B, tipo;
};

struct mem_inst_intermediario{
  int tipo;
  char inst_char[17];
  int opcode;
  int rs;
  int rt;
  int rd;
  int funct;
  int imm;
  int addr;
  char assembly[30];
  int A;
  int B;
};

struct mem_dado_intermediario{
  int dado;
  int tamanho;
};

struct PC_temp{
  int pc;
};

struct estado{
  int estado_atual;
  int est;
};

struct nodo{
  struct nodo *prox;
  struct back *backup;
};

struct descBC{
  struct nodo *topo;
  int tam;
};

//////////////////////////////////////////////////////////////////////////////////////////

//INICIALIZA E DECODIFICA INSTRUÇÕES
void iniciaregis(struct bancoRegistradores *registradores);
void iniciamem(struct memoria_dados *dados);
void bin_para_dec(struct memoria_instrucao *mem_inst, int imem);
void parser(struct memoria_instrucao *mem_inst);
void decode_dado(struct memoria_instrucao *mem_inst, int imem);

//////////////////////////////////////////////////////////////////////////////////////////

//FUNÇÕES DE IMPRESSÃO 
void imprimeinstruct(struct memoria_instrucao *mem_inst);
void imprimeMem(struct memoria_instrucao *mem);
void imprimeregist(struct bancoRegistradores *registradores);
void imprimePC(struct program_counter *pc);
void imprimeDados(struct memoria_dados *dados);
void imprime_simulador(struct memoria_instrucao *mem_inst, struct program_counter *pc,  struct mem_inst_intermediario *IR);
void instru_mem(struct memoria_instrucao *mem_inst);
void imprimeEstado(struct estado *estado);

//////////////////////////////////////////////////////////////////////////////////////////

//FUNCÕES DE EXECUTAR
void executaInst(struct mem_inst_intermediario *IR, struct mem_dado_intermediario *RDM, struct bancoRegistradores *registradores, struct PC_temp *ProgC);
struct ResultadoULA *ULA(int opcode, int funct, int rs, int rt);

struct ResultadoULA* controle(struct mem_inst_intermediario *IR, struct mem_dado_intermediario *RDM, struct bancoRegistradores *registradores, struct PC_temp *ProgC, struct estado *estado, struct memoria_instrucao *mem_inst, struct program_counter *pc, struct ResultadoULA *resultado, int *dado);

//////////////////////////////////////////////////////////////////////////////////////////

//BACKUP
struct back* grava_backup(struct bancoRegistradores *registradores, struct PC_temp *ProgC, struct estado *estado, struct memoria_instrucao *mem_inst, struct program_counter *pc, struct ResultadoULA *resultado, int *dado, struct mem_inst_intermediario *IR);

struct nodo* faz_backup(struct bancoRegistradores *registradores, struct PC_temp *ProgC, struct estado *estado, struct memoria_instrucao *mem_inst, struct program_counter *pc, struct ResultadoULA *resultado, int *dado, struct descBC *descBC, struct mem_inst_intermediario *IR);

struct descBC* CriaDesc();
struct nodo* CriaNodo(struct back *backup);
void push(struct descBC *descBC, struct nodo *NODO);
void imprime(struct descBC *descBC);

//////////////////////////////////////////////////////////////////////////////////////////

//SALVA EM ARQUIVOS
void le_mem(struct memoria_dados *dados);
void salvar_dados(struct memoria_dados *dados);
void para_assembly (struct memoria_instrucao *mem_inst);
void grava_assembly(struct memoria_instrucao *mem_inst);

//////////////////////////////////////////////////////////////////////////////////////////


int main() {

  struct instrucao *inst_atual = NULL;

  struct instrucao *mem_inst = NULL;
  mem_inst = (struct instrucao *)malloc(256*sizeof(struct instrucao));

  struct memoria_instrucao *mem = NULL;
  mem = (struct memoria_instrucao *)malloc(sizeof(struct memoria_instrucao));
  
  struct memoria_dados *memoriaDadoMIPS = NULL;
  memoriaDadoMIPS = (struct memoria_dados *)malloc(sizeof(struct memoria_dados));
  
  mem->mem = mem_inst;
  memoriaDadoMIPS->mem_dado = mem_inst; 
  
  iniciamem(memoriaDadoMIPS);

  struct program_counter *pc = NULL;
  pc = (struct program_counter *)malloc(sizeof(struct program_counter));
  pc->pc_decimal = 0;

  struct bancoRegistradores *registradores = NULL;
  registradores = (struct bancoRegistradores *)malloc(sizeof(struct bancoRegistradores));
  struct regis *registrador = NULL;
  registrador = (struct regis *)malloc(8 * sizeof(struct regis));
  registradores->reg = registrador;
  registradores->tamanho = 8;
  iniciaregis(registradores);

  struct ResultadoULA *resultado = NULL;
  resultado = (struct ResultadoULA *)malloc(sizeof(struct ResultadoULA));

  struct mem_dado_intermediario *RDM = NULL;
  RDM = (struct mem_dado_intermediario *)malloc(256*sizeof(struct mem_dado_intermediario));

  struct mem_inst_intermediario *IR = NULL;
  IR = (struct mem_inst_intermediario *)malloc(sizeof(struct mem_inst_intermediario));

  struct PC_temp *ProgC = NULL;
  ProgC = (struct PC_temp *)malloc(sizeof(struct PC_temp));
  ProgC->pc = 0;

  struct estado *estado = NULL;
  estado = (struct estado *)malloc(sizeof(struct estado));
  estado->estado_atual = 0;

  int *dado;
  dado = (int *)malloc(sizeof(int));

  struct descBC *descBC = NULL;
  struct nodo *NODO = NULL;
  struct back *backup = NULL;

  int i, v=0;
  int escolha = -1, ET=0;

  while (escolha != 0) {



    printf("\n||////////////// MINI MIPS /////////////||\n");
    printf("||\t1. Carregar memoria de instruções   ||\n");
    printf("||\t2. Imprimir memória                 ||\n");
   // printf("||\t3. Imprimir memoria de dados        ||\n");
    printf("||\t4. Imprimir registradores           ||\n");
    printf("||\t5. Imprimir todo o simulador        ||\n");
    printf("||\t6. Salvar .asm                      ||\n");
    printf("||\t7. Salvar.dat                       ||\n");
    printf("||\t8. Executar uma instrução (Step)    ||\n");
    printf("||\t9. Executar Programa (run)          ||\n");
    printf("||\t10.Voltar uma instrução (Back)      ||\n");
    printf("||\t11.Verificar pilha de step back     ||\n");
    printf("||\t12.Ver todas instruções da memoria  ||\n");
    printf("||\t13.Reiniciar o simulador(Zera tudo) ||\n");
    printf("||\t14.Zerar o PC                       ||\n");
    printf("||\t0- Sair                             ||\n");
    printf("||//////////////////////////////////////||\n");


    printf("\t\tInsira a opção desejada: ");
    scanf("%d", &escolha);
    switch (escolha) {
    case 0:
      printf("Saindo...");
      exit(-1);
      break;
    case 1:

      parser(mem);
      pc->pc_decimal = 0;
      descBC=CriaDesc();
      para_assembly(mem);
      // CarregarMemoria - carrega o arquivo .mem na memoria
      break;

    case 2:
      // Carrega a memoria de dados
       //le_mem(memoriaDadoMIPS);
      instru_mem(mem);

      break;

    case 3:
      imprimeDados(memoriaDadoMIPS);

      // ImprimirRegistradores imprime o banco de registradores
      break;

    case 4:
      imprimeregist(registradores);
      // ImprimirRegistradores imprime o banco de registradores
      break;

    case 5:
      // Imprime todo o simulador
      //imprimeinstruct(mem);
      //imprimeDados(memoriaDadoMIPS);
      imprime_simulador(mem, pc, IR);
      imprimeregist(registradores);
      imprimePC(pc);
      imprimeEstado(estado);
      
      printf("\n");
      break;

    case 6:
      grava_assembly(mem);
      // Salvar o arquivo .dat
      break;

    case 7:
      salvar_dados(memoriaDadoMIPS);
      // Ler o arquivo .dat
      break;

    case 8:
      // ExecutaPrograma
     backup = grava_backup(registradores, ProgC, estado, mem, pc, resultado, dado, IR);
      NODO=CriaNodo(backup);
      push(descBC, NODO);
      
     resultado = controle(IR, RDM, registradores, ProgC, estado, mem, pc, resultado, dado);
      
      break;

    case 9:
      //for (i = 0; i < p; i++) {
        while(ProgC->pc < mem->tam){
        backup = grava_backup(registradores, ProgC, estado, mem, pc, resultado, dado, IR);
          NODO=CriaNodo(backup);
          push(descBC, NODO);
          
        resultado = controle(IR, RDM, registradores, ProgC, estado, mem, pc, resultado, dado);
      }
      break;

    case 10:
      faz_backup(registradores, ProgC, estado, mem, pc, resultado, dado, descBC, IR);
      // VoltaUmaInstrucao decrementa 1 no PC
      break;
      
      case 11:
        if(descBC!=NULL)
          imprime(descBC);
        else
          printf("Não foi executa nennuma instruçao para que seja possível voltar! \n");
      break;
      
      case 12:
      instru_mem(mem);
      break;

      case 13:
      iniciaregis(registradores);
      iniciamem(memoriaDadoMIPS);
      pc->pc_decimal=0;
        for (int i = 0; i < 8; i++) {
          backup->regis[i] = 0;
        }
        backup->pc_b = 0;
        for (int j = 0; j < 256; j++) {
          backup->memdados[j] = 0;
        }
      mem->tam = 0;
      free(mem);
      estado->estado_atual = 0;
      estado->est = 0;
        
      break;

      case 14:
      pc->pc_decimal = 0;
      break;
     

    default:
      printf("Opção inválida! Digite uma das opções no menu!\n");
    }
  }
  return 0;
}

void parser(struct memoria_instrucao *mem_inst) {

  char nome_arq[20];

  /*printf("Digite o nome do arquivo a ser carregado (.mem) :\n");
   setbuf(stdin, NULL);
   scanf("%s", nome_arq);
   setbuf(stdin, NULL);
   FILE *arq = fopen(nome_arq, "r");
*/
  FILE *arq = fopen("divisao.mem", "r");
  //FILE *arq = fopen("testenegativo.mem", "r");
  //FILE *arq = fopen("multiplica.mem", "r");


  if (arq == NULL) {
    printf("Erro ao abrir o arquivo - %s - .\n", nome_arq);
    exit(1);
  }

  char charac;
  char linha[256];
  int i = 0;
  int imem = 0;
  while (fgets(linha, sizeof(linha), arq) != NULL) {
    linha[strcspn(linha, "\n")] = '\0';
    if (strlen(linha) == 8) {
        strcpy(mem_inst->mem[imem].dado_char, linha);
        decode_dado(mem_inst, imem);
    } else if (strlen(linha) == 16) {
        strcpy(mem_inst->mem[imem].inst_char, linha);
        bin_para_dec(mem_inst, imem);
    }
    imem++;
  }
  mem_inst->tam = imem;
  fclose(arq);
}

void decode_dado(struct memoria_instrucao *mem_inst, int imem) {
    int valor = 0;
    int pot = 7;
    for (int i = 0; i < 8; i++) {
        if (mem_inst->mem[imem].dado_char[i] == '1') {
            valor += (1 * pow(2, pot));
        }
        pot--;
    }
    mem_inst->mem[imem].dado = valor;
    mem_inst->mem[imem].tipo = tipo_D;
}

void bin_para_dec(struct memoria_instrucao *mem_inst, int imem) {
  int i, pot = 3;
  int valor, opdecimal = 0, rsdecimal = 0, rtdecimal = 0, rddecimal = 0,
             functdecimal = 0, addrdecimal = 0, immdecimal = 0, decimal = 0;

  for (i = 0; i < 4; i++) {
    if (mem_inst->mem[imem].inst_char[i] == '1') {
      valor = (1 * pow(2, pot));
      opdecimal = opdecimal + valor;
    }

    else {
      opdecimal = opdecimal + 0;
    }
    pot--;
  }
  mem_inst->mem[imem].opcode = opdecimal;


  if (opdecimal == 0) {
    mem_inst->mem[imem].tipo = tipo_R;
    pot = 2;
    for (i = 4; i < 7; i++) {
      if (mem_inst->mem[imem].inst_char[i] == '1') {
        valor = (1 * pow(2, pot));
        rsdecimal = rsdecimal + valor;
      }

      else {
        rsdecimal = rsdecimal + 0;
      }
      pot--;
    }
    mem_inst->mem[imem].rs = rsdecimal;

    pot = 2;
    for (i = 7; i < 10; i++) {
      // decodificar os rt
      if (mem_inst->mem[imem].inst_char[i] == '1') {
        valor = (1 * pow(2, pot));
        rtdecimal = rtdecimal + valor;
      }

      else {
        rtdecimal = rtdecimal + 0;
      }
      pot--;
    }
    mem_inst->mem[imem].rt = rtdecimal;

    pot = 2;
    for (i = 10; i < 13; i++) {
      // decodificar os rd
      if (mem_inst->mem[imem].inst_char[i] == '1') {
        valor = (1 * pow(2, pot));
        rddecimal = rddecimal + valor;
      }

      else {
        rddecimal = rddecimal + 0;
      }
      pot--;
    }
    mem_inst->mem[imem].rd = rddecimal;

    pot = 2;
    for (i = 13; i < 16; i++) {
      // decodificar os funct
      if (mem_inst->mem[imem].inst_char[i] == '1') {
        valor = (1 * pow(2, pot));
        functdecimal = functdecimal + valor;
      }

      else {
        functdecimal = functdecimal + 0;
      }
      pot--;
    }
    mem_inst->mem[imem].funct = functdecimal;
  }

  // TIPO J
  if (opdecimal == 2) {
    mem_inst->mem[imem].tipo = tipo_J;
    pot = 5;
    for (i = 10; i < 16; i++) {
      if (mem_inst->mem[imem].inst_char[i] == '1') {
        valor = (1 * pow(2, pot));
        addrdecimal = addrdecimal + valor;
      }

      else {
        addrdecimal = addrdecimal + 0;
      }
      pot--;
    }
    mem_inst->mem[imem].addr = addrdecimal;
  }

  // TIPO I
  else if (opdecimal == 4 || opdecimal == 11 || opdecimal == 15 ||opdecimal == 8) {
    mem_inst->mem[imem].tipo = tipo_I;

    pot = 2;
    for (i = 4; i < 7; i++) {
      if (mem_inst->mem[imem].inst_char[i] == '1') {
        valor = (1 * pow(2, pot));
        rsdecimal = rsdecimal + valor;
      }

      else {
        rsdecimal = rsdecimal + 0;
      }
      pot--;
    }
    mem_inst->mem[imem].rs = rsdecimal;

    pot = 2;
    for (i = 7; i < 10; i++) {
      if (mem_inst->mem[imem].inst_char[i] == '1') {
        valor = (1 * pow(2, pot));
        rtdecimal = rtdecimal + valor;
      }

      else {
        rtdecimal = rtdecimal + 0;
      }
      pot--;
    }
    mem_inst->mem[imem].rt = rtdecimal;


    pot = 5;
        int sinal = 1;
        if (mem_inst->mem[imem].inst_char[10] == '1') { 
            sinal = -1;

            for (i = 10; i < 16; i++) {
                if (mem_inst->mem[imem].inst_char[i] == '0') {
                    mem_inst->mem[imem].inst_char[i] = '1';
                } else {
                    mem_inst->mem[imem].inst_char[i] = '0';
                }
            }

            int carry = 1;
            for (i = 15; i >= 10; i--) {
                if (mem_inst->mem[imem].inst_char[i] == '0' && carry == 1) {
                    mem_inst->mem[imem].inst_char[i] = '1';
                    carry = 0;
                } else if (mem_inst->mem[imem].inst_char[i] == '1' && carry == 1) {
                    mem_inst->mem[imem].inst_char[i] = '0';
                }
            }
        }

        for (i = 10; i < 16; i++) {
            if (mem_inst->mem[imem].inst_char[i] == '1') {
                valor = (1 * pow(2, pot));
                immdecimal = immdecimal + valor;
            } else {
                immdecimal = immdecimal + 0;
            }
            pot--;
        }

        mem_inst->mem[imem].imm = immdecimal * sinal;
    }
}
/*
void executaInst(struct mem_inst_intermediario *IR, struct mem_dado_intermediario *RDM, struct bancoRegistradores *registradores, struct PC_temp *ProgC) {

  struct ResultadoULA *resul = NULL;

  if (inst_atual->tipo == tipo_J) {
    pc->pc_decimal = inst_atual->addr;
  }

  if (inst_atual->tipo == tipo_R) {
    resul = ULA(inst_atual->opcode, inst_atual->funct, registradores->reg[inst_atual->rs].valor, registradores->reg[inst_atual->rt].valor);

    registradores->reg[inst_atual->rd].valor = resul->result;

    pc->pc_decimal++;
  }

  if (inst_atual->tipo == tipo_I) {
    resul = ULA(inst_atual->opcode, inst_atual->funct, registradores->reg[inst_atual->rs].valor, inst_atual->imm);

    if (inst_atual->opcode == 4) {
      registradores->reg[inst_atual->rt].valor = resul->result;
      pc->pc_decimal++;
    }

    if (inst_atual->opcode == 8) {
      if (registradores->reg[inst_atual->rt].valor == registradores->reg[inst_atual->rs].valor) {
        pc->pc_decimal = pc->pc_decimal+inst_atual->imm;
      } 
      else {
        pc->pc_decimal++;
      }
    }

    if (inst_atual->opcode == 11) {
      registradores->reg[inst_atual->rt].valor = dados->mem_dado[resul->result].dado;
      pc->pc_decimal++;
    }

    if (inst_atual->opcode == 15) {
      dados->mem_dado[resul->result].dado = registradores->reg[inst_atual->rt].valor;
      pc->pc_decimal++;
    }
  }
}
*/
struct ResultadoULA *ULA(int opcode, int funct, int rs, int rt) {

  struct ResultadoULA *resul = (struct ResultadoULA *)malloc(sizeof(struct ResultadoULA));

  resul->flag = 0;

  switch (opcode) {
  case 0:
    switch (funct) {
    case 0:
      resul->result = rs + rt;
      break;

    case 2:
      resul->result = rs - rt;
      break;

    case 4:
      resul->result = rs & rt;
      break;

    case 5:
      resul->result = rs | rt;
      break;
    }
    break;

  case 8:
    resul->result = 0;
    if (rs == rt) {
      resul->flag = 1;
    } else {
      resul->flag = 0;
    }
    break;

  case 4:
  case 11:
  case 15:
    resul->result = rs + rt;
    break;
  }

  if (resul->result > 31 || resul->result < -32){
    resul->flag = 1;}
  return resul;
}

void imprimeDados(struct memoria_dados *dados) {
  int i;
  printf("\nMemoria de Dados:\n");
  for (i = 0; i < 256; i++) {
    printf("%2d ", dados->mem_dado[i].dado);
    if ((i + 1) % 16 == 0) {
      printf("\n");
    }
  }
  printf("\n");
}

void imprimePC(struct program_counter *pc) {
  printf("\nPC atual: %d\n\n", pc->pc_decimal);
}

void imprimeregist(struct bancoRegistradores *registradores) {
  int i;
  printf("\nBANCO REGISTRADORES:\n");
  for (i = 0; i < 8; i++) {
    printf("Registrador %d: [ %d ]\n", i, registradores->reg[i].valor);
  }
}

void imprimeinstruct(struct memoria_instrucao *mem_inst) {

  for (int i = 0; i < mem_inst->tam; i++) {

    printf("\n\nInstrução: [%s]\t", mem_inst->mem[i].inst_char);
    printf("ASSEMBLY: [%s]\t", mem_inst->mem[i].assembly);
    printf("TIPO: [%d]\n", mem_inst->mem[i].tipo);
    printf("OPCODE: [%d]\t", mem_inst->mem[i].opcode);
    printf("RS: [%d]\t", mem_inst->mem[i].rs);
    printf("RT: [%d]\t", mem_inst->mem[i].rt);
    printf("RD: [%d]\t", mem_inst->mem[i].rd);
    printf("\nFUNCT: [%d]\t", mem_inst->mem[i].funct);
    printf("IMM: [%d]\t", mem_inst->mem[i].imm);
    printf("ADDR: [%d]\n\n", mem_inst->mem[i].addr);
  }
  printf("\n\n");
}

void iniciaregis(struct bancoRegistradores *registradores) {
  for (int i = 0; i < 8; i++) {
    registradores->reg[i].valor = 0;
  }
}

void iniciamem(struct memoria_dados *dados) {
  for (int i = 0; i < 256; i++) {
    dados->mem_dado[i].dado = 0;
  }
}

void le_mem(struct memoria_dados *dados) {
  FILE *arq;
  char nome_arq[20];
  int i;

  /*  printf("Digite o nome do arquivo a ser carregado (.dat) :\n");
    setbuf(stdin, NULL);
    scanf("%s", nome_arq);
    setbuf(stdin, NULL);*/

  arq = fopen("dados.dat", "r");

  if (arq == NULL) {
    printf("Erro ao abrir o arquivo - %s - .\n", nome_arq);
    exit(1);
  }

  for (i = 0; i < 256; i++) {
    fscanf(arq, "%d", &dados->mem_dado[i].dado);
  }
  fclose(arq);
}

void salvar_dados(struct memoria_dados *dados) {
  FILE *dado;
  char nome_arq[20];
  int i;

  /*printf("Digite o nome do arquivo a ser carregado (.dat) :\n");
  setbuf(stdin, NULL);
  scanf("%s", nome_arq);
  setbuf(stdin, NULL);*/
  dado = fopen("dados.dat", "w");

  if (dado == NULL) {
    printf("erro ao abrir o arquivo, tente novamente\n");
    exit(1);
  }

  for (i = 0; i < 256; i++) {
    fprintf(dado, "%d\n", dados->mem_dado[i].dado);
  }

  fclose(dado);
}


void para_assembly(struct memoria_instrucao *mem_inst){
int i;


  for(i = 0; i < mem_inst->tam; i++){

   if(mem_inst->mem[i].opcode==0 && mem_inst->mem[i].funct==0){
        sprintf(mem_inst->mem[i].assembly,"add $%d, $%d, $%d",mem_inst->mem[i].rd, mem_inst->mem[i].rs, mem_inst->mem[i].rt);
        mem_inst->mem[i].estados = 4;
        //add $ $ $
   }

      if(mem_inst->mem[i].opcode==0 && mem_inst->mem[i].funct==2){
        sprintf(mem_inst->mem[i].assembly,"sub $%d, $%d, $%d",mem_inst->mem[i].rd, mem_inst->mem[i].rs, mem_inst->mem[i].rt);
        mem_inst->mem[i].estados = 4;
        //sub $ $ $
      }

    if(mem_inst->mem[i].opcode==0 && mem_inst->mem[i].funct==4){
        sprintf(mem_inst->mem[i].assembly,"and $%d, $%d, $%d",mem_inst->mem[i].rd, mem_inst->mem[i].rs, mem_inst->mem[i].rt);
      mem_inst->mem[i].estados = 4;
        //and $ $ $
    }

    if(mem_inst->mem[i].opcode==0 && mem_inst->mem[i].funct==5){
        sprintf(mem_inst->mem[i].assembly,"or $%d, $%d, $%d",mem_inst->mem[i].rd, mem_inst->mem[i].rs, mem_inst->mem[i].rt);
      mem_inst->mem[i].estados = 4;
        //or $ $ $
    }

    if(mem_inst->mem[i].opcode==2){
      sprintf(mem_inst->mem[i].assembly, "j %d", mem_inst->mem[i].addr);
      mem_inst->mem[i].estados = 3;
      //j $
    }

    if(mem_inst->mem[i].opcode==8){
      sprintf(mem_inst->mem[i].assembly,"beq $%d, $%d, %d",mem_inst->mem[i].rt,mem_inst->mem[i].rs,mem_inst->mem[i].imm);
      mem_inst->mem[i].estados = 3;
      //beq $ $ $
    }

    if(mem_inst->mem[i].opcode==4){
      sprintf(mem_inst->mem[i].assembly,"addi $%d, %d, %d",mem_inst->mem[i].rt,mem_inst->mem[i].rs,mem_inst->mem[i].imm);
      mem_inst->mem[i].estados = 4;
      //addi $ $ $
    }

    if(mem_inst->mem[i].opcode==11){
      sprintf(mem_inst->mem[i].assembly,"lw $%d %d($%d)", mem_inst->mem[i].rt,mem_inst->mem[i].imm,mem_inst->mem[i].rs);
      mem_inst->mem[i].estados = 5;
      //lw $ $ $
    }

    if(mem_inst->mem[i].opcode==15){
      sprintf(mem_inst->mem[i].assembly,"sw $%d %d($%d)", mem_inst->mem[i].rt,mem_inst->mem[i].imm,mem_inst->mem[i].rs);
      mem_inst->mem[i].estados = 4;
      //sw $ $ $
    }
  }
}

void grava_assembly(struct memoria_instrucao *mem_inst){

  FILE *arquivo;
  char nome_arq[20];
  int i;

  /*printf("Digite o nome do arquivo a ser carregado (.dat) :\n");
  setbuf(stdin, NULL);
  scanf("%s", nome_arq);
  setbuf(stdin, NULL);*/
  arquivo = fopen("assembly.asm", "w");

  if (arquivo == NULL) {
    printf("erro ao abrir o arquivo, tente novamente\n");
    exit(1);
  }

  for (i = 0; i < mem_inst->tam; i++) {
    fprintf(arquivo, "%s\n", mem_inst->mem[i].assembly);
  }

  fclose(arquivo);
}

void imprime_simulador(struct memoria_instrucao *mem_inst, struct program_counter *pc,  struct mem_inst_intermediario *IR){

  int i;
  i=pc->pc_decimal;
if(mem_inst->mem[i].tipo==tipo_R){
    printf("\n\n\n//////////EM USO//////////\n");
    printf("\nInstrução: [%s]\t", mem_inst->mem[i].inst_char);
    printf("ASSEMBLY: [%s]\n", mem_inst->mem[i].assembly);
    printf("OPCODE: [%d]\t", mem_inst->mem[i].opcode);
    printf("RS: [%d]\t", mem_inst->mem[i].rs);
    printf("RT: [%d]\t", mem_inst->mem[i].rt);
    printf("RD: [%d]\t", mem_inst->mem[i].rd);
    printf("FUNCT: [%d]\n", mem_inst->mem[i].funct);
    printf("\tESTADOS: [%d]\n", mem_inst->mem[i].estados);
    printf("EM IR rs[%d], rt[%d], rd[%d]\n", IR[pc->pc_decimal].rs, IR[pc->pc_decimal].rt, IR[pc->pc_decimal].rd);
    printf("//////////////////////////\n\n");
}
  if(mem_inst->mem[i].tipo==tipo_I){
      printf("\n\n\n//////////EM USO//////////");
      printf("\n\nInstrução: [%s]\t", mem_inst->mem[i].inst_char);
      printf("ASSEMBLY: [%s]\n", mem_inst->mem[i].assembly);
      printf("OPCODE: [%d]\t", mem_inst->mem[i].opcode);
      printf("RS: [%d]\t", mem_inst->mem[i].rs);
      printf("RT: [%d]\t", mem_inst->mem[i].rt);
      printf("IMM: [%d]\t", mem_inst->mem[i].imm);
      printf("ESTADOS: [%d]\n\n", mem_inst->mem[i].estados);
      printf("//////////////////////////\n\n");
  }
  if(mem_inst->mem[i].tipo==tipo_J){
      printf("\n\n\n//////////EM USO/////////");
      printf("\n\nInstrução: [%s]\t", mem_inst->mem[i].inst_char);
      printf("OPCODE: [%d]\t", mem_inst->mem[i].opcode);
      printf("ASSEMBLY: [%s]\n", mem_inst->mem[i].assembly);
      printf("ADDR: [%d]\t", mem_inst->mem[i].addr);
      printf("ESTADOS: [%d]\n\n", mem_inst->mem[i].estados);
      printf("//////////////////////////\n\n");
  }
}


void instru_mem(struct memoria_instrucao *mem_inst){
int i=0;
printf("\n\n");
for(i=0; i<mem_inst->tam; i++){
  if(mem_inst->mem[i].tipo==tipo_D){
    printf("%d - DADO\t",i);
    printf("[%d]\n", mem_inst->mem[i].dado);
  }
  else{
  printf("%d - [%s]\t",i ,mem_inst->mem[i].inst_char);
  printf("Assembly: [%s]\t", mem_inst->mem[i].assembly);
  printf("Estados [%d]\n", mem_inst->mem[i].estados);
  }
}
  printf("\n\n");

}

void imprimeEstado(struct estado *estado){
  printf("\n||                     ||");
  printf("\n|| Estado executado: %d ||", estado->est);
  printf("\n|| Próximo estado: %d   ||", estado->estado_atual);
  printf("\n||                     ||\n");
}

struct ResultadoULA* controle(struct mem_inst_intermediario *IR, struct mem_dado_intermediario *RDM, struct bancoRegistradores *registradores, struct PC_temp *ProgC, struct estado *estado, struct memoria_instrucao *mem_inst, struct program_counter *pc, struct ResultadoULA *resultado, int *dado){

  int i=0, est=0;
  
  //ESTADO DE BUSCA GERAL
  if(estado->estado_atual == 0){
   
ProgC->pc=pc->pc_decimal;  
resultado = ULA(0, 0, pc->pc_decimal, 1);
pc->pc_decimal=resultado->result; 

    
if(mem_inst->mem[ProgC->pc].tipo == tipo_D){
  return resultado;
}

    else{
   resultado=ULA(mem_inst->mem[ProgC->pc].opcode, mem_inst->mem[ProgC->pc].funct, registradores->reg[mem_inst->mem[ProgC->pc].rs].valor, registradores->reg[mem_inst->mem[ProgC->pc].rt].valor);
    //calculo endereço do BEQ

  estado->est=estado->estado_atual;
    
  estado->estado_atual = 1; 
    imprimeEstado(estado);
    }
    
    return resultado;
}

  //ESTADO DE DECODICAÇÃO GERAL
  if(estado->estado_atual == 1){

  strcpy(IR->inst_char, mem_inst->mem[ProgC->pc].inst_char);
  IR->opcode = mem_inst->mem[ProgC->pc].opcode;
  IR->funct = mem_inst->mem[ProgC->pc].funct;
  IR->rs = mem_inst->mem[ProgC->pc].rs;
  IR->rt = mem_inst->mem[ProgC->pc].rt;
  IR->rd = mem_inst->mem[ProgC->pc].rd;
  IR->imm = mem_inst->mem[ProgC->pc].imm;
  IR->addr = mem_inst->mem[ProgC->pc].addr;
  strcpy(IR->assembly, mem_inst->mem[ProgC->pc].assembly);
  IR->tipo = mem_inst->mem[ProgC->pc].tipo;
  IR->A = registradores->reg[IR->rs].valor;
  IR->B = registradores->reg[IR->rt].valor;
  
  estado->est = estado->estado_atual;
    
  //será substitudo por switchs 
    if(IR->opcode==0){
      estado->estado_atual = 7;
    }

    if(IR->opcode == 11 || IR->opcode == 4 || IR->opcode == 15){  
      estado->estado_atual = 2;
    }

    if(IR->opcode==8){  
      estado->estado_atual = 9;
    }

    if(IR->opcode==2){  
      estado->estado_atual = 10;
    }
    imprimeEstado(estado);
    
    return resultado;
}

  //ADDI, LW E SW 3º ESTADO
  if(estado->estado_atual == 2){

 //Chama a ULA, para SOMAR o IMM com o RS 
  
  resultado = ULA(IR->opcode, IR->funct, IR->rs, IR->imm);
  
    estado->est= estado->estado_atual;
    
    if(IR->opcode==11){
      estado->estado_atual = 3;
    }
      
    if(IR->opcode==4){ 
      estado->estado_atual = 6;
    }
      
    if(IR->opcode==15){ 
      estado->estado_atual = 5;
    }
    imprimeEstado(estado);

    return resultado;
}

  
//LW 4º ESTADO
  if(estado->estado_atual == 3){

    //pega o resultado da soma de IMM com RS e pega o dado da memoria desse endereço
    *dado = mem_inst->mem[resultado->result].dado;
    estado->est = estado->estado_atual;  
    estado->estado_atual = 4;
    imprimeEstado(estado);

    return resultado;
}



  //LW ULTIMO ESTADO
  if(estado->estado_atual == 4){
// registradores->reg[inst_atual->rt].valor = dados->mem_dado[resul->result].dado;
//Após pegar o dado da memoria, salva em RT e volta ao estado 0, para executar a prox inst
    
  registradores->reg[IR->rt].valor = *dado;
    estado->est= estado->estado_atual;
  estado->estado_atual = 0;
  
    imprimeEstado(estado);

    return resultado;
}


  //SW ULTIMO ESTADO 
  if(estado->estado_atual == 5){

    //Salva o dado em RT no endereço de RS+IMM, e volta ao estado 0 para executar a prox inst
  mem_inst->mem[resultado->result].tipo = tipo_D;
  mem_inst->tam++;
    
  mem_inst->mem[resultado->result].dado = registradores->reg[IR->rt].valor;
  
  estado->est=estado->estado_atual;
  estado->estado_atual = 0;
    imprimeEstado(estado);
    
    return resultado;
}



  //ADDI ULTIMO ESTADO
  if(estado->estado_atual == 6){

  //Guarda a soma do addi em rt, e volta para estado 0 
  registradores->reg[IR->rt].valor = resultado->result;
    estado->est= estado->estado_atual;
  estado->estado_atual = 0;
    imprimeEstado(estado);

    return resultado;
}



  //3º ESTADO P/ TIPO R
  if(estado->estado_atual == 7){
      
  //CHAMA A ULA e faz a operação que precise entre RS e RT
    resultado = ULA(IR->opcode, IR->funct, IR->A, IR->B);
    printf("%d", resultado->result);
    estado->est= estado->estado_atual;
  estado->estado_atual = 8;
    imprimeEstado(estado);

    return resultado;
}



  //4º E ULTIMO ESTADO PARA TIPO R
  if(estado->estado_atual == 8){
  //Guarda o resultado em rd e volta ao estado 0
  registradores->reg[IR->rd].valor = resultado->result;
  
    estado->est=estado->estado_atual;
  estado->estado_atual = 0;
    imprimeEstado(estado);
    return resultado;
}


  //BEQ 3 e ULTIMO estado
  if(estado->estado_atual == 9){
    //Compara RS e RT, desvia a instrução para pc+imm e volta ao estado 0
     if(resultado->flag == 1){
       pc->pc_decimal = pc->pc_decimal + IR->imm;
     }
    
    estado->est= estado->estado_atual;
  estado->estado_atual = 0;
      imprimeEstado(estado);
    return resultado;
}

  

 //JUMP 3º e ULTIMO estado
 if(estado->estado_atual == 10){
   pc->pc_decimal = IR->addr;
 
   estado->est= estado->estado_atual;
  estado->estado_atual = 0;
   imprimeEstado(estado);

    return resultado;
  } 
  return resultado;
}

struct descBC* CriaDesc(){

  struct descBC *pilha_back = (struct descBC* )malloc(sizeof(struct descBC));

    pilha_back->tam=0;
    pilha_back->topo=NULL;

  return pilha_back;
}

struct nodo* CriaNodo(struct back *backup){

struct nodo *novoNodo = (struct nodo *)malloc(sizeof(struct nodo));

novoNodo->backup=backup;
novoNodo->prox=NULL;

return novoNodo;
}

void push(struct descBC *descBC, struct nodo *NODO){

NODO->prox = descBC->topo;
descBC->topo = NODO;
descBC->tam++;

}


struct back* grava_backup(struct bancoRegistradores *registradores, struct PC_temp *ProgC, struct estado *estado, struct memoria_instrucao *mem_inst, struct program_counter *pc, struct ResultadoULA *resultado, int *dado, struct mem_inst_intermediario *IR) {

  struct back *VOLTA = (struct back *)malloc(sizeof(struct back));

    VOLTA->pc_b = pc->pc_decimal;
    VOLTA->pc_temp = ProgC->pc;

  for (int i = 0; i < 8; i++) {
      VOLTA->regis[i] = registradores->reg[i].valor;
  }

    VOLTA->estado = estado->est ;
    VOLTA->estado_atual= estado->estado_atual;

    VOLTA->dado=*dado;

    VOLTA->result=resultado->result;
    VOLTA->flag=resultado->flag;

    VOLTA->opcode=IR->opcode;
    VOLTA->funct=IR->funct;
    VOLTA->rs=IR->rs;
    VOLTA->rt=IR->rt;
    VOLTA->rd=IR->rd;
    VOLTA->imm=IR->imm;
    VOLTA->addr=IR->addr;
    VOLTA->tipo=IR->tipo;
    VOLTA->A=IR->A;
    VOLTA->B=IR->B;

  return VOLTA;
}

struct nodo* faz_backup(struct bancoRegistradores *registradores, struct PC_temp *ProgC, struct estado *estado, struct memoria_instrucao *mem_inst, struct program_counter *pc, struct ResultadoULA *resultado, int *dado, struct descBC *descBC, struct mem_inst_intermediario *IR) {

  struct nodo *aux = descBC->topo;

  //fazendo o backup de tudo oq foi utilizado na execução
  pc->pc_decimal = descBC->topo->backup->pc_b;
  ProgC->pc = descBC->topo->backup->pc_temp;

  for (int i = 0; i < 8; i++) {
    registradores->reg[i].valor = descBC->topo->backup->regis[i];
  }
  
  estado->est = descBC->topo->backup->estado;
  estado->estado_atual=descBC->topo->backup->estado_atual;

  *dado=descBC->topo->backup->dado;

  resultado->result=descBC->topo->backup->result;
  resultado->flag=descBC->topo->backup->flag;
  
  IR->opcode=descBC->topo->backup->opcode;
  IR->funct=descBC->topo->backup->funct;
  IR->rs=descBC->topo->backup->rs;
  IR->rt=descBC->topo->backup->rt;
  IR->rd=descBC->topo->backup->rd;
  IR->imm=descBC->topo->backup->imm;
  IR->addr=descBC->topo->backup->addr;
  IR->tipo=descBC->topo->backup->tipo;
  IR->A=descBC->topo->backup->A;
  IR->B = descBC->topo->backup->B;

  
  //fazendo o pop deste elemento
  descBC->topo=descBC->topo->prox;
  descBC->tam--;

 
  
return aux;
}

void imprime(struct descBC *descBC){
struct nodo *aux=descBC->topo;

while(aux!=NULL){
  printf("\nPC [%d]\t", aux->backup->pc_b);
  printf("PC Temp [%d]\t", aux->backup->pc_temp);
  printf("Flag [%d]\n", aux->backup->flag);
  printf("Resultado [%d]\t", aux->backup->result);
  printf("Estado atual [%d]\t\n", aux->backup->estado);
  printf("Próximo Estado [%d]\t\n", aux->backup->estado_atual);
  aux = aux->prox;
}
printf("\n");
}

