#include <assert.h>
#include <stdio.h>

#include "posicao.h"

char * posicao2str (posicao_p p)
{
	static char ret[sizeof(posicao_s) << 1];
	assert(p != NULL);

	sprintf(ret, "%02x", p->x);
	sprintf(ret+2, "%02x", p->y);

	return ret;
}

posicao_s str2posicao (char * args)
{
	posicao_s ret = {0};
	unsigned int d = 0;

	assert(args != NULL);

	sscanf(args, "%2x", &d);
	ret.x = (uchar) d;

	args += 2;

	sscanf(args, "%2x", &d);
	ret.y = (uchar) d;

	return ret;
}

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
	bool ret = false;
	size_t i = 0;
	assert(p != NULL);
	for (i = 0; i < num && !(ret = posicao_igual(p[i], q)); i++);
	return ret;
}

posicao_s posicao_new (abcissa x, ordenada y)
{
	posicao_s r;
	r.x = x;
	r.y = y;
	return r;
}
