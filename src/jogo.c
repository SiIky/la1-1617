#include <string.h>

#include "check.h"
#include "posicao.h"
#include "estado.h"

#include "jogo.h"

/*
 * Tipos de movimento:
 * - [X] Rei do Xadrez
 * - [ ] Cavalo do Xadrez
 * - [ ] Peao do Xadrez
 * - [ ] Torre do Xadrez
 * - [ ] Bispo do Xadrez
 * - [ ] Rainha do Xadrez
 * - [ ] Damas
 */

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
	check(j != NULL);

	if (!jogada_valida(&e, &p))
		return 0;

	size_t i = 0;
	e = ((i = pos_inimigos_ind(e.inimigo, p, e.num_inimigos)) < e.num_inimigos) ?
		ataca(&e, e.inimigo, i) :
		move_jogador(e, p);

	/*
	 * se o jog tiver na porta e matar o ult
	 * inimigo tem de passar ao nivel seguinte
	 */
	if (posicao_igual(e.porta, e.jog.pos) && fim_de_ronda(&e))
		e = init_estado(e.nivel + 1);

	if (e.matou)
		e = move_jogador(e, p);

	char * link = estado2str(&e);

	check(link != NULL);
	strcpy(j->link, link);
	j->dest = p;

	return 1;
}

uchar jogadas_xadrez_rei (const estado_p e, jogada_p j)
{
	check(e != NULL);
	check(j != NULL);

	/*
	 *    1 0 1
	 * 1 |X|X|X|
	 *   -------
	 * 0 |X|J|X|
	 *   -------
	 * 1 |X|X|X|
	 */

	uchar ret = 0;
	for (abcissa x = e->jog.pos.x; x < e->jog.pos.x + 3; x++)
		for (ordenada y = e->jog.pos.y; y < e->jog.pos.y + 3; y++)
			ret += jogadas_aux(*e, (j + ret), posicao_new(x-1, y-1));

	return ret;
}

uchar jogadas_xadrez_cavalo (const estado_p e, jogada_p j)
{
	check(e != NULL);
	check(j != NULL);

	/*
	 *    2 1 0 1 2
	 * 2 | |X| |X| |
	 *   -----------
	 * 1 |X| | | |X|
	 *   -----------
	 * 0 | | |J| | |
	 *   -----------
	 * 1 |X| | | |X|
	 *   -----------
	 * 2 | |X| |X| |
	 */

	uchar ret = 0;

#define F(X, Y) ret += jogadas_aux(*e, (j + ret), posicao_new((X), (Y)))
#define X e->jog.pos.x
#define Y e->jog.pos.y
	F(X - 2, Y - 1);
	F(X - 2, Y + 1);
	F(X - 1, Y - 2);
	F(X - 1, Y + 2);
	F(X + 1, Y - 2);
	F(X + 1, Y + 2);
	F(X + 2, Y - 1);
	F(X + 2, Y + 1);
#undef Y
#undef X
#undef F

	return ret;
}

jogada_p jogadas_possiveis (const estado_p e)
{
	check(e != NULL);

	/* numero maximo de jogadas */
#define N    8
	/* tamanho do array em bytes */
#define SIZE (1 + (sizeof(jogada_s) * N))

	/*
	 * [0] uchar => quantas jogadas possiveis existem
	 * [1] jogada_s
	 * ..
	 * [N] jogada_s
	 */
	static uchar arr[SIZE] = "";
	jogada_p ret = (jogada_p) (arr + 1);

	arr[0] = '\0';

	uchar w = 0;
	switch (e->mov_type) {
		case MOV_TYPE_XADREZ_REI:
			w = jogadas_xadrez_rei(e, ret);
		break;
		case MOV_TYPE_XADREZ_CAVALO:
			w = jogadas_xadrez_cavalo(e, ret);
		break;
	}

	arr[0] = w;
	return ret;
#undef SIZE
#undef N
}
