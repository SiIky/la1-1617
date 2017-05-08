#include "check.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estado.h"
#include "entidades.h"

bool posicao_ocupada (const estado_p e, posicao_s p)
{
	assert(e != NULL);
	return (pos_inimigos(e->inimigo, p,  e->num_inimigos)
		|| pos_inimigos(e->obstaculo, p,  e->num_obstaculos)
		|| posicao_igual(e->jog.pos, p));
}

posicao_s nova_posicao_unica (const estado_p e)
{
	posicao_s ret = { (~0), (~0) };

	assert(e != NULL);

	do {
		ret.x = rand() % TAM;
		ret.y = rand() % TAM;
	} while (posicao_ocupada(e, ret));

	return ret;
}

char * estado2str (const estado_p e)
{
	static char ret[MAX_BUFFER] = "";
	const char * p = (const char *) e;
	char tmp[(sizeof(char) << 1) + 1] = "";
	size_t r = 0;

	assert(e != NULL);

	ret[0] = '\0';

	for (r = 0; r < sizeof(estado_s); r++) {
		sprintf(tmp, "%02x", p[r]);
		strcat(&ret[r << 1], tmp);
	}

	return ret;
}

estado_s str2estado (char * args)
{
	estado_s ret;
	uchar * p = (uchar *) &ret;
	size_t r = 0;

	assert(args != NULL);

	for (r = 0; r < sizeof(estado_s); r++) {
		unsigned int w = 0;
		sscanf(&args[r << 1], "%02x", &w);
		p[r] = (uchar) w;
	}

	return ret;
}

bool fim_de_ronda (const estado_p e)
{
	assert(e != NULL);
	return e->num_inimigos == 0;
}

void init_entidades (estado_p e, entidades p, uchar N, uchar * num, uchar vida)
{
	assert(e != NULL);
	assert(p != NULL);
	assert(num != NULL);

	for ((*num) = 0; (*num) < N; (*num)++) {
		p[(*num)].pos = nova_posicao_unica(e);
		p[(*num)].vida = vida;
	}
}

#define min(A, B)	((A) < (B)) ? (A) : (B)
estado_s init_inimigos (estado_s e)
{
	uchar N = min(MIN_INIMIGOS + e.nivel, MAX_INIMIGOS);
	init_entidades(&e, e.inimigo, N, &e.num_inimigos, 1);
	return e;
}

estado_s init_obstaculos (estado_s e)
{
	uchar N = min(MIN_OBSTACULOS + e.nivel, MAX_OBSTACULOS);
	init_entidades(&e, e.obstaculo, N, &e.num_obstaculos, 1);
	return e;
}
#undef min

estado_s init_jogador (estado_s e)
{
	e.jog.pos = nova_posicao_unica(&e);
	e.jog.vida = 3 + e.nivel;
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
	ret.matou = false;
	ret.mov_type = MOV_TYPE_XADREZ_CAVALO;

	ret = init_jogador(ret);

	ret = init_obstaculos(ret);
	ret = init_inimigos(ret);

	ret = init_porta(ret);

	return ret;
}

estado_s move_jogador (estado_s e, posicao_s p)
{
	e.jog.pos = p;
	e.matou = false;
	return e;
}

estado_s ataca(const estado_p e, const entidades i, uchar I)
{
	estado_s ne;
	entidade ni;

	assert(e != NULL);
	assert(i != NULL);

	ne = *e;
	ni = i[I];

	ni.vida--;

	ne.inimigo[I] = ni;

	if (entidade_dead(&ni)) {
		ne.num_inimigos = entidade_remove(ne.inimigo, I, ne.num_inimigos);
		ne.matou = true;
	}

	return ne;
}
