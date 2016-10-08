/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   nRainhas.h
 * Author: vinicius
 *
 * Created on October 4, 2016, 5:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NRAINHAS_H
#define NRAINHAS_H

#ifdef __cplusplus
extern "C" {
#endif

#define FALSE   0
#define TRUE    1

    typedef struct {
        int *marcaColuna;
        int *marcaDiagonal;
        int *marcaDiagonalPrincipal;
        int *marcaDiagonalSecundaria;
        int *marcaRainhas;

        int tamanho;
        int nSolucoes;
        int tentativasUsadas;
        int tentativasDescartadas;
    } nRainhas;

    void imprimeTabuleiro(nRainhas tabuleiro);
    void resolveNRainhas(nRainhas *tabuleiro);

#ifdef __cplusplus
}
#endif

#endif /* NRAINHAS_H */

