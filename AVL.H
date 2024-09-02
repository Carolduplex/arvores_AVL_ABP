// ----------------------------// Estruturas //---------------------------- //
#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED
#define MAX 50
/*struct s_InfoNoAVL {
    char palavra[50];
    float nota;
};
typedef struct s_InfoNoAVL TipoInfoNoAVL;*/

struct TNodo{
    char palavra[MAX];
    char mais_usada[MAX];
    int FB;
    struct TNodo *esq;
    struct TNodo *dir;
};
typedef struct TNodo ptNodo;

// ----------------------------// Funcoes //---------------------------- //
ptNodo* cria_AVL(); // cria uma arvore vazia
ptNodo* InsereAVL(ptNodo *raiz, char palavra[], char mais_uso[], int *h); // dada uma arvore e um valor, insere um novo nodo
ptNodo* consulta_AVL(ptNodo *raiz, char palavra[]); // dado um numero, devolve o nodo que o contem, caso exista

ptNodo* rotacao_direita(ptNodo *nodo); // dada uma subarvore, faz uma rotacao simples para a direita
ptNodo* rotacao_esquerda(ptNodo *nodo); // dada uma subarvore, faz uma rotacao simples para a esquerda
ptNodo* rotacao_dupla_direita(ptNodo *nodo); // dada uma subarvore, faz uma rotacao dupla para a direita
ptNodo* rotacao_dupla_esquerda(ptNodo *nodo); // dada uma subarvore, faz uma rotacao dupla para a esquerda

int calcula_altura(ptNodo *nodo); // dado um nodo, calcula a sua altura
int calcula_fator(ptNodo *nodo); // dado um nodo, calcula seu fator

ptNodo* Caso2(ptNodo *a, int *h);//caso a rotação tenha que ser feita a direita
ptNodo* Caso1(ptNodo *a, int *h);//caso a rotação tenha que ser feita a esquerda

int caso_esq(ptNodo *nodo); // verifica se a rotacao a ser feita é simples ou dupla para a direita
int caso_dir(ptNodo *nodo); // verifica se a rotacao a ser feita é simples ou dupla para a esquerda

int Nodos_AVL();
int rotacoes_AVL();
void imprimeArvore(ptNodo *raiz, int k);

int imprimeCompAVL();

#endif

