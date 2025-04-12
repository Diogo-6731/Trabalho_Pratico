/*****************************************************************//**
 * \file   funcoes.h
 * \brief  
 * 
 * \author Diogo Apolinário
 * \date   March 2025
 *********************************************************************/

#pragma once

#include "dados.h"
#include <stdio.h>


ANTENA* CriaAntena(int linha, int coluna, char nome);
ANTENA* inserirAntena(ANTENA* h, ANTENA* n);
int mostrarMatriz(ANTENA* h);
int mostrarMatrizDoFicheiro(ANTENA* h);
int mostrarLista(ANTENA* h);
int mostrarListaDoFicheiro(ANTENA* h);
ANTENA* removerAntena(ANTENA* h, int linha, int coluna);
ANTENA* calcularZonasNefastas(ANTENA* h);
int LerFicheiro(const char* NomeFicheiro, ANTENA** h);
bool GravarAntenaBinario(char* nomeFicheiro, ANTENA* h);
ANTENA* LerAntenaBinario(char* nomeFicheiro);
int GravarNoFicheiroTxt(const char* nomeFicheiro, ANTENA* h, ANTENA* hNefastas);
