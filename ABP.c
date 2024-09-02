#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "ABP.h"

int compABP = 0;

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

pNodoA* cria_arvore(void)
{
    return NULL;
}

pNodoA* InsereRaiz(pNodoA *a, char ch[], char mais_uso[])
{
    if (a == NULL)
    {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        strcpy(a->info, ch);
        strcpy(a->mais_usada, mais_uso);
        a->esq = NULL;
        a->dir = NULL;
    }
    return(a);
}

pNodoA* consultaABP(pNodoA *a, char palavra[])
{
    int cmp;
    while (a!=NULL)
    {
        compABP++;
        cmp = strcmp(palavra, a->info);
        //printf("%s\t%s\t%d\n",a->info, palavra, cmp);
        if (cmp == 0 ){
            compABP++;
            return a; //achou retorna o ponteiro para o nodo
        }
        else{
            compABP++;
            if(cmp > 0){
                a = a->esq;
            }
            else a = a->dir;
        }
    }
    return NULL; //não achou, retorna null
}

pNodoA* InsereArvore(pNodoA *a, char ch[], char mais_uso[])
{
    if (a == NULL)
    {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        strcpy(a->info, ch);
        strcpy(a->mais_usada, mais_uso);
        a->esq = NULL;
        a->dir = NULL;
    }

    int cmp = strcmp(ch, a->info);//compara o tamanho lexico da palavra do nodo atual e a palavra a ser inserida

    if(cmp > 0){
        a->esq = InsereArvore(a->esq,ch, mais_uso);//caso o tamanho lexico for menor que a inserida passa para o nodo da esqueda
    }
    else if(cmp < 0){
        a->dir = InsereArvore(a->dir,ch, mais_uso);//se o tamanho lexico for maior que a palavra do nodo atual vai para a direita
    }
    return a;
}
/*
pNodoA *InsereArvore (pNodoA *arv, char info, char mais_uso[]){
    if (arv == NULL){
        arv = (pNodoA*) malloc(sizeof(pNodoA));
        memcpy(&arv->nodoInfo,&info,sizeof(arv->nodoInfo));
        arv->esq = NULL;
        arv->dir = NULL;
        return arv;
    } else {
        int comparacao = comparaAlimento(arv->nodoInfo,info.alimento);
        if (comparacao < 0){
            arv->dir = insereABP(arv->dir, info);
        }
        else if(comparacao > 0){
            arv->esq = insereABP(arv->esq, info);
        }
    }

    return arv;
}*/

int ContaNodos(pNodoA *a)
{
    if (a==NULL)
        return 0;
    else
        return 1 + ContaNodos(a->esq) + ContaNodos(a->dir);

}

void ImprimepreFixadoEsq(pNodoA *a, int nivel)
{
    int i;

    if (a!= NULL)
    {
        for(i = 0; i < nivel; i++)
            printf("=");
        printf("%s\t%s\n",a->info, a->mais_usada);
        ImprimepreFixadoEsq(a->esq, nivel + 1);
        ImprimepreFixadoEsq(a->dir, nivel + 1);
    }
}

// Função para calcular a altura de uma árvore binária
int alturaABP(pNodoA* a) {
   int altEsq, altDir;

   if (a == NULL)
      return 0;

   else {
      altEsq = alturaABP (a->esq);
      altDir = alturaABP (a->dir);

      if (altEsq > altDir)
         return (1 + altEsq);
      else
         return (1 + altDir);
     }
}

int imprimeCompABP() {
    //printf("Numero de comparcoees usando uma Arvore Binaria de Pesquisa(ABP): %d\n", compABP);
    return compABP;
}

