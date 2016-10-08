/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: vinicius
 *
 * Created on October 4, 2016, 4:22 PM
 */

#include "nRainhas.h"


/*
 * 
 */
int main(int argc, char** argv) {
    
    nRainhas tabuleiro;
    printf("digite o tamanho do tabuleiro: ");
    scanf("%d",&tabuleiro.tamanho);
    resolveNRainhas(&tabuleiro);
    printf("Um arquivo chamado 'solucoes-%d-Rainhas.txt' contendo todas as possiveis solucoes foi criado na pasta do programa !\n",tabuleiro.tamanho);
    return (EXIT_SUCCESS);
}

