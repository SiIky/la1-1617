#include <string.h>

#include "check.h"
#include "posicao.h"
#include "estado.h"

#include "jogo.h"

bool jogada_valida (const estado_p e, const posicao_p p)
{
	check(e != NULL);
	check(p != NULL);
	return posicao_valida(*p)
	    && !(pos_inimigos(e->obstaculo, *p, e->num_obstaculos))
	    && !(posicao_igual(e->jog.pos, *p));
}

uchar jogadas_aux (estado_s e, jogada_p j, posicao_s p)
{
	char * link = NULL;
	size_t i = 0;

	check(j != NULL);

	if (!jogada_valida(&e, &p))
		return 0;

	e = (posicao_igual(e.porta, p) && fim_de_ronda(&e)) ?
		init_estado(e.nivel + 1) :
		((i = pos_inimigos_ind(e.inimigo, p, e. num_inimigos)) < e.num_inimigos) ?
		ataca(&e, e.inimigo, i) :
		move_jogador(e, p);

	link = estado2str(&e);

	check(link != NULL);
	strcpy(j->link, link);
	j->dest = p;

	return 1;
}

uchar jogadas_xadrez_rei (const estado_p e, jogada_p j)
{
	uchar ret = 0;

	check(e != NULL);
	check(j != NULL);

#define F(X, Y) ret += jogadas_aux(*e, (j + ret), posicao_new(e->jog.pos.y + (X), e->jog.pos.x + (Y)))
	F(-1, -1);
	F(-1, +0);
	F(-1, +1);
	F(+0, -1);
	F(+0, +1);
	F(+1, -1);
	F(+1, +0);
	F(+1, +1);
#undef F

	return ret;
}

jogada_p jogadas_possiveis (const estado_p e)
{
	/*
	 * [0] uchar => quantas jogadas possiveis existem
	 * [1] jogada_s
	 * ..
	 * [N] jogada_s
	 */
#define N (sizeof(jogada_s) * 9)
	static jogada_s ret[N] = { 0 };
	uchar w = 0;

	check(e != NULL);

	w = jogadas_xadrez_rei(e, ret + 1);

	return ret->dest.x = w, ret;
#undef N
}
