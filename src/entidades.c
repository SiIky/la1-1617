#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "posicao.h"

#include "entidades.h"

char * entidade2str (const entidades e)
{
	static char ret[((sizeof(entidade)) << 1) + 1] = "";
	char * tmp = (char *) e;
	size_t i = 0;

	assert(e != NULL);

	ret[0] = '\0';

	for (i = 0; i < sizeof(entidade); i++)
		sprintf(ret + (i << 1), "%02x", tmp[i]);

	return ret;
}

entidade str2entidade (const char * args)
{
	entidade ret;
	char * tmp = (char *) &ret;
	unsigned int d = 0;
	size_t i = 0;

	assert(args != NULL);

	for (i = 0; i < sizeof(entidade); i++)
		sscanf(args + (i << 1), "%2x", &d), tmp[i] = (char) d;

	return ret;
}

size_t pos_inimigos_ind (const entidades e, posicao_s p, size_t num_inimigos)
{
	size_t i = num_inimigos;
	assert(e != NULL);
	for (i = 0; i < num_inimigos && !(posicao_igual(e[i].pos, p)) ; i++);
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

	for (; i < (N - 1); i++)
		e[i] = e[i+1];

	return N - 1;
}