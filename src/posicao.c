/** @file */
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

/**
 * @brief Filtra um array de posicoes.
 * @param p Um array de posicoes.
 * @param num O numero de posicoes no array.
 * @param f O predicado.
 * @returns O numero de posicoes que satisfizeram o predicado.
 */
size_t pos_filter (posicao_p p, size_t num, bool (* f) (posicao_s))
{
	assert(p != NULL);
	assert(num > 0);
	assert(f != NULL);

	size_t w = 0;

	for (size_t r = 0; r < num; r++)
		if (f(p[r]))
			p[w++] = p[r];

	return w;
}

/**
 * @brief Calcula o quadrado da distancia entre 2 posicoes.
 * @param p1 Uma posicao.
 * @param p2 Outra posicao.
 * @returns O quadrado da distancia entre as 2 posicoes.
 */
ssize_t pos_sq_dist (posicao_s p1, posicao_s p2)
{
	ssize_t dx = p1.x - p2.x;
	ssize_t dy = p1.y - p2.y;
	return (dx * dx) + (dy * dy);
}

size_t pos_mais_perto (const posicao_p ps, size_t N, posicao_s p)
{
	assert(ps != NULL);
	assert(N > 0);
	size_t ret = 0;
	for (size_t i = 1; i < N; i++)
		ret = (pos_sq_dist(ps[ret], p) <= pos_sq_dist(ps[i], p)) ?
			i :
			ret;
	return ret;
}

posicao_s posicao_new (abcissa x, ordenada y)
{
	return (posicao_s) {
		.x = x,
		.y = y,
	};
}
