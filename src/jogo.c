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
	char * link = NULL;
	size_t i = 0;

	check(j != NULL);

	if (!jogada_valida(&e, &p))
		return 0;

	e = (posicao_igual(e.porta, p) && fim_de_ronda(&e)) ?
		init_estado(e.nivel + 1) :
		((i = pos_inimigos_ind(e.inimigo, p, e.num_inimigos)) < e.num_inimigos) ?
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
	abcissa x = ~0;
	ordenada y = ~0;

	check(e != NULL);
	check(j != NULL);

	/*
	 *    -1 0 +1
	 * -1 | | | |
	 *    -------
	 *  0 | |J| |
	 *    -------
	 * +1 | | | |
	 */
	for (x = e->jog.pos.x - 1; x <= e->jog.pos.x + 1; x++)
		for (y = e->jog.pos.y - 1; y <= e->jog.pos.y + 1; y++)
			ret += jogadas_aux(*e, (j + ret), posicao_new(x, y));

	return ret;
}

jogada_p jogadas_possiveis (const estado_p e)
{
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
	uchar w = 0;

	check(e != NULL);

	arr[0] = '\0';

	w = jogadas_xadrez_rei(e, ret);

	arr[0] = w;
	return ret;
#undef SIZE
#undef N
}
