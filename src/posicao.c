#include "posicao.h"

bool posicao_valida (abcissa x, ordenada y)
{
	/*
	 * Como `abcissa` e `ordenada` sao inteiros sem
	 * sinal, nao e preciso comparar com 0
	 */
	return x < TAM && y < TAM;
}

bool posicao_igual (posicao_s p, abcissa x, ordenada y)
{
	return p.x == x && p.y == y;
}

bool pos_elem (posicao_p p, size_t num, abcissa x, ordenada y)
{
	bool ret = false;
	if (p != NULL)
		for (size_t i = 0; i < num && !(ret = posicao_igual(p[i], x, y)); i++);
	return ret;
}

posicao_s posicao_new (abcissa x, ordenada y)
{
	static posicao_s ret;
	ret.x = x;
	ret.y = y;
	return ret;
}

posicao_s posicao_cpy (posicao_s p)
{
	return posicao_new(p.x, p.y);
}
