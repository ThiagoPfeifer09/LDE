
struct music {
    char titulo[256];
    char artista[256];
    char letra[256];
    int codigo;
    int execucoes;
};

struct nodo_LSE {
    struct nodo_LSE *prox;
    struct music *info;
};

struct desc_LSE {
    struct nodo_LSE *inicio;
    int tamanho;
};


struct music *criarMusica(const char *titulo, const char *artista, const char *letra, int codigo, int execucoes);
struct desc_LSE *criarLista();
void inserirMusica(struct desc_LSE *minhaLista, struct music *novaMusica, int posicao);
struct music *consultarMusica(struct desc_LSE *minhaLista, int codigo);
void removerMusica(struct desc_LSE *minhaLista, int codigo);
void liberarLista(struct desc_LSE *minhaLista);
void imprimirLista(struct desc_LSE *minhaLista);

