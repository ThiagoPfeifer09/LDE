
struct musica{
char titulo[256];
  char artista[256];
  char letra[256];
  int codigo;
  int execucoes;
}; 


struct nodo{
  struct nodo *prox;
  struct musica *music;
};

struct descp{
  struct nodo *topo;
  int tamanho;
};


struct musica* CriaMusica();
struct descp* CriaDesc();
struct nodo* CriaNodo(struct musica *NovaMusica);
void push(struct nodo *NovoElement, struct descp *NovaPilha);
void imprime(struct descp *NovaPilha);
void ConsultaMusic(struct descp* NovaPilha, int code);
struct nodo *pop(struct descp *NovaPilha);
void LiberaPilha(struct descp *NovaPilha);

