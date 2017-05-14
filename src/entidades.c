#include "check.h"

#include <stdio.h>
#include <string.h>

#include "posicao.h"

#include "entidades.h"

size_t pos_inimigos_ind (const entidades e, posicao_s p, size_t num_inimigos)
{
	size_t i = 0;
	assert(e != NULL);
	for (i = 0; i < num_inimigos && !(posicao_igual(e[i].pos, p)); i++);
	return i;
}

bool pos_inimigos (const entidades e, posicao_s p, size_t num_inimigos)
{
	return pos_inimigos_ind(e, p, num_inimigos) < num_inimigos;
}

bool entidade_dead (const entidades e)
{
	assert(e != NULL);
	return e->vida == 0;
}

uchar entidade_remove (entidades e, size_t i, size_t N)
{
	assert(e != NULL);
	assert(i < N);

	N--;
	e[i] = e[N];

	return N;
}