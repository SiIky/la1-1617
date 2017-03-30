#ifndef _ESTADO_H
#define _ESTADO_H

#include "posicao.h"

#define TAM	10
#define MAX_BUFFER	10240
#define MAX_INIMIGOS	((TAM * TAM) >> 2)
#define MAX_OBSTACULOS	((TAM * TAM) >> 2)

typedef struct {
	posicao_s jog;
	unsigned char num_inimigos;
	unsigned char num_obstaculos;
	posicao_s inimigo[MAX_INIMIGOS];
	posicao_s obstaculo[MAX_OBSTACULOS];
} estado_s, *estado_p;

char * estado2str (estado_p e);
estado_s str2estado (char * args);
estado_s ler_estado (char * args);

#endif /* _ESTADO_H */
