/** @file */
#ifndef _POSICAO_H
#define _POSICAO_H

#define TAM		10

typedef unsigned char uchar;
typedef uchar abcissa;
typedef uchar ordenada;

typedef struct {
	abcissa x;
	ordenada y;
} posicao_s, *posicao_p;

#include <stddef.h>
#include <stdbool.h>

bool posicao_igual (posicao_s p1, posicao_s p2);
bool posicao_valida (posicao_s p);
bool pos_elem (const posicao_p p, size_t num, posicao_s q);
posicao_s posicao_new (abcissa x, ordenada y);
size_t pos_filter (posicao_p p, size_t num, bool (* f) (posicao_s));
size_t pos_mais_perto (const posicao_p ps, size_t N, posicao_s p);

#endif /* _POSICAO_H */
