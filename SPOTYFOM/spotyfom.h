
struct musica {
  char titulo[256];
  char artista[256];
  char letra[256];
  int codigo;
  int execucoes;
};

//NODO E DESC DA LDE
struct nodo{
  struct nodo *prox, *ant;
  struct musica *info;
};

struct desc{
  struct nodo *inicio;
  struct nodo *fim;
  int tamanho;
};

//NODO E DESC DA PILHA 
struct nodo_pilha{
  struct nodo_pilha *prox;
  struct musica *music;
};

struct desc_pilha{
  struct nodo_pilha *topo;
  int tamanho;
};

//NODO E DESC DA FILA
struct nodo_fila {
  struct nodo_fila *prox;
  struct nodo_fila *ant;
  struct musica *music;
};

struct desc_fila {
  struct nodo_fila *inicio;
  struct nodo_fila *fim;
  int tamanho;
};

//FUNÇÕES DA LDE
struct desc *CriaLista();
struct musica *CriaMusica(char *titulo, char *artista, char *letra, int codigo);
void inserirMusica(struct desc *minhaLista, struct musica *novaMusica, int posicao);
void imprimirLista(struct desc *MinhaLista);
void carregarAcervo(struct desc *MinhaLista, char *nome_arq);
void imprimirMenu(struct desc *MinhaLista, int quant, int start);
void imprimirRange(struct desc *MinhaLista, int inicio, int fim);
struct musica *consultarMusicaPorTitulo(struct desc *MinhaLista, const char *titulo);

//FUNÇÕES DA PILHA


//FUNÇÕES DA FILA
struct desc_fila *CriaFila();
void InsereFila(struct nodo_fila *NodoFila, struct desc_fila *NovaFila);
struct musica *MusicaFila();
struct nodo_fila *CriaNodoFila(struct musica *Nova_Musica);
void imprime(struct desc_fila *NovaFila);
void criarPlaylistAleatoria(struct desc *MinhaLista, struct desc_fila *NovaFila, int tam);
void ImprimeMusica(struct musica *music);
void imprimeFILA(struct desc_fila *NovaFila); 
