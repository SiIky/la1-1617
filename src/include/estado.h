#ifndef _ESTADO_H
#define _ESTADO_H

#include "posicao.h"

#define TAM	10
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

estado_s init_estado (void);
estado_s ler_estado (char * args);
estado_s str2estado (char * args);
char * estado2str (estado_p e);

void init_entidade (estado_p e, posicao_p p);
void init_entidades (estado_p e, posicao_p p, unsigned char * num, size_t max);
void init_inimigos (estado_p e);
void init_obstaculos (estado_p e);
void init_jogador (estado_p e);

#endif /* _ESTADO_H */
