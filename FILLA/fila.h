struct musica{
char titulo[256];
  char artista[256];
  char letra[256];
  int codigo;
  int execucoes;
}; 


struct nodo{
  struct nodo *prox;
  struct nodo *ant;
  struct musica *music;
};

struct descp{
  struct nodo *inicio;
  struct nodo *fim;
  int tamanho;
};


struct musica* CriaMusica();
struct descp* CriaFila();
struct nodo* CriaNodo(struct musica *NovaMusica);
void InsereFila(struct nodo *NovoElement, struct descp *NovaFila);
void imprime(struct descp *NovaFila);
void ConsultaMusic(struct descp* NovaFila, int code);
struct nodo *RemoveFila(struct descp *NovaFila);
void LiberaFila(struct descp *NovaFila);
