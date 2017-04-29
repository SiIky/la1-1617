#ifndef _JOGO_H
#define _JOGO_H

#include "posicao.h"
#include "estado.h"

#define quantas_jogadas(J) (*(((uchar *) (J)) - 1))

typedef struct {
	posicao_s dest;
	char link[MAX_BUFFER];
} jogada_s, *jogada_p;

jogada_p jogadas_possiveis (const estado_p e);

#endif /* _JOGO_H */
