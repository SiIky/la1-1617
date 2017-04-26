#ifndef _ESTADO_H
#define _ESTADO_H

#include "posicao.h"

#define MAX_BUFFER	10240

#define MIN_INIMIGOS	(TAM)
#define MIN_OBSTACULOS	(MIN_INIMIGOS << 1)

#define MAX_OBSTACULOS	((TAM * TAM) >> 1)
#define MAX_INIMIGOS	(MAX_OBSTACULOS >> 1)

typedef struct {
	uchar nivel;
	uchar num_inimigos;
	uchar num_obstaculos;
	posicao_s jog;
	posicao_s porta;
	posicao_p inimigo;
	posicao_p obstaculo;
} estado_s, *estado_p;

char * estado2str (const estado_p e);
estado_s str2estado (char * args);
estado_s ler_estado (char * args);

bool fim_de_ronda (const estado_p e);
bool posicao_ocupada (const estado_p e, posicao_s p);
posicao_s nova_posicao_unica (const estado_p e);
void init_entidades (estado_p e, posicao_p p, uchar N, uchar * num);

estado_s init_estado (uchar nivel);
estado_s init_inimigos (estado_s e);
estado_s init_jogador (estado_s e);
estado_s init_obstaculos (estado_s e);
estado_s init_porta (estado_s e);
estado_s move_jogador (estado_s e, posicao_s p);

#endif /* _ESTADO_H */
