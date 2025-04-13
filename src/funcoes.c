/*****************************************************************//**
* \file   funcoes.c
* \brief  
* 
* \author Diogo Apolinário
* \nº 6731
* \date   March 2025
*********************************************************************/

#include "dados.h"

#pragma region Criacao de Antenas

/**
* brief Cria uma antena
* 
* \param linha da antena
* \param coluna da antena
* \param nome (caracter) da antena
* \return antena criada
*/

ANTENA* CriaAntena(int linha, int coluna, char nome) {		//cria uma antena
	ANTENA* aux;		//apontador para a antena	

	aux = (ANTENA*)malloc(sizeof(ANTENA));		//aloca memória para a antena

	if (aux == NULL) return(NULL);		//se não conseguir alocar memória, devolve NULL

	

	aux->linha = linha;		//guarda a linha
	aux->coluna = coluna;		//guarda a coluna
	aux->nome = nome;		//guarda o caracter	
	aux->next = NULL;		//apontador para a próxima antena a NULL	

	return aux;		//devolve a antena	

}

#pragma endregion

#pragma region Inserir Antenas no local correto

/**
 *	brief Insere uma antena na lista no local correto
 *
 * \param h - Apontador da lista
 * \param n - Apontador da nova antena
 * \return h - Apontador da lista com a nova antena
 */

ANTENA* inserirAntena(ANTENA* h, ANTENA* n) {		//insere uma antena na lista


	if (n == NULL) return h;			// se não houver nova lista, devolve a lista original

	// Verificar se já existe uma antena com a mesma linha e coluna
	ANTENA* tmp = h;
	while (tmp != NULL) {
		if (tmp->linha == n->linha && tmp->coluna == n->coluna) {
			free(n); // evitar duplicados
			return h;
		}
		tmp = tmp->next;
	}
	
	if (h == NULL) {				// se a lista original estiver vazia								
		h = n;							// a lista nova passa a ser a primeira lista
		n->next = NULL;					// a lista nova não aponta para mais nenhuma lista, porque é única
		return h;						// devolve a primeira lista
	}

	if (n->linha < h->linha) {			// Se a linha da nova é menor que a linha da primeira lista, é a primeira da lista                         
		n->next = h;						// a nova lista aponta para a lista original
		h = n;								// nova passa a ser o head da lista, ou seja, a primeira lista
		return h;							// devolve a primeira lista
	}

	if (n->linha == h->linha) {				// Se a linha da nova for igual à linha da head, vai comparar a coluna
		if (n->coluna < h->coluna) {			// Se a nova coluna é menor que a coluna do primeiro da lista, é a primeira da lista
			n->next = h;						// nova passa a apontar para a lista original
			h = n;								// nova passa a ser o head da lista
			return h;							// devolve a lista
		}
	}


	ANTENA* aux2 = h;
	ANTENA* aux = aux2;
	while (n->linha > aux2->linha) {		// enquanto a linha da lista nova for superior à linha da lista original, avança na lista
		if (aux2->next == NULL) {			// se não houver mais listas, a lista nova passa a ser a última
			aux2->next = n;					// a lista original passa a apontar para a lista nova
			n->next = NULL;					// a lista nova passa a apontar para NULL
			return h;						// devolve a lista original
		}
		aux = aux2;							// guarda a posição anterior
		aux2 = aux2->next;					// avança na lista original
	}
	
	if (n->linha == aux2->linha) {			// se a linha da lista nova for igual à linha da lista original	
		while ((n->linha == aux2->linha) && (n->coluna > aux2->coluna)) {	// enquanto a coluna da lista nova for superior à coluna da lista original
			if (aux2->next == NULL) {		// se não houver mais listas, aux2 é a última lista
				aux2->next = n;				// a lista original passa a apontar para a lista nova
				n->next = NULL;				// a lista nova passa a apontar para NULL
				return h;					// devolve a lista original
			}
			aux = aux2;						// guarda a posição anterior
			aux2 = aux2->next;				// avança na lista original
		}
	}
	// caso não pare em nenhuma das condições anteriores, a nova antena é inserida no meio da lista
	n->next = aux2;							// a lista nova passa a apontar para a lista original
	aux->next = n;							// a lista anterior passa a apontar para a lista nova

	return h;								// devolve a lista original
}

#pragma endregion

#pragma region Mostrar os dados das Antenas
/**
 * brief Mostra a lista das antenas
 * 
 * \param h - Apontador da lista
 * \return Dados das antenas
 */

int mostrarLista(ANTENA* h) {		//mostra a lista

	ANTENA* aux = h;

	if (aux == NULL) {				// se a lista estiver vazia
		printf("A lista esta vazia !\n");
		return 0;					
	}
	while (aux) {					// se a lista != NULL
		printf("Antena %c - Linha %d - Coluna %d\n", aux->nome, aux->linha, aux->coluna);
		aux = aux->next;			// avança na lista
	}

	return 1;	

}

#pragma endregion

#pragma region Mostra os dados das Antenas a partir do Ficheiro

/**
 * brief Mostra a lista das antenas a partir do ficheiro
 * 
 * \param h - Apontador da lista
 * \return Dados das antenas
 */

int mostrarListaDoFicheiro(ANTENA* h) {		//mostra a lista dos ficheiros, apenas para corrigir as linhas e colunas

	ANTENA* aux = h;

	if (aux == NULL) {						// se a lista estiver vazia
		return 0;
	}
	while (aux) {							// se a lista != NULL
		printf("Antena %c - Linha %d - Coluna %d\n", aux->nome, aux->linha + 1, aux->coluna + 1);	
		aux = aux->next;					// avança na lista
	}

	return 1;

}

#pragma endregion

#pragma region Mostra a Matriz a partir das inserções no terminal

/**
 * brief Mostra a matriz no terminal
 * 
 * \param h - Apontador da lista
 * \return Matriz no terminal
 */

int mostrarMatriz(ANTENA* h) {			//mostra a matriz no terminal com os pontos e as antenas

	if (h == NULL) return 0;			// se a lista estiver vazia, devolve 0

	ANTENA* aux = h;					
	ANTENA* aux2 = h;
	int nLinhasMatriz = 0;
	int nColunasMatriz = aux->coluna;			

	//para calcular o tamanho da matriz, atualizando o número de linhas e colunas
	while (aux != NULL) {			// enquanto a lista não for NULL
		if (aux->coluna > nColunasMatriz) {		// se a coluna da lista for maior que a coluna da lista atual	
			nColunasMatriz = aux->coluna;			// a coluna da lista atual passa a ser a coluna da lista
		}
		aux = aux->next;								// avança na lista
	}
	aux = h;

	while (aux != NULL) {								// enquanto a lista não for NULL
		if (aux->linha > nLinhasMatriz) {				// se a linha da lista for maior que a linha da matriz
			nLinhasMatriz = aux->linha;					// a linha da matriz passa a ser a linha da lista
		}
		aux = aux->next;								// avança na lista	
	}
	

	//mostra uma linha na horizontal, antes de mostrar a matriz
	printf("\n");
	for (int x = 1; x < nColunasMatriz+1; x++) {
		printf("---");
	}
	printf("\n");

	//mostra a matriz
	for (int i = 1; i < nLinhasMatriz + 1; i++) {				// percorre as linhas da matriz, a começar na linha 1
		for (int j = 1; j < nColunasMatriz + 1; j++) {			// percorre as colunas da matriz, a começar na coluna 1
			if (aux2 != NULL && i == aux2->linha && j == aux2->coluna) {		// se a lista não for NULL e a linha e a coluna da lista forem iguais à linha e coluna da matriz	
				printf(" %c ", aux2->nome);									// mostra o caracter da lista
				aux2 = aux2->next;											// avança na lista
				continue;							
			}
			printf(" . ");										// se não houver antena, mostra um ponto
		}
		printf("\n");
	}

	
	return 1;
}

#pragma endregion

#pragma region Mostra a Matriz a partir do Ficheiro

/**
 * brief Mostra a matriz do ficheiro
 * 
 * \param h - Apontador da lista
 * \return matriz do ficheiro no terminal
 */

int mostrarMatrizDoFicheiro(ANTENA* h) {		//mostra a matriz dos ficheiros, apenas para corrigir as linhas e colunas

	if (h == NULL) return 0;

	ANTENA* aux = h;
	ANTENA* aux2 = h;
	int nLinhasMatriz = 0;
	int nColunasMatriz = aux->coluna;

	while (aux->next != NULL) {
		if (aux->next->coluna > nColunasMatriz) {
			nColunasMatriz = aux->next->coluna;
		}
		aux = aux->next;
	}
	aux = h;

	while (aux != NULL) {
		if (aux->linha > nLinhasMatriz) {
			nLinhasMatriz = aux->linha;
		}
		aux = aux->next;
	}


	printf("\n");
	for (int x = 0; x < nColunasMatriz + 1; x++) {
		printf("---");
	}
	printf("\n");

	for (int i = 0; i < nLinhasMatriz + 1; i++) {				// percorre as linhas da matriz, a começar na linha 0
		for (int j = 0; j < nColunasMatriz + 1; j++) {			// percorre as colunas da matriz, a começar na coluna 0
			if (aux2 != NULL && i == aux2->linha && j == aux2->coluna) {
				printf(" %c ", aux2->nome);
				aux2 = aux2->next;
				continue;
			}
			printf(" . ");
		}
		printf("\n");
	}


	return 1;
}

#pragma endregion

#pragma region Remover Antena

/**
 * brief Remover uma antena da lista
 *
 * \param h - Apontador da lista
 * \param linha - linha da antena
 * \param coluna - coluna da antena
 * \return h - Apontador da lista
 */

ANTENA* removerAntena(ANTENA* h, int linha, int coluna) {		//remove uma antena da lista
	ANTENA* aux = h;
	ANTENA* aux2 = h;

	if (h == NULL) {							// se não houver lista
		return h;
	}
	if (h->linha == linha && h->coluna == coluna) {		// se a linha e a coluna da lista forem iguais à linha e coluna da matriz
		aux = h->next;									// o aux começa na lista seguinte
		free(h);										// liberta a lista que removi, que era a primeira		
		return aux;										// devolve a lista
	}
	while ((aux) && aux->next != NULL) {		// enquanto houver lista e a lista seguinte não for NULL
		if (aux->next->linha == linha && aux->next->coluna == coluna) {		// se a linha e a coluna da lista seguinte forem iguais à linha e coluna da matriz
			aux2 = aux->next;					// o aux2 coloca-se na lista que quero remover
			aux->next = aux->next->next;		// o aux->next aponta para a lista seguinte, sem ser a que quero remover
			free(aux2);							// liberta a lista que removi
			return h;							// devolve a lista
		}
		aux = aux->next;						// avança na lista	
	}
	
	return h;

}

#pragma endregion

#pragma region Calcular Zonas Nefastas

/**
 * brief Calcula as zonas nefastas
 * 
 * \param h - Apontador da lista
 * \return apontador da lista com as zonas nefastas
 */

ANTENA* calcularZonasNefastas(ANTENA* h) {		//calcula as zonas nefastas
	ANTENA* aux = h;
	ANTENA* aux2 = aux;
	ANTENA* hNefaste = NULL;

	
	while (aux != NULL) {						// enquanto o auxiliar 1 não for NULL
		while (aux2 != NULL) {					// enquanto o auxiliar 2 não for NULL

			if (aux == aux2) {					// se o auxiliar 1 for igual ao auxiliar 2
				aux2 = aux2->next;				// o auxiliar 2 avança na lista	
				continue;
			}

			if (aux->nome == aux2->nome) {		// se o caracter do auxiliar 1 for igual ao caracter do auxiliar 2	
				ANTENA* n;
				n = (ANTENA*)malloc(sizeof(ANTENA));		// aloca memória para a nova lista com a zona nefasta

				if (n == NULL) {						// se não existir zona nefasta
					return 0;
				}

				n->next = NULL;												// a nova lista não aponta para mais nenhuma lista
				n->linha = aux->linha - aux2->linha + aux->linha;			// a linha da nova lista é a linha do auxiliar 1 - a linha do auxiliar 2 + a linha do auxiliar 1 (para calcular a linha de uma zona nefaste)
				n->coluna = aux->coluna - aux2->coluna + aux->coluna;		// a coluna da nova lista é a coluna do auxiliar 1 - a coluna do auxiliar 2 + a coluna do auxiliar 1 (para calcular a coluna de uma zona nefaste)
				n->nome = '#';												// e escreve o caracter # na zona nefasta

				ANTENA* tmp = hNefaste;							// apontador temporário para a zona nefasta
				int repetido = 0;

				while (tmp != NULL) {							// enquanto a zona nefasta não for NULL
					if (tmp->linha == n->linha && tmp->coluna == n->coluna) {		// se a linha e a coluna da zona nefasta forem iguais à linha e coluna da matriz (se já houver uma zona nefasta)
						repetido = 1;												// a zona nefasta é repetida e não é inserida	
						break;
					}
					tmp = tmp->next;												// avança na zona nefasta
				}
				if (repetido == 0) {												// se a zona nefasta não for repetida	
					hNefaste = inserirAntena(hNefaste, n);						// insere a zona nefasta na lista
				}
				if (repetido == 1) {												// se a zona nefasta for repetida
					free(n);														// liberta a zona nefasta, para ter apenas uma lista com a mesma localização
				}
				
			}
			aux2 = aux2->next;													// avança na lista
		}
		aux2 = h;																// o auxiliar 2 volta ao início da lista
		aux = aux->next;														// avança na lista
	}
	return hNefaste;															// devolve a lista com as zonas nefastas

}

#pragma endregion

#pragma region Mostrar a Matriz com as Zonas Nefastas

/**
 * brief Mostra a matriz com as zonas nefastas
 *
 * \param h - Apontador da lista
 * \param hNefastas - Apontador da lista com as zonas nefastas
 * \return Matriz com as zonas nefastas
 */

int mostrarMatrizComNefastas(ANTENA* h, ANTENA* hNefastas) {		//mostra a matriz com as zonas nefastas

	if (h == NULL) {		// se a lista estiver vazia não mostra nada
		return 0;
	}

	ANTENA* aux = h;
	ANTENA* aux2 = h;
	ANTENA* nefasta = hNefastas;
	ANTENA* nefasta2 = hNefastas;
	int nLinhasMatriz = 0, nColunasMatriz = 0;
	int nColunasNefastas = 0, nLinhasNefastas = 0;

	while (aux != NULL) {								// enquanto a lista não for NULL
		if (aux->coluna > nColunasMatriz) {				// se a coluna da lista for maior que a coluna da matriz, atualiza a coluna da matriz
			nColunasMatriz = aux->coluna;				// a coluna da matriz passa a ser a coluna da lista
		}
		if (aux->linha > nLinhasMatriz) {				// se a linha da lista for maior que a linha da matriz, atualiza a linha da matriz
			nLinhasMatriz = aux->linha;					// a linha da matriz passa a ser a linha da lista
		}
		aux = aux->next;								// avança na lista	
	}

	while (nefasta != NULL) {							// enquanto a lista das zonas nefastas não for NULL	
		if (nefasta->coluna > nColunasMatriz) {			// se a coluna da zona nefasta for maior que a coluna da matriz, atualiza a coluna da matriz
			nColunasMatriz = nefasta->coluna;			// a coluna da matriz passa a ser a coluna da zona nefasta
		}
		if (nefasta->coluna < nColunasNefastas) {		// se a coluna da zona nefasta for menor que a coluna das zonas nefastas, atualiza a coluna das zonas nefastas
			nColunasNefastas = nefasta->coluna;			// a coluna das zonas nefastas passa a ser a coluna da zona nefasta
		}
		if (nefasta->linha > nLinhasMatriz) {			// se a linha da zona nefasta for maior que a linha da matriz, atualiza a linha da matriz
			nLinhasMatriz = nefasta->linha;				// a linha da matriz passa a ser a linha da zona nefasta
		}
		if (nefasta->linha < nLinhasNefastas) {			// se a linha da zona nefasta for menor que a linha das zonas nefastas, atualiza a linha das zonas nefastas
			nLinhasNefastas = nefasta->linha;			// a linha das zonas nefastas passa a ser a linha da zona nefasta
		}
			nefasta = nefasta->next;					// avança na lista das zonas nefastas
	}

	//mostra uma linha na horizontal, antes de mostrar a matriz
	printf("\n");
	for (int x = nColunasNefastas; x <= nColunasMatriz; x++) {			
		printf("---");
	}
	printf("\n");
	

	for (int i = nLinhasNefastas; i <= nLinhasMatriz; i++) {				// percorre as linhas da matriz, a começar na linha das zonas nefastas
		for (int j = nColunasNefastas; j <= nColunasMatriz; j++) {			// percorre as colunas da matriz, a começar na coluna das zonas nefastas	
			if (aux2 != NULL && i == aux2->linha && j == aux2->coluna) {		// se a lista não for NULL e a linha e a coluna da lista forem iguais à linha e coluna da matriz
				printf(" %c ", aux2->nome);									// mostra o caracter da lista
				aux2 = aux2->next;											// avança na lista
				if (nefasta2 != NULL && i == nefasta2->linha && j == nefasta2->coluna) {		// se a lista das zonas nefastas não for NULL e a linha e a coluna da zona nefasta forem iguais à linha e coluna da matriz
					nefasta2 = nefasta2->next;												// avança na lista das zonas nefastas
				}
				continue;
			}
			if ((nefasta2 != NULL) && (i == nefasta2->linha) && (j == nefasta2->coluna)) {		// se a lista das zonas nefastas não for NULL e a linha e a coluna da zona nefasta forem iguais à linha e coluna da matriz
				printf(" %c ", nefasta2->nome);												// mostra o caracter da zona nefasta
				nefasta2 = nefasta2->next;													// avança na lista das zonas nefastas
				continue;
			}
			printf(" . ");										// se não houver antena ou zona nefasta, mostra um ponto
		}
		printf("\n");
	}

	return 1;
}

#pragma endregion

#pragma region Ler Ficheiro Txt

/**
 * brief Lê o ficheiro txt
 * 
 * \param Nome do Ficheiro
 * \param h - Apontador da lista
 * \return Ficheiro lido
 */

int LerFicheiro(const char* NomeFicheiro, ANTENA** h) {		//lê o ficheiro txt	

	ANTENA* aux = NULL;
	FILE* fp;

	if (fopen_s(&fp, NomeFicheiro, "r") != 0) {			// se não conseguir abrir o ficheiro
			printf("Erro ao abrir ficheiro.\n");		
			return 0;
	}

	char linhaFicheiro[256];
	int numeroLinha = 0;

	while (fgets(linhaFicheiro, sizeof(linhaFicheiro), fp)) {		// enquanto houver linhas no ficheiro	
		int numeroColuna = 0;										// inicializa o número da coluna
		while ((linhaFicheiro[numeroColuna] != '\n') && linhaFicheiro[numeroColuna] != '\0') {		// enquanto a linha não chegar ao fim
			if ((linhaFicheiro[numeroColuna] != '.') && (linhaFicheiro[numeroColuna] != '#')) {		// se a linha for diferente de . e #
				aux = CriaAntena(numeroLinha, numeroColuna, linhaFicheiro[numeroColuna]);			// cria uma antena
				*h = inserirAntena(*h, aux);														// insere a antena na lista	
			}

			numeroColuna++;		// avança na coluna
		}
		numeroColuna = 0;
		numeroLinha++;			// avança na linha
	}

fclose(fp);		// fecha o ficheiro
return 1;
}

#pragma endregion

#pragma region Gravar no Ficheiro Txt

/**
 * brief Grava no ficheiro txt
 *
 * \param nome do Ficheiro
 * \param h - Apontador da lista
 * \return Ficheiro gravado no Txt
 */

bool GravarNoFicheiroTxt(const char* nomeFicheiro, ANTENA* h) {		//grava no ficheiro txt

	if (h == NULL) {		// se a lista estiver vazia
		return false;
	}

	ANTENA* aux = h;
	ANTENA* aux2 = h;
	int nLinhasMatriz = aux->linha, nColunasMatriz = aux->coluna;

	FILE* fp;													// apontador para o ficheiro

	if (fopen_s(&fp, nomeFicheiro, "w") != 0) {				// se não conseguir abrir o ficheiro
		printf("Erro ao abrir ficheiro.\n");
		return false;
	}

	while (aux != NULL) {										// enquanto a lista não for NULL	
		if (aux->coluna > nColunasMatriz)						// se a coluna da lista for maior que a coluna da matriz
			nColunasMatriz = aux->coluna;						// a coluna da matriz passa a ser a coluna da lista
		if (aux->linha > nLinhasMatriz)							// se a linha da lista for maior que a linha da matriz
			nLinhasMatriz = aux->linha;							// a linha da matriz passa a ser a linha da lista
		aux = aux->next;										// avança na lista
	}

	for (int i = 1; i <= nLinhasMatriz; i++) {		// percorre as linhas da matriz, a começar na linha das zonas nefastas
		for (int j = 1; j <= nColunasMatriz; j++) {	// percorre as colunas da matriz, a começar na coluna das zonas nefastas
			if ((aux2 != NULL) && (i == aux2->linha) && (j == aux2->coluna)) {		// se a lista não for nula e a linha e a coluna da lista forem iguais à linha e coluna da matriz
				fprintf(fp, "%c", aux2->nome);		// escreve o caracter da lista no ficheiro
				aux2 = aux2->next;					// avança na lista
				continue;
			}
			fprintf(fp, "%c", '.');		// se não houver antena ou zona nefasta, escreve um ponto no ficheiro
		}
		fprintf(fp, "%c", '\n');		// escreve uma nova linha no ficheiro
	}

	return true;
}
#pragma endregion

#pragma region Gravar no Ficheiro Binario

/**
	 * brief Grava no ficheiro binário
	 *
	 * \param nome do Ficheiro
	 * \param h - Apontador da lista
	 * \return Ficheiro gravado no Binário
	 */

bool GravarAntenaBinario(char* nomeFicheiro, ANTENA* h) {
	FILE* fp;				//apontador para o ficheiro

	if (h == NULL) {		//se a lista estiver vazia
		return false;		//devolve falso
	}
	if (fopen_s(&fp, nomeFicheiro, "wb") != 0) {		//se não conseguir abrir o ficheiro	
		printf("Erro ao abrir ficheiro");
		return false;		//devolve falso		
	}

	//grava todas as antenas da lista no ficheiro
	ANTENA* aux = h;		//apontador auxiliar para percorrer a lista	
	ANTENAFILE auxAntena;		//struct auxiliar para gravar em ficheiro

	//inicializa a struct auxiliar
	memset(&auxAntena, 0, sizeof(ANTENAFILE));		

	//coloca no ficheiro a informação que tem em memória
	while (aux != NULL) {			//enquanto houver antenas na lista
		auxAntena.linha = aux->linha;
		auxAntena.coluna = aux->coluna;
		auxAntena.nome = aux->nome;

		fwrite(&auxAntena, sizeof(ANTENAFILE), 1, fp);		//escreve no ficheiro

		aux = aux->next;		//avança na lista
	}

	fclose(fp);		//fecha o ficheiro

	return true;

}

#pragma endregion

#pragma region Ler do Ficheiro Binario

/**
 * brief Lê do ficheiro binário
 * 
 * \param nome do Ficheiro
 * \return Ficheiro lido do Binário
 */

ANTENA* LerAntenaBinario(char* nomeFicheiro) {			//lê do ficheiro binário
	FILE* fp;				//apontador para o ficheiro
	ANTENAFILE auxAntena;	//struct auxiliar para ler do ficheiro
	ANTENA* h = NULL;		//lista de antenas
	ANTENA* n = NULL;		//antena a ser inserida na lista
	if (fopen_s(&fp, nomeFicheiro, "rb") != 0) {		//se não conseguir abrir o ficheiro
		printf("\nErro ao abrir ficheiro");
		return NULL;		//devolve NULL
	}
	//enquanto conseguir ler do ficheiro
	while (fread(&auxAntena, sizeof(ANTENAFILE), 1, fp) == 1) {
		n = CriaAntena(auxAntena.linha, auxAntena.coluna, auxAntena.nome);	//cria uma antena
		h = inserirAntena(h, n);		//insere a antena na lista
	}
	fclose(fp);		//fecha o ficheiro	
	return h;		//devolve a lista
}

#pragma endregion