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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef STRINGSUTIL_H_
#define STRINGSUTIL_H_

/* ***************************
 * UTIL
 * ***************************/
char *concat(char *base, char c);
char *concatString(char *base, char *src);
char *concatStringNoFreeSrc(char *base, char *src);
void freeString(char *utf8String);
char *concatStringNNoFreeSrc(char *base, char *src, int n);
char *trim(char *src);
char *inverseString(char *src);

/* ***************************
 * REPLACE
 * ***************************/
int getNumberOfOccurencesString(char *string, char *token);
char *replaceTokenByIndex(char *source, char *token, char *value, int index);

/* ***************************
 * SPLIT
 * ***************************/
int getNumberOfElementsForSplit(char *string, char token);
char *getElementsForSplitByIndex(char *string, char token, int index);

#endif
