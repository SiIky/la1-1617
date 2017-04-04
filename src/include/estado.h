#ifndef _ESTADO_H
#define _ESTADO_H

#include "posicao.h"

#define TAM		10
#define MAX_BUFFER	10240
#define MAX_INIMIGOS	(TAM)
#define MAX_OBSTACULOS	(TAM)

typedef struct {
	posicao_s jog;
	unsigned char num_inimigos;
	unsigned char num_obstaculos;
	posicao_s inimigo[MAX_INIMIGOS];
	posicao_s obstaculo[MAX_OBSTACULOS];
} estado_s, *estado_p;

char * estado2str (const estado_p e);
estado_s str2estado (char * args);
estado_s ler_estado (char * args);

posicao_s nova_posicao_unica (const estado_p e);

estado_s init_inimigos (estado_s e);
estado_s init_obstaculos (estado_s e);
estado_s init_jogador (estado_s e);
estado_s init_estado (void);
estado_s move_jogador (estado_s e, posicao_s p);

#endif /* _ESTADO_H */
