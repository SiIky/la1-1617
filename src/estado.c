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
	assert(e != NULL);
	posicao_s ret = { (~0), (~0) };

	do {
		ret.x = rand() % TAM;
		ret.y = rand() % TAM;
	} while (posicao_ocupada(e, ret));

	return ret;
}

bool fim_de_jogo (const estado_p e)
{
	assert(e != NULL);
	return e->jog.vida == 0;
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
	assert(vida > 0);

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
	e.jog.vida = 20 + e.nivel;
	return e;
}

estado_s init_porta (estado_s e)
{
	e.porta = nova_posicao_unica(&e);
	return e;
}

estado_s init_estado (uchar nivel, uchar score, enum mov_type mt, const char * nome)
{
	assert(nome != NULL);

	estado_s ret = {0};

	strcpy(ret.nome, nome);

	ret.nivel = nivel + 1;
	ret.score = score;
	ret.matou = false;
	ret.mov_type = (mt >= MOV_TYPE_QUANTOS) ?
		(random() % MOV_TYPE_QUANTOS) :
		mt;

	ret = init_jogador(ret);
	ret = init_obstaculos(ret);
	ret = init_porta(ret);
	ret = init_inimigos(ret);

	return ret;
}

estado_s move_jogador (estado_s e, posicao_s p)
{
	e.jog.pos = p;
	e.matou = false;
	/* nao perde vida no fim de uma ronda */
	if (!fim_de_ronda(&e))
		e.jog.vida--;
	return e;
}

estado_s ataca (const estado_p e, const entidades i, uchar I)
{
	assert(e != NULL);
	assert(i != NULL);

	estado_s ne = *e;
	entidade ni = i[I];

	assert(ni.vida > 0);

	ni.vida--;
	ne.jog.vida += 3;

	ne.inimigo[I] = ni;

	if (entidade_dead(&ni)) {
		ne.num_inimigos = entidade_remove(ne.inimigo, I, ne.num_inimigos);
		ne.matou = true;
		ne.score++;
	}

	return ne;
}
