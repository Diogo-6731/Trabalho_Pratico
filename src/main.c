/*****************************************************************//**
 * \file   main.c
 * \brief  
 * 
 * \author Diogo Apolinário
 * \date   March 2025
 *********************************************************************/

#include "dados.h"
#include "funcoes.h"
#include <locale.h>


 int main() {
	 setlocale(LC_ALL, "Portuguese");

		ANTENA* criaAntena = NULL;
		ANTENA* insereAntena = NULL;
		ANTENA* h = NULL;
		ANTENA* n = NULL;
		ANTENA* hNefastas = NULL;
		ANTENA* novaAntena = NULL;
		ANTENA* listaNefastas = NULL;
		bool res;

		int opcao, linha, coluna;
		char nome;
		

		printf("\n -----------------------------------\n\n");
		printf("       Trabalho Prático - Fase 1\n");
		printf("\n -----------------------------------\n\n");
		printf("              MENU\n\n");
		printf("1 - Inserir uma Antena\n");
		printf("2 - Remove uma Antena\n");
		printf("3 - Mostrar Antenas\n");
		printf("4 - Calcular Zonas Nefastas\n");
		printf("5 - Mostra as Antenas e as Zonas Nefastas\n");
		printf("6 - Lê do Txt e Mostra a Matriz\n");
		printf("7 - Grava em Txt\n");
		printf("8 - Lê do Binário e Mostra a Matriz\n");
		printf("9 - Grava em Binário\n");
		printf("0 - Sair\n\n");

		do {
			printf("\n\nEscolha uma opção: ");
			scanf_s("%d", &opcao);
			switch (opcao) {
				case 1:
					printf("\n\nInsere a linha: ");
					scanf_s("%d", &linha);
					printf("\nInsere a coluna: ");
					scanf_s("%d", &coluna);
					printf("\nInsere o caracter da antena (frequência): ");
					scanf_s(" %c", &nome, 1);

					novaAntena = CriaAntena(linha, coluna, nome);
					if (novaAntena == NULL) {
						printf("Erro ao criar antena!\n");
						break;
					}
					h = inserirAntena(h, novaAntena);

					/*h = inserirAntena(h, CriaAntena(1, 1, 'x'));
					h = inserirAntena(h, CriaAntena(0, 0, 'x'));
					h = inserirAntena(h, CriaAntena(3, 4, 'a'));
					h = inserirAntena(h, CriaAntena(5, 3, 'a'));
					h = inserirAntena(h, CriaAntena(2, 3, 'a'));
					h = inserirAntena(h, CriaAntena(5, 5, 'x'));*/

					break;
				case 2:
					if (h != NULL) {
						printf("\nQual linha queres remover?\n");
						scanf_s("%d", &linha);
						printf("\nQual coluna queres remover?\n");
						scanf_s("%d", &coluna);
					}

					printf("\n");

					if (h == NULL) {
						printf("\nErro: Não há antenas para remover!\n");
						break;
					}
					else {
						h = removerAntena(h, linha, coluna);
						printf("\n\nAntena removida!\n\n");
					}
					

					break;
				case 3:
					printf("\n");

					if (h == NULL) {
						printf("\nErro: Não há antenas para mostrar!\n");
						break;
					}
					else {
						printf("\n\nAntenas criadas!\n\n");
					}

					if (h != NULL) {
						mostrarLista(h);
					}

					printf("\n");

					mostrarMatriz(h);

					
					break;
				case 4:
					if (h == NULL) {
						printf("\nErro: Não há antenas para calcular as zonas nefastas!\n");
						break;
					}
					else{
					printf("\n\nZonas Nefastas Calculadas!\n\n");
					}
					
					hNefastas = calcularZonasNefastas(h);
					mostrarLista(hNefastas);

					break;
				case 5:
					
					if (hNefastas == NULL) {
						printf("\nErro: Primeiro tens de calcular as zonas nefastas (Opção 4)!\n");
						printf("Ou então não há antenas para calcular as zonas nefastas!\n");
						break;
					}

					printf("\n");

					mostrarLista(h);
					mostrarLista(hNefastas);

					printf("\n");

					mostrarMatrizComNefastas(h, hNefastas);
					
					break;

				case 6:
					
					n = LerFicheiro("Lista_de_Antenas.txt", &h);

					if (h == NULL) {
						printf("\n\nErro ao ler ficheiro!\n");
					}
					else {
						printf("\n\nFicheiro lido com sucesso!\n\n");
					}

					mostrarListaDoFicheiro(h);
					mostrarMatrizDoFicheiro(h);

					GravarAntenaBinario("Lista_de_Antenas.bin", h);

					break;

				case 7:
					
					res = GravarNoFicheiroTxt("Lista_de_Antenas.txt", h);

					if (res) {
						printf("\n\nFicheiro gravado com sucesso!\n");
					}
					else {
						printf("\n\nErro ao gravar ficheiro!\n");
					}

					break;

				case 8:

					h = LerAntenaBinario("Lista_de_Antenas.bin");
					if (h == NULL) {
						printf("\n\nErro ao ler ficheiro!\n");
					}
					else {
						printf("\n\nFicheiro lido com sucesso!\n\n");
					}

					mostrarListaDoFicheiro(h);
					mostrarMatrizDoFicheiro(h);

					break;

				case 9:

					res = GravarAntenaBinario("Lista_de_Antenas_e_Nefastes.bin", h);

					if (res) {
						printf("\n\nFicheiro gravado com sucesso!\n");
					}
					else {
						printf("\n\nErro ao gravar ficheiro!\n");
					}
				
					break;
				case 0:
					printf("\nAté à próxima...\n");
					break;
			default:
				printf("Opção inválida\n");
			}
		} while (opcao != 0);
 }