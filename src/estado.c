#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estado.h"

bool posicao_ocupada (const estado_p e, posicao_s p)
{
	return (e != NULL)
		&& (pos_elem(e->inimigo, e->num_inimigos, p)
		|| pos_elem(e->obstaculo, e->num_obstaculos, p)
		|| posicao_igual(e->jog, p));
}

posicao_s nova_posicao_unica (const estado_p e)
{
	posicao_s ret = { (~0), (~0) };
	do {
		ret.x = rand() % TAM;
		ret.y = rand() % TAM;
	} while (posicao_ocupada(e, ret));

	return ret;
}

char * estado2str (const estado_p e)
{
#define write(TO, FROM, W)
	size_t i = 0;
	static char buffer[MAX_BUFFER];
	char tmp[4];
	char *p = (char *) e;
	buffer[0] = '\0';

	/* nivel; */
	sprintf(tmp, "%02x", p[i]);
	strcat(buffer,
	i++;


	/* num_inimigos; */
	sprintf(tmp, "%02x", p[i]);
	strcat();
	i++;

	/* num_obstaculos; */

	/* jog; */
	/* porta; */
	/* inimigo; */

	if (e == NULL)
		return NULL;

	for (i = 0; i < sizeof(estado_s); i++)
		sprintf(buffer, "%s%02x", buffer, p[i]);
	return buffer;
#undef write
}

estado_s str2estado (char * args)
{
#define read(STR, I, W, D) \
	sscanf((STR) + (I), "%2x", &(D)); \
	(W) = (uchar) (D); \
	(I) += 2;

	estado_s e;
	unsigned int d = 0;
	size_t i = 0;

	/* nivel; */
	read(args, i, e.nivel, d);

	/* num_inimigos; */
	read(args, i, e.num_inimigos, d);

	/* num_obstaculos; */
	read(args, i, e.num_obstaculos, d);

	/* jog; */
	e.jog = str2posicao(args + i);
	i += 2;

	/* porta; */
	e.porta = str2posicao(args + i);
	i += 2;

	/* inimigo */
	for (d = 0; d < e.num_inimigos; d++, i += 2)
		e.inimigo[d] = str2posicao(args + i);

	/* obstaculo */
	for (d = 0; d < e.num_obstaculos; d++, i += 2)
		e.obstaculo[d] = str2posicao(args + i);

	return e;
#undef read
}

bool fim_de_ronda (const estado_p e)
{
	/* Temporário, só para a primeira etapa. */
	return true || e != NULL;
	/*return e != NULL && e->num_inimigos == 0;*/
}

void init_entidades (estado_p e, posicao_p p, uchar N, uchar * num)
{
	if (e != NULL && p != NULL && num != NULL)
		for ((*num) = 0; (*num) < N; (*num)++)
			p[(*num)] = nova_posicao_unica(e);
}

#define min(A, B)	((A) < (B)) ? (A) : (B)
estado_s init_inimigos (estado_s e)
{
	uchar N = min(MIN_INIMIGOS + e.nivel, MAX_INIMIGOS);

	e.inimigo = (posicao_p) calloc(N, sizeof(posicao_s));

	assert(e.inimigo != NULL);

	init_entidades(&e, e.inimigo, N, &e.num_inimigos);
	return e;
}

estado_s init_obstaculos (estado_s e)
{
	uchar N = min(MIN_OBSTACULOS + e.nivel, MAX_OBSTACULOS);

	e.obstaculo = (posicao_p) calloc(N, sizeof(posicao_s));

	assert(e.obstaculo != NULL);

	init_entidades(&e, e.obstaculo, N, &e.num_obstaculos);
	return e;
}
#undef min

estado_s init_jogador (estado_s e)
{
	e.jog = nova_posicao_unica(&e);
	return e;
}

estado_s init_porta (estado_s e)
{
	e.porta = nova_posicao_unica(&e);
	return e;
}

estado_s init_estado (uchar nivel)
{
	estado_s ret = {0};

	ret.nivel = nivel;

	ret = init_obstaculos(ret);
	ret = init_porta(ret);
	ret = init_inimigos(ret);
	ret = init_jogador(ret);

	return ret;
}

estado_s ler_estado (char * args)
{
	return (args == NULL || strlen(args) == 0) ?
		init_estado(0) :
		str2estado(args);
}

estado_s move_jogador (estado_s e, posicao_s p)
{
	e.jog = p;
	return e;
}
