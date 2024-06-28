struct music {
    char titulo[256];
    char artista[256];
    char letra[256];
    int codigo;
    int execucoes;
};

struct nodo_LDE {
    struct nodo_LDE *prox, *ante;
    struct music *info;
};

struct desc_LDE {
    struct nodo_LDE *inicio, *fim;
    int tamanho;
};


struct music* criarMusica(const char *titulo, const char *artista, const char *letra, int codigo, int execucoes);
struct desc_LDE *criarLista();
void inserirMusica(struct desc_LDE *minhaLista, struct nodo_LDE *novoNodo, int posicao);
struct music *consultarMusica(struct desc_LDE *minhaLista, int codigo);
void removerMusica(struct desc_LDE *minhaLista, int codigo);
void liberarLista(struct desc_LDE *minhaLista);
void imprimirLista(struct desc_LDE *minhaLista);
struct nodo_LDE* CriaNodo(struct music *novaMusica);
struct music *consultarMusicaPorTitulo(struct desc_LDE *minhaLista, const char *titulo);
