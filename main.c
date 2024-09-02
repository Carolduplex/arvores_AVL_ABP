/* Programa desenvolvido por Leandra Machado e Ana Caroline de Jesus
   no intuito de concluir o trabalho da disciplina Estrutura de Dados
   10 de Agosto de 2024 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "AVL.h"
#include "ABP.h"

// Função para abrir arquivos e verificar erros
FILE* openFile(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        exit(1);
    }
    return file;
}

// Função para processar o dicionário
void processDictionary(FILE* dicionario, pNodoA** avl, ptNodo** abp) {
    char linha[1000];
    char* palavra;
    char* palavra2;

    int aH=0;
    while (fgets(linha, sizeof(linha), dicionario)) {
        palavra = strtok(linha, "\t\n");
        palavra2 = strtok(NULL, "\t\n");
        while (palavra != NULL) {
            toLowerCase(palavra);
            toLowerCase(palavra2);
            *avl = InsereAVL(*avl, palavra, palavra2, &aH);
            *abp = InsereArvore(*abp, palavra, palavra2);
            palavra = strtok(NULL, "\t\n");
        }
    }
}

// Função para processar o arquivo de entrada
void processInputFile(FILE* txt_entrada, FILE* txtsimplificado, pNodoA* avl, ptNodo* abp) {
    char linha[1000];
    char* palavra;

    while (fgets(linha, sizeof(linha), txt_entrada)) {
        palavra = strtok(linha, " \t\n");
        while (palavra != NULL) {
                ptNodo* ptAVL = consulta_AVL(avl, palavra);
            if (ptAVL != NULL) {
                fprintf(txtsimplificado, "%s ", ptAVL->mais_usada);
            } else {
                pNodoA* ptABP = consultaABP(abp, palavra);
                if (ptABP != NULL) {
                    fprintf(txtsimplificado, "%s ", ptABP->mais_usada);
                } else {
                    fprintf(txtsimplificado, "%s ", palavra);
                }
            }
            palavra = strtok(NULL, " \t\n");
        }
        fprintf(txtsimplificado, "\n"); // Para separar linhas
    }
}

// Função para gerar estatísticas
void generateStatistics(FILE* stats_ger, ptNodo* abp, pNodoA* avl) {
    fprintf(stats_ger, "========  ESTATÍSTICAS ABP ============\n\n");
    fprintf(stats_ger, "Número de nodos: %d\n", ContaNodos(abp));
    fprintf(stats_ger, "Altura: %d\n", alturaABP(abp));
    fprintf(stats_ger, "Rotações: %d\n", 0);
    fprintf(stats_ger, "Comparações: %d", imprimeCompABP());

    fprintf(stats_ger, "\n\n\n");

    fprintf(stats_ger, "========  ESTATÍSTICAS AVL ============\n\n");
    fprintf(stats_ger, "Número de nodos: %d\n", Nodos_AVL());
    fprintf(stats_ger, "Altura: %d\n", calcula_altura(avl));
    fprintf(stats_ger, "Rotações: %d\n", rotacoes_AVL());
    fprintf(stats_ger, "Comparações: %d\n", imprimeCompAVL());
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Portuguese");

    if (argc != 5) {
        printf("Número incorreto de parâmetros.\n");
        return 1;
    }

    FILE* dicionario = openFile(argv[1], "r");
    FILE* txt_entrada = openFile(argv[2], "r");
    FILE* txtsimplificado = openFile(argv[3], "w");
    FILE* stats_ger = openFile(argv[4], "w");

    pNodoA* avl = cria_AVL();
    ptNodo* abp = cria_arvore();

    processDictionary(dicionario, &avl, &abp);
    fclose(dicionario); // Fechar o arquivo do dicionário após o processamento

    processInputFile(txt_entrada, txtsimplificado, avl, abp);
    fclose(txt_entrada);
    fclose(txtsimplificado); // Fechar o arquivo de simplificação após o processamento

    generateStatistics(stats_ger, abp, avl);
    fclose(stats_ger); // Fechar o arquivo de estatísticas após a escrita

    return 0;
}
