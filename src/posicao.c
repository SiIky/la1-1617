#include "check.h"

#include <stdio.h>

#include "posicao.h"

bool posicao_valida (posicao_s p)
{
	/*
	 * Como `abcissa` e `ordenada` sao inteiros sem
	 * sinal, nao e preciso comparar com 0
	 */
	return p.x < TAM && p.y < TAM;
}

bool posicao_igual (posicao_s p1, posicao_s p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}

bool pos_elem (const posicao_p p, size_t num, posicao_s q)
{
	assert(p != NULL);
	bool ret = false;
	for (size_t i = 0;
	     i < num && !(ret = posicao_igual(p[i], q));
	     i++);
	return ret;
}

posicao_s posicao_new (abcissa x, ordenada y)
{
	posicao_s r;
	r.x = x;
	r.y = y;
	return r;
}
