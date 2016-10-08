#include "nRainhas.h"

void resolveNRainhas(nRainhas *tabuleiro) {

    int linhaAtual = 0, colunaAtual = 0, i = 0;
    int fim, posicaoValida;

    tabuleiro->marcaColuna = (int*) malloc(sizeof (int)*tabuleiro->tamanho);
    tabuleiro->marcaDiagonal = (int*) malloc(sizeof (int)*(2 * tabuleiro->tamanho - 1));
    tabuleiro->marcaDiagonalSecundaria = (int*) malloc(sizeof (int)*(2 * tabuleiro->tamanho - 1));
    tabuleiro->marcaDiagonalPrincipal = tabuleiro->marcaDiagonal + tabuleiro->tamanho - 1;
    tabuleiro->marcaRainhas = malloc(sizeof (int)*tabuleiro->tamanho);

    for (i = 0; i < tabuleiro->tamanho; i++)
        tabuleiro->marcaColuna[i] = TRUE;

    for (i = 0; i < (2 * tabuleiro->tamanho - 1); i++) {
        tabuleiro->marcaDiagonal[i] = TRUE;
        tabuleiro->marcaDiagonalSecundaria[i] = TRUE;
    }

    fim = FALSE;
    tabuleiro->nSolucoes = 0;
    tabuleiro->tentativasUsadas = 0;
    tabuleiro->tentativasDescartadas = 0;

    while (!fim) {
        posicaoValida = FALSE;
        while (colunaAtual < tabuleiro->tamanho && !posicaoValida) {
            if (tabuleiro->marcaColuna[colunaAtual] && tabuleiro->marcaDiagonalPrincipal[linhaAtual - colunaAtual] //verifica se a coluna ja foi marcada, verifica tambem se as diagonais estão mardas
                    && tabuleiro->marcaDiagonalSecundaria[linhaAtual + colunaAtual]) {

                tabuleiro->marcaColuna[colunaAtual] = FALSE;
                tabuleiro->marcaDiagonalPrincipal[linhaAtual - colunaAtual] = FALSE;
                tabuleiro->marcaDiagonalSecundaria[linhaAtual + colunaAtual] = FALSE;
                tabuleiro->marcaRainhas[linhaAtual] = colunaAtual;
                tabuleiro->tentativasUsadas++;
                posicaoValida = TRUE;
            } else {
                colunaAtual++; // posicao corre risco de ataque
            }
        }
        if (posicaoValida) {
            if (linhaAtual != tabuleiro->tamanho - 1) { //se a posicao e valida e a linha ainda é menor que o tamanho do tabuleiro, tentaremos então posicionar outra peça
                linhaAtual++;
                colunaAtual = 0;
            } else { //se não é contabilizada mais uma solução, imprimimos a solução encontrada no arquivo , desmarcamos as posições e recomeçamos
                tabuleiro->nSolucoes++;
                imprimeTabuleiro(*tabuleiro);

                tabuleiro->marcaColuna[colunaAtual] = TRUE;
                tabuleiro->marcaDiagonalPrincipal[linhaAtual - colunaAtual] = TRUE;
                tabuleiro->marcaDiagonalSecundaria[linhaAtual + colunaAtual] = TRUE;
                
                tabuleiro->tentativasUsadas = 0;
                tabuleiro->tentativasDescartadas = 0;
                colunaAtual = tabuleiro->tamanho;
            }
        } else {
            if (linhaAtual == 0) //todas as possibilidades testadas
                fim = TRUE;
            else { //Tentamos outra posição para a rainha na linha anterior
                
                linhaAtual--;
                tabuleiro->tentativasDescartadas++;
                
                colunaAtual = tabuleiro->marcaRainhas[linhaAtual];
                tabuleiro->marcaColuna[colunaAtual] = TRUE;
                tabuleiro->marcaDiagonalPrincipal[linhaAtual - colunaAtual] = TRUE;
                tabuleiro->marcaDiagonalSecundaria[linhaAtual + colunaAtual] = TRUE;                
                
                colunaAtual++;
            }
        }
    }
    if (tabuleiro->nSolucoes == 0) {
        printf("Nao existe solucao para %d rainhas !\n", tabuleiro->tamanho);
    }
}

void imprimeTabuleiro(nRainhas tabuleiro) {
    
    FILE *file;
 
    static int solucao = 1;
    int i, j;
    char inicioArquivo[20] = "solucao-";
    char fimArquivo[20] = "-Rainhas.txt";
    char tamtab[100];
    char *nomeFinal;
    
    snprintf(tamtab,20,"%d",tabuleiro.tamanho);
    strcat(inicioArquivo,tamtab);
    nomeFinal = strcat(inicioArquivo,fimArquivo);
    file = fopen(nomeFinal, "a+");

    if (solucao == 1)
        fprintf(file, "%s %d %s\n\n", "Possiveis solucoes para ", tabuleiro.tamanho, "rainhas");

    fprintf(file, "%s %d %s", "Solucao", solucao,":");
    fprintf(file, "%s", "\n");
    for (j = 0; j < tabuleiro.tamanho; j++) {
        for (i = 0; i < tabuleiro.tamanho; i++) {
            if ((tabuleiro.marcaRainhas[j] == i))
                fprintf(file, "%s", "|x");
            else
                fprintf(file, "%s", "|_");
        }
        fprintf(file, "%s", "|");
        fprintf(file, "%s", "\n");
    }
    fprintf(file,"%s %d\n","Tentativa feitas com sucesso: ",tabuleiro.tentativasUsadas);
    fprintf(file,"%s %d\n","Tentativas descartadas: ",tabuleiro.tentativasDescartadas);
    fprintf(file,"%s %d\n","Total de tentativas: ",tabuleiro.tentativasUsadas+tabuleiro.tentativasDescartadas);
    fprintf(file, "%s", "\n");
    solucao++;

    fclose(file);
}



