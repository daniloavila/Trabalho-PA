#include <stdio.h>
#include <stdlib.h>
#include "Definitions.h"

void lerParametros(	animal *coelho,
					animal *leopardo,
					posicao *posicaoInicialCoelho,
					posicao *posicaoInicialLeopardo,
					char *arquivo) {

	FILE *arq = fopen(arquivo, "r");

	if(arq == NULL){
		printf("\n arquivo de entrada nao encontrado.");
		exit(0);
	}

	char direcao;

	direcao = getc(arq);

	switch (direcao) {
	case ('q'):
		coelho->aceleracaoCorrente.direcao = NORTE;
		break;
	case ('r'):
		coelho->aceleracaoCorrente.direcao = NORDESTE;
		break;
	case ('l'):
		coelho->aceleracaoCorrente.direcao = LESTE;
		break;
	case ('s'):
		coelho->aceleracaoCorrente.direcao = SULDESTE;
		break;
	case ('n'):
		coelho->aceleracaoCorrente.direcao = SUL;
		break;
	case ('t'):
		coelho->aceleracaoCorrente.direcao = SUDOESTE;
		break;
	case ('o'):
		coelho->aceleracaoCorrente.direcao = OESTE;
		break;
	case ('z'):
		coelho->aceleracaoCorrente.direcao = NOROESTE;
		break;
	}


	fscanf(arq, "%lf", &(coelho->aceleracaoCorrente.valor));
	fscanf(arq, "%d", &(coelho->massa));
	fscanf(arq, "%lf", &(coelho->velocidadeCorrente));

	fscanf(arq, "%lf", &(posicaoInicialCoelho->x));
	fscanf(arq, "%lf", &(posicaoInicialCoelho->y));

	direcao = getc(arq);

	switch (direcao) {
	case ('q'):
		leopardo->aceleracaoCorrente.direcao = NORTE;
		break;
	case ('r'):
		leopardo->aceleracaoCorrente.direcao = NORDESTE;
		break;
	case ('l'):
		leopardo->aceleracaoCorrente.direcao = LESTE;
		break;
	case ('s'):
		leopardo->aceleracaoCorrente.direcao = SULDESTE;
		break;
	case ('n'):
		leopardo->aceleracaoCorrente.direcao = SUL;
		break;
	case ('t'):
		leopardo->aceleracaoCorrente.direcao = SUDOESTE;
		break;
	case ('o'):
		leopardo->aceleracaoCorrente.direcao = OESTE;
		break;
	case ('z'):
		leopardo->aceleracaoCorrente.direcao = NOROESTE;
		break;
	}

	fscanf(arq, "%lf", &(leopardo->aceleracaoCorrente.valor));
	fscanf(arq, "%d", &(leopardo->massa));
	fscanf(arq, "%lf", &(leopardo->velocidadeCorrente));

	fscanf(arq, "%lf", &(posicaoInicialLeopardo->x));
	fscanf(arq, "%lf", &(posicaoInicialLeopardo->y));
}
