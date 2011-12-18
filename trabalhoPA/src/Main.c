/*
* Universidade de Brasília
* Disciplina: Programação Avançada
*
* Alunos:
* 			Danilo Ávila  		xx/xxxxx
* 			Ricardo Andrade  	08/39710
* 			Tales Porto 		08/41200
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Definitions.h"
#include "StringsUtil.h"
#include "Arquivo.h"

DIRECAO getDirecao(posicao posicaoLeopardo, posicao posicaoCoelho);
double calcularDistanciaEntreAnimais(posicao coelho, posicao leopardo);
void getPosicaoCoelho(animal *coelho, animal *leopardo, int i);
void getPosicaoLeopardo(animal *leopardo, animal *coelho);
char *loadFile(char *fileName);

posicao posicaoInicialLeopardo, posicaoInicialCoelho;

int numeroPassos = 200;

int main(void) {

	animal coelho, leopardo;

	printf("Numero de passos: ");
	scanf("%d", &numeroPassos);

	char *entrada= loadFile("entrada.txt");
	lerParametros(&coelho, &leopardo, &posicaoInicialCoelho, &posicaoInicialLeopardo, "entrada.txt");

	coelho.posicaoCorrente = posicaoInicialCoelho;
	leopardo.posicaoCorrente = posicaoInicialLeopardo;

	// proporcao entre os aninais
	int proporcao = leopardo.massa / coelho.massa;

	coelho.posicoes = malloc(sizeof(posicao) * numeroPassos);
	leopardo.posicoes = malloc(sizeof(posicao) * numeroPassos);

	for (int i = 0; i < numeroPassos; i++) {
		coelho.posicoes[i] = coelho.posicaoCorrente;
		leopardo.posicoes[i] = leopardo.posicaoCorrente;

		// calcula proxima posicao
		getPosicaoLeopardo(&leopardo, &coelho);
		getPosicaoCoelho(&coelho, &leopardo, i);

		if (coelho.velocidadeCorrente < VELOCIDADE_MAXIMA_COELHO) {
			coelho.velocidadeCorrente += coelho.aceleracaoCorrente.valor;
		}

		if (leopardo.velocidadeCorrente < VELOCIDADE_MAXIMA_LEOPARDO) {
			leopardo.velocidadeCorrente += leopardo.aceleracaoCorrente.valor;
		}

	}

	// carregar arquivo
	tagReplace *replaces = malloc(sizeof(tagReplace) * 4);

	replaces[0].oldContent = "";
	replaces[1].oldContent = "";
	replaces[2].oldContent = "";
	replaces[3].oldContent = "";

	replaces[0].newContent = "";
	replaces[1].newContent = "";
	replaces[2].newContent = "";
	replaces[3].newContent = "";

	replaces[0].oldContent = concatStringNoFreeSrc(replaces[0].oldContent, LEOPARDO_KEY);
	replaces[1].oldContent = concatStringNoFreeSrc(replaces[1].oldContent, LEOPARDO_KEY_VALUE);
	replaces[2].oldContent = concatStringNoFreeSrc(replaces[2].oldContent, COELHO_KEY);
	replaces[3].oldContent = concatStringNoFreeSrc(replaces[3].oldContent, COELHO_KEY_VALUE);

	for (int i = 0; i < numeroPassos; i++) {
		if (i != 0) {
			replaces[0].newContent = concatStringNoFreeSrc(replaces[0].newContent, ", ");
			replaces[1].newContent = concatStringNoFreeSrc(replaces[1].newContent, ", ");
			replaces[2].newContent = concatStringNoFreeSrc(replaces[2].newContent, ", ");
			replaces[3].newContent = concatStringNoFreeSrc(replaces[3].newContent, ", ");
		}

		char s[255] = "";
		sprintf(s, "%f", ((double) 1 / (double) numeroPassos * i));
		replaces[0].newContent = concatStringNoFreeSrc(replaces[0].newContent, s);
		replaces[2].newContent = concatStringNoFreeSrc(replaces[2].newContent, s);

		sprintf(s, "%lf  %lf %lf", leopardo.posicoes[i].x + 2, 0.0, leopardo.posicoes[i].y + 2);
		replaces[1].newContent = concatStringNoFreeSrc(replaces[1].newContent, s);

		sprintf(s, "%lf  %lf %lf", coelho.posicoes[i].x + 2, 0.0, coelho.posicoes[i].y + 2);
		replaces[3].newContent = concatStringNoFreeSrc(replaces[3].newContent, s);
	}

	char *saida = loadFile("template.wrl");

	for (int i = 0; i < 4; i++) {
		tagReplace replace = replaces[i];
		int total = getNumberOfOccurencesString(saida, replace.oldContent);
		saida = replaceTokenByIndex(saida, replace.oldContent, replace.newContent, 0);
	}

	FILE *fileSaida = fopen("saida.wrl", "w+");
	fprintf(fileSaida, "%s", saida);
	fflush(fileSaida);
	fclose(fileSaida);

	printf("Arquivo \"saida.wrl\" gerado com sucesso.\n");

	return EXIT_SUCCESS;
}

DIRECAO getDirecao(posicao posicaoLeopardo, posicao posicaoCoelho) {
	if (posicaoCoelho.y > posicaoLeopardo.y) {
		if (posicaoCoelho.x > posicaoLeopardo.x)
			return NORDESTE;
		else if (posicaoCoelho.x == posicaoLeopardo.x)
			return NORTE;
		else
			return NOROESTE;
	} else if (posicaoCoelho.y == posicaoLeopardo.y) {
		if (posicaoCoelho.x > posicaoLeopardo.x)
			return LESTE;
		else if (posicaoCoelho.x == posicaoLeopardo.x) {
			printf("COMIIII PORRAAAA\n\n\n");
			return COMI;
		} else
			return OESTE;
	} else {
		if (posicaoCoelho.x > posicaoLeopardo.x)
			return SULDESTE;
		else if (posicaoCoelho.x == posicaoLeopardo.x)
			return SUL;
		else
			return SUDOESTE;
	}

	return NORTE;
}

void getPosicaoLeopardo(animal *leopardo, animal *coelho) {
	DIRECAO direcao = getDirecao(leopardo->posicaoCorrente, coelho->posicaoCorrente);

	// proporcao entre os aninais
	int proporcao = leopardo->massa / coelho->massa;

	switch (direcao) {
	case NORTE:
		leopardo->posicaoCorrente.y += leopardo->velocidadeCorrente;
		break;
	case NORDESTE:
		leopardo->posicaoCorrente.y += proporcao;
		leopardo->posicaoCorrente.x += 1;
		leopardo->velocidadeCorrente = 0;
		break;
	case LESTE:
		leopardo->posicaoCorrente.x += leopardo->velocidadeCorrente;
		break;
	case SULDESTE:
		leopardo->posicaoCorrente.y -= proporcao;
		leopardo->posicaoCorrente.x += 1;
		leopardo->velocidadeCorrente = 0;
		break;
	case SUL:
		leopardo->posicaoCorrente.y -= leopardo->velocidadeCorrente;
		break;
	case SUDOESTE:
		leopardo->posicaoCorrente.y -= proporcao;
		leopardo->posicaoCorrente.x -= 1;
		leopardo->velocidadeCorrente = 0;
		break;
	case OESTE:
		leopardo->posicaoCorrente.x -= leopardo->velocidadeCorrente;
		break;
	case NOROESTE:
		leopardo->posicaoCorrente.y += proporcao ;
		leopardo->posicaoCorrente.x -= 1;
		leopardo->velocidadeCorrente = 0;
		break;
	}


}

void getPosicaoCoelho(animal *coelho, animal *leopardo, int i) {
	posicao posicaoAntigaLeopardo;

	if (i > 0)
		posicaoAntigaLeopardo = leopardo->posicoes[i - 1];
	else
		posicaoAntigaLeopardo = leopardo->posicaoCorrente;

	if (calcularDistanciaEntreAnimais(coelho->posicaoCorrente, posicaoAntigaLeopardo) <= 2) {
		coelho->velocidadeCorrente = coelho->velocidadeCorrente/2;
		int randomico = rand() % 3;
		if (randomico == 0) {
			if (coelho->aceleracaoCorrente.direcao == NORTE || coelho->aceleracaoCorrente.direcao == SUL) {
				coelho->posicaoCorrente.x -= coelho->velocidadeCorrente;
				coelho->aceleracaoCorrente.direcao = LESTE;
			} else {
				coelho->posicaoCorrente.y += coelho->velocidadeCorrente;
				coelho->aceleracaoCorrente.direcao = NORTE;
			}
		} else if (randomico == 1) {
			if (coelho->aceleracaoCorrente.direcao == NORTE || coelho->aceleracaoCorrente.direcao == SUL) {
				coelho->posicaoCorrente.x += coelho->velocidadeCorrente;
				coelho->aceleracaoCorrente.direcao = OESTE;
			} else {
				coelho->posicaoCorrente.y -= coelho->velocidadeCorrente;
				coelho->aceleracaoCorrente.direcao = SUL;
			}
		}

	} else {

		switch (coelho->aceleracaoCorrente.direcao) {
		case NORTE:
			coelho->posicaoCorrente.y = coelho->posicaoCorrente.y + coelho->velocidadeCorrente;
			break;

		case LESTE:
			coelho->posicaoCorrente.x += coelho->velocidadeCorrente;
			break;

		case SUL:
			coelho->posicaoCorrente.y -= coelho->velocidadeCorrente;
			break;
		case OESTE:
			coelho->posicaoCorrente.x -= coelho->velocidadeCorrente;
			break;
		}

	}

	if (coelho->posicaoCorrente.y < 0) {
		coelho->posicaoCorrente.y = coelho->posicaoCorrente.y + coelho->velocidadeCorrente/2;
		coelho->velocidadeCorrente = coelho->velocidadeCorrente/2;
		coelho->aceleracaoCorrente.direcao = rand() % 2 == 0 ? LESTE : OESTE;
	} else if (coelho->posicaoCorrente.y > 19) {
		coelho->posicaoCorrente.y = coelho->posicaoCorrente.y - coelho->velocidadeCorrente/2;
		coelho->velocidadeCorrente = coelho->velocidadeCorrente/2;
		coelho->aceleracaoCorrente.direcao = rand() % 2 == 0 ? LESTE : OESTE;
	}

	if (coelho->posicaoCorrente.x < 0) {
		coelho->posicaoCorrente.x = coelho->posicaoCorrente.x + coelho->velocidadeCorrente/2;
		coelho->velocidadeCorrente = coelho->velocidadeCorrente/2;
		coelho->aceleracaoCorrente.direcao = rand() % 2 == 0 ? NORTE : SUL;
	} else if (coelho->posicaoCorrente.x > 19) {
		coelho->posicaoCorrente.x = coelho->posicaoCorrente.x - coelho->velocidadeCorrente/2;
		coelho->velocidadeCorrente = coelho->velocidadeCorrente/2;
		coelho->aceleracaoCorrente.direcao = rand() % 2 == 0 ? NORTE : SUL;
	}

}

double calcularDistanciaEntreAnimais(posicao coelho, posicao leopardo) {
	return sqrt(pow(coelho.y - leopardo.y, 2) + pow(coelho.x - leopardo.x, 2));
}

int verifyInitString(FILE *file) {
	char c;

	if (feof(file))
		return 1;

	fscanf(file, "%c", &c);

	if (!feof(file))
		fseek(file, sizeof(char) * -1, SEEK_CUR);

	if (c == '\n' || c == '\r' || c == '\t' || c == '\b') {
		return 0;
	}
	return 1;
}

char *loadFile(char *fileName) {
	FILE *file = fopen(fileName, "r");
	char *fileLoad = "";

	if (file == NULL
		)
		return NULL;

	while (feof(file) == 0) {
		char *linha, c;

		linha = (char *) calloc(1, sizeof(char) * 255);

		int stringLida = fscanf(file, "%254[^\n]", linha);
		if (stringLida >= 0) {
			fileLoad = concatStringNoFreeSrc(fileLoad, linha);
		}

		int charLido = 0;
		while (feof(file) == 0 && !verifyInitString(file)) {
			charLido = fscanf(file, "%c", &c);
			if (charLido < 0)
				break;
			fileLoad = concat(fileLoad, c);
		}
	}

	fclose(file);

	return fileLoad;
}
