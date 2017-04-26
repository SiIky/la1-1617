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

posicao_s str2posicao(char * args);
bool posicao_igual (posicao_s p1, posicao_s p2);
bool posicao_valida (posicao_s p);
bool pos_elem (const posicao_p p, size_t num, posicao_s q);
posicao_s posicao_new (abcissa x, ordenada y);

#endif /* _POSICAO_H */
