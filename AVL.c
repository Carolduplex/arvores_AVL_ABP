// ------------------// Bibliotecas //------------------ //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"

// -------------------// Variáveis Globais // ------------------- //
int compAVL = 0;
int count = 0;
int count_nodos = 0;
int count_rot = 0;
// -------------------// Funcoes // ------------------- //
// Funcao cria arvore
ptNodo* cria_AVL() {
    return NULL;
}
int calcula_altura(ptNodo* nodo) {
    int altura_esq, altura_dir;

    if(nodo == NULL){
        return 0;
    } else {
        altura_dir = calcula_altura(nodo->dir);
        altura_esq = calcula_altura(nodo->esq);

        if(altura_dir > altura_esq){
            return (1 + altura_dir);
        } else {
            return (1 + altura_esq);
        }
    }
}

// Funcao calcula fator
int calcula_fator(ptNodo* nodo) {
    return (calcula_altura(nodo->esq) - calcula_altura(nodo->dir));
}


ptNodo* InsereAVL(ptNodo *a, char palavra[], char mais_uso[], int *h)
{
    if (a == NULL) {
        count_nodos++; // Incrementa apenas ao criar um novo nodo.
        a = (ptNodo*)malloc(sizeof(ptNodo));
        strcpy(a->palavra, palavra);
        strcpy(a->mais_usada, mais_uso);
        a->dir = NULL;
        a->esq = NULL;
        a->FB = 0;
        *h = 1;
    }
    else {
        if (strcmp(palavra, a->palavra) < 0) {
            a->esq = InsereAVL(a->esq, palavra, mais_uso, h);
            if (*h) {
                switch (a->FB) {
                    case -1: a->FB = 0; *h = 0; break;
                    case 0: a->FB = 1; break;
                    case 1: a = Caso1(a, h); count_rot++; break;
                }
            }
        }
        else {
            a->dir = InsereAVL(a->dir, palavra, mais_uso, h);
            if (*h) {
                switch (a->FB) {
                    case 1: a->FB = 0; *h = 0; break;
                    case 0: a->FB = -1; break;
                    case -1: a = Caso2(a, h); count_rot++; break;
                }
            }
        }
    }
    return a;
}
ptNodo* Caso1(ptNodo *a, int *h)
{
    ptNodo *z;

    z = a->esq;
    if(z->FB ==1){
        a = rotacao_direita(a);
    }
    else{
        a = rotacao_dupla_direita(a);
    }

    a->FB = 0;
    *h = 0;
    return a;
}
ptNodo* Caso2(ptNodo *a, int *h)
{
    ptNodo *z;

    z = a->dir;
    if(z->FB == -1){
        a = rotacao_esquerda(a);
    }
    else{
        a = rotacao_dupla_esquerda(a);
    }

    a->FB = 0;
    *h = 0;
    return a;

}
/*Toda vez que uma subárvore ficca com fator POSITIVO e sua subárvore a esquerda também fica com fator positivo
é ROTAÇÃO SIMPLES A DIREITA*/
ptNodo* rotacao_direita(ptNodo *p)
{
    ptNodo *u;

    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p=u;
    return p;
}

/*Toda vez que uma subarvore fica com fator negativo e sua subárvore a DIREITA fica com fator negativo
é ROTAÇÃO SIMPLES A ESQUERDA*/
ptNodo* rotacao_esquerda(ptNodo *p)
{
    ptNodo *z;

    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
}
/*Toda vez que uma subarvore fica com fator positivo e sua subárvore a esquerda fica com fator negativo
é ROTAÇÃO DUPLA A DIREITA*/

ptNodo* rotacao_dupla_direita(ptNodo *p)
{
    ptNodo *u, *v;

    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;

    if(v->FB == 1)
        p->FB = -1;
    else
        p->FB = 0;

    if(v->FB == -1)
        u->FB = 1;
    else
        u->FB = 0;

    p=v;
    return p;
}
/*Toda vez que uma subarvore fica com fator negativo e sua subárvore a DIREITA fica com fator positivo
é ROTAÇÃO DUPLA A ESQUERDA*/
ptNodo* rotacao_dupla_esquerda(ptNodo *p)
{
    ptNodo *z, *y;

    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;

    if(y->FB == -1)
        p->FB = 1;
        else
            p->FB = 0;

    if(y->FB == 1)
        z->FB = -1;
        else z->FB = 0;
    p=y;
    return p;
}


// Funcao consulta nodo
ptNodo* consulta_AVL(ptNodo* raiz, char palavra[]) {

    if(raiz == NULL){
        return NULL;
    } else {
        int comparacao = strcmp(palavra, raiz->palavra);
        if(comparacao == 0){
            compAVL++;
            return raiz;
        } else if(comparacao > 0){
            compAVL++;
            return consulta_AVL(raiz->esq, palavra);
        } else {
            compAVL++;
            return consulta_AVL(raiz->dir, palavra);
        }
    }
}
// FUNCOES DE VERIFICACOES
// Funcao caso esquerdo
int caso_esq(ptNodo* nodo) {
    if(calcula_fator(nodo->esq) > 0){
        return 0;
    } else {
        return 1;
    }
}

// Funcao caso direito
int caso_dir(ptNodo* nodo) {
    if(calcula_fator(nodo->dir) < 0){
        return 0;
    } else {
        return 1;
    }
}

void imprimeArvore(ptNodo *raiz, int k){
    if(raiz != NULL && count <= k){
        imprimeArvore(raiz->dir, k);
        count++;

        if(count <= k){
             printf("Palvra: %s\n", raiz->palavra);
        }

        imprimeArvore(raiz->esq, k);
    }

}
int Nodos_AVL()
{
    return count_nodos;
}

int rotacoes_AVL()
{
    return count_rot;
}

void reseta_count(){
    count = 0;
}

int imprimeCompAVL() {
    //printf("Numero de comparcoees usando uma Arvore Binaria de Pesquisa Balanceada(AVL): %d\n", compAVL);
    return compAVL;
}

