#ifndef _ESTADO_H
#define _ESTADO_H

#define MAX_BUFFER	10240

typdef struct {
	posicao_s jog;
	unsigned char num_inimigos;
	unsigned char num_obstaculos;
	posicao_s inimigo[MAX_INIMIGOS]
	posicao_s obstaculo[MAX_OBSTACULOS]
} estado_s, *estado_p;

char *estado2str (estado_p e);
estado_s str2estado (char *argumentos);
#endif /* _ESTADO_H */
