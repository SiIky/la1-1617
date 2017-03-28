#ifndef _POSICAO_H
#define _POSICAO_H

typedef unsigned char abcissa;
typedef unsigned char ordenada;

typedef struct {
	abcissa x;
	ordenada y;
} posicao_s, *posicao_p;

#include "bool.h"

bool posicao_igual (posicao_s p, abcissa x, ordenada y);
bool posicao_valida (abcissa x, ordenada y);

#endif /* _POSICAO_H */
