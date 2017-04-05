#ifndef _POSICAO_H
#define _POSICAO_H

#define TAM		10

typedef unsigned char abcissa;
typedef unsigned char ordenada;

typedef struct {
	abcissa x;
	ordenada y;
} posicao_s, *posicao_p;

#include <stddef.h>

#include "bool.h"

bool posicao_igual (posicao_s p, abcissa x, ordenada y);
bool posicao_valida (abcissa x, ordenada y);
bool tem_merdas (posicao_p p, size_t num, abcissa x, ordenada y);
posicao_s posicao_cpy (posicao_s p);
posicao_s posicao_new (abcissa x, ordenada y);

#endif /* _POSICAO_H */
