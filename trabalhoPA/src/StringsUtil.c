/*
 ============================================================================
 Nome        : Tales Mundim Andrade Porto
 Matricula   : 08/41200
 Descricao   : Trabalho feito para ler 2 arquivos um de "entrada" que servirá 
 	 	 	   de template e um que listará as palavas chaves e os seus 
 	 	 	   respectivos valores.
 	 	 	   
 	 	 	   Para compilar basta executar no console:
 	 	 	     make clean
 	 	 	     make
 	 	 	     
 	 	 	   Para executar basta executar no console:
 	 	 	     ./replaceInFile <arquivo_entrada> <arquivo_replace> <arquivo_saida>
 	 	 	   Exemplo:
 	 	 	     ./replaceInFile entrada.txt replace.txt saida.wrl
 ============================================================================
 */

#include "StringsUtil.h"

/* ***************************
 * UTIL
 * ***************************/

/**
 *Função que concatena um char no final de uma string.
 */
char *concat(char *base, char c) {
	char *stringAuxiliar = NULL;
	stringAuxiliar = malloc(strlen(base) + 2);
	strcpy(stringAuxiliar, base);
	if (strlen(base) > 0)
		free(base);
	strncat(stringAuxiliar, &c, 1);
	return stringAuxiliar;
}

/**
 * Função que concatena duas strings em uma string auxiliar e da free nas strings passadas como parâmetro.
 */
char *concatString(char *base, char *src) {
	char *stringAuxiliar;
	stringAuxiliar = malloc(strlen(base) + strlen(src) + 1);
	strcpy(stringAuxiliar, base);
	if (strlen(base) > 0)
		free(base);
	strcat(stringAuxiliar, src);
	if (strlen(src) > 0)
		free(src);
	return stringAuxiliar;
}

/**
 * Função que concatena duas strings em uma string auxiliar e da free nas strings passadas como parâmetro.
 */
char *concatStringN(char *base, char *src, int n) {
	char *stringAuxiliar;
	stringAuxiliar = malloc(strlen(base) + n + 1);
	strcpy(stringAuxiliar, base);
	if (strlen(base) > 0)
		free(base);
	strncat(stringAuxiliar, src, n);
	if (strlen(src) > 0)
		free(src);
	return stringAuxiliar;
}

/**
 * Função que concatena duas strings em uma string auxiliar e da free nas strings passadas como parâmetro.
 */
char *concatStringNNoFreeSrc(char *base, char *src, int n) {
	char *stringAuxiliar;
	stringAuxiliar = malloc(strlen(base) + n + 1);
	strcpy(stringAuxiliar, base);
	if (strlen(base) > 0)
		free(base);
	strncat(stringAuxiliar, src, n);
	return stringAuxiliar;
}

/**
 * Função que concatena duas strings em uma string auxiliar e da free em somente uma string.
 */
char *concatStringNoFreeSrc(char *base, char *src) {
	char *stringAuxiliar;
	stringAuxiliar = malloc(strlen(base) + strlen(src) + 1);
	strcpy(stringAuxiliar, base);
	if (strlen(base) > 0)
		free(base);
	strcat(stringAuxiliar, src);
	return stringAuxiliar;
}

/**
 * Função que da free em um ponteiro que aponta para uma string.
 */
void freeString(char *utf8String) {
	if (strlen(utf8String) > 0)
		free(utf8String);
}

/**
 * Inverte a string
 */
char *inverseString(char *src) {
	int i;
	int length = strlen(src);
	char *newString = "";
	for(i = 0; i <= length; i++) {
		newString = concat(newString, src[length - i]);
	}
	return newString;
}

/**
 * Remove os espacos em branco antes e depois do texto
 */
char *trim(char *src) {
	int i = 0, length, startedText;
	char *newString = "";

	if(src == NULL)
		return NULL;

	length = strlen(src);

	if(length == 0)
		return NULL;

	src = inverseString(src);

	startedText = 0;

	for(i = 0; i < length; i++) {
		if(!startedText) {
			if(!(src[i] == '\n' || src[i] == '\r' || src[i] == '\t')) {
				newString = concat(newString, src[i]);
				startedText = 1;
			}
		} else {
			newString = concat(newString, src[i]);
		}
	}

	src = inverseString(newString);
	newString = "";

	startedText = 0;

	for(i = 0; i < length; i++) {
		if(!startedText) {
			if(!(src[i] == '\n' || src[i] == '\r' || src[i] == '\t')) {
				newString = concat(newString, src[i]);
				startedText = 1;
			}
		} else {
			newString = concat(newString, src[i]);
		}
	}

	return newString;
}

/* ***************************
 * REPLACE
 * ***************************/

int getNumberOfOccurencesString(char *string, char *token) {
	int number = 0;
	char *start = string;

	while (start != NULL) {
		start = strstr(start, token);
		if (start != NULL) {
			number++;
			start = start + (strlen(token) * sizeof(char));
		}
	}
	return number;
}

char *replaceTokenByIndex(char *source, char *token, char *value, int index) {
	int i = -1, indexMax;
	char *start = source, *end, *result = "";

	indexMax = getNumberOfOccurencesString(source, token);

	end = start;

	while (start != NULL && i < index) {
		if (i == 0) {
			start = end;
		} else {
			start = end + 1;
		}

		start = strstr(start, token);
		end = start + (strlen(token) * sizeof(char));

		i++;
	}

	if (index == indexMax && end == NULL) {
		end = start + strlen(start);
	}

	if (start != NULL) {
		result = concatStringNNoFreeSrc(result, source, abs(start - source));
	}
	result = concatStringNoFreeSrc(result, value);
	if (end != NULL) {
		result = concatStringNoFreeSrc(result, end);
	}

	return result;
}

/* ***************************
 * SPLIT
 * ***************************/

int getNumberOfElementsForSplit(char *string, char token) {
	int number = 0;
	char *start = string;

	while (start != NULL) {
		start = strchr(start, token);
		number++;
		if (start != NULL)
			start++;
	}
	return number;
}

char *getElementsForSplitByIndex(char *string, char token, int index) {
	int number = 0, indexMax;
	char *start = string, *end, *element = "";

	indexMax = getNumberOfElementsForSplit(string, token);

	end = start;

	while (start != NULL && number < index) {
		if (number == 0) {
			start = end;
		} else {
			start = end + 1;
		}

		end = strchr(start, token);

		number++;
	}

	if (index == indexMax && end == NULL) {
		end = start + strlen(start);
	}

	if (start != NULL && end != NULL) {
		while (start != end) {
			element = concat(element, *start);
			start++;
		}
	}

	return element;
}
