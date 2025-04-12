/*****************************************************************//**
 * \file   dados.h
 * \brief  
 * 
 * \author Diogo Apolinário
 * \date   March 2025
 *********************************************************************/

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>


typedef struct ANTENA {
	int linha;
	int coluna;
	char nome;
	struct ANTENA* next;
}ANTENA;

typedef struct ANTENAFILE {
	int linha;
	int coluna;
	char nome;
}ANTENAFILE;
