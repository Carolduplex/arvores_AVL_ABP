#define MAX 50
struct TNodoA
{
    char info[MAX];
    char mais_usada[MAX];
    struct TNodoA *esq;
    struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;

void toLowerCase(char *str);

pNodoA* cria_arvore(void);

pNodoA* consultaABP(pNodoA *a, char palavra[]);
pNodoA* InsereArvore(pNodoA *a, char ch[], char mais_uso[]);


int ContaNodos(pNodoA *a);
int alturaABP(pNodoA* a);
void ImprimepreFixadoEsq(pNodoA *a, int nivel);
int imprimeCompABP();


