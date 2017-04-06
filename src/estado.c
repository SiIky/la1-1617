#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estado.h"

bool posicao_ocupada (const estado_p e, abcissa x, ordenada y)
{
	return (e != NULL)
		&& (pos_elem(e->inimigo, e->num_inimigos, x, y)
		|| pos_elem(e->obstaculo, e->num_obstaculos, x, y)
		|| posicao_igual(e->jog, x, y));
}

posicao_s nova_posicao_unica (const estado_p e)
{
	abcissa x;
	ordenada y;

	do {
		x = rand() % TAM;
		y = rand() % TAM;
	} while (posicao_ocupada(e, x, y));

	return posicao_new(x, y);
}

char * estado2str (const estado_p e)
{
	if (e == NULL)
		return NULL;
	static char buffer[MAX_BUFFER];
	char *p = (char *) e;
	buffer[0] = '\0';

	for (size_t i = 0; i < sizeof(estado_s); i++)
		sprintf(buffer, "%s%02x", buffer, p[i]);
	return buffer;
}

estado_s str2estado (char * args)
{
	estado_s e;
	char * p = (char *) &e;

	for (size_t i = 0; i < sizeof(estado_s); i++) {
		unsigned int d;
		sscanf(args + (i << 1), "%2x", &d);
		p[i] = (char) d;
	}

	return e;
}

bool fim_de_ronda (const estado_p e)
{
	// Temporário, só para a primeira etapa.
	return true || e != NULL;
	//return e != NULL && e->num_inimigos == 0;
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
	init_entidades(&e, e.inimigo, N, &e.num_inimigos);
	return e;
}

estado_s init_obstaculos (estado_s e)
{
	uchar N = min(MIN_OBSTACULOS + e.nivel, MAX_OBSTACULOS);
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
