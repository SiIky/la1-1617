#include "jogo.h"

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

bool tem_merdas (posicao_p p, size_t num, abcissa x, ordenada y)
{
	if (p != NULL)
		for (size_t i = 0; i < num; i++)
			if (posicao_igual(p[i], x, y))
				return true;

	return false;
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

void posicoes_cpy (posicao_p to, posicao_p from, size_t N)
{
	if (to == NULL || from == NULL)
		return;
	for (size_t i = 0; i < N; i++)
		to[i] = posicao_cpy(from[i]);
}
