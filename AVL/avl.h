typedef struct no {
    struct no *parente;
    int valor;
    struct no *esquerda, *direita;
} arvore;

typedef struct descricao_avl {
    struct no *topo;
    int altura;
} descritor;

descritor *CriarDescritor();
arvore *AdicionarNo(arvore *topo, arvore *parente, int valor);
arvore *EncontrarMin(arvore *no);
arvore *rotacionarDireita(arvore *y);
arvore *rotacionarEsquerda(arvore *x);
arvore *ajustarBalanceamento(arvore *no);
void InserirRaiz(descritor *avl, int valor);
int maiorValor(int a, int b);
int obterAltura(arvore *no);
int calcularBalanceamento(arvore *no);
arvore *removerNoAuxiliar(arvore *topo, int valor);
void removerNo(descritor *avl, int valor);
void imprimirInOrder(arvore *topo);
void imprimirPreOrder(arvore *topo);
void imprimirPostOrder(arvore *topo);