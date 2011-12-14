#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define LEOPARDO_KEY "LEOPARDO_KEY"
#define LEOPARDO_KEY_VALUE "LEOPARDO_KEY_VALUE"
#define COELHO_KEY "COELHO_KEY"
#define COELHO_KEY_VALUE "COELHO_KEY_VALUE"

#define VELOCIDADE_MAXIMA_LEOPARDO 4
#define VELOCIDADE_MAXIMA_COELHO 2

typedef enum DIRECAO { NORTE, NORDESTE, LESTE, SULDESTE, SUL, SUDOESTE, OESTE, NOROESTE, COMI } DIRECAO;

typedef struct posicao {
	double x, y;
} posicao;

typedef struct aceleracao {
	DIRECAO direcao;
	double valor;
} aceleracao;

typedef struct animal {
	posicao posicaoCorrente;
	double velocidadeCorrente;
	aceleracao aceleracaoCorrente;
	int massa;
	posicao *posicoes;

} animal;

typedef struct tagReplace {
	char *oldContent;
	char *newContent;
} tagReplace;

#endif
