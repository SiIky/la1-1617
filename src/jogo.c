#include "check.h"

#include <string.h>

#include "posicao.h"
#include "estado.h"

#include "jogo.h"

/*
 * Tipos de movimento:
 * [X] Rei do Xadrez
 * [X] Cavalo do Xadrez
 * [ ] Peao do Xadrez
 * [ ] Torre do Xadrez
 * [ ] Bispo do Xadrez
 * [ ] Rainha do Xadrez
 * [ ] Damas
 */

bool jogada_valida (const estado_p e, const posicao_p p)
{
	assert(e != NULL);
	assert(p != NULL);
	return posicao_valida(*p)
	    && !(pos_inimigos(e->obstaculo, *p, e->num_obstaculos))
	    && !(posicao_igual(e->jog.pos, *p));
}

uchar jogadas_aux (estado_s e, jogada_p j, posicao_s p)
{
	assert(j != NULL);

	if (!jogada_valida(&e, &p))
		return 0;

	sprintf(j->link,
		"%08x,"
		"%02hhx,"
		"%02hhx,"
		"%02hhx,"
		"%02hhx",
		ACCAO_MOVE,
		e.jog.pos.x,
		e.jog.pos.y,
		p.x,
		p.y);

	j->link[JOGADA_LINK_MAX_BUFFER - 1] = '\0';
	j->dest = p;

	return 1;
}

uchar mov_type_xadrez_rei (const estado_p e, jogada_p j)
{
	assert(e != NULL);
	assert(j != NULL);

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

uchar mov_type_xadrez_cavalo (const estado_p e, jogada_p j)
{
	assert(e != NULL);
	assert(j != NULL);

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

typedef uchar (* mov_handler) (const estado_p e, jogada_p j);
const mov_handler * mov_handlers (void)
{
	static const mov_handler ret[MOV_TYPE_QUANTOS] = {
		[MOV_TYPE_XADREZ_REI] = mov_type_xadrez_rei,
		[MOV_TYPE_XADREZ_CAVALO] = mov_type_xadrez_cavalo,
	};
	return ret;
}

jogada_p jogadas_possiveis (const estado_p e)
{
	assert(e != NULL);
	assert(e->mov_type < MOV_TYPE_QUANTOS);

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

	const mov_handler * handlers = mov_handlers();
	uchar w = handlers[e->mov_type](e, ret);

	arr[0] = w;
	return ret;
#undef SIZE
#undef N
}

estado_s accao_reset_handler (estado_s ret, char * args)
{
	ret = init_estado(0);
	return (args != NULL) ? /* calar "unused variable" warning */
		ret :
		ret;
}

estado_s accao_move_handler (estado_s ret, char * args)
{
	assert(args != NULL);

	ifjmp(*args == '\0', out);

	posicao_s p = posicao_new(~0, ~0);
	sscanf(args, "%02hhx,%02hhx", &p.x, &p.y);

	ifjmp(!posicao_valida(p), out);

	size_t i = pos_inimigos_ind(ret.inimigo, p, ret.num_inimigos);

	ret = (i < ret.num_inimigos) ? /* se tiver inimigo */
		ataca(&ret, ret.inimigo, i) :
		move_jogador(ret, p);

	if (ret.matou)
		ret = move_jogador(ret, p);

	if (fim_de_ronda(&ret) && posicao_igual(ret.jog.pos, ret.porta))
		ret = init_estado(ret.nivel);

out:
	return ret;
}

bool link_is_jogada (const estado_p e, char * args)
{
	assert(e != NULL);
	assert(args != NULL);

	jogada_p jogadas = jogadas_possiveis(e);
	uchar quantas = quantas_jogadas(jogadas);
	bool ret = false;

	for (size_t i = 0; i < quantas && !ret; i++)
		ret = (strcmp(args, jogadas[i].link) == 0);

	return ret;
}

bool link_is_menu_action (const char * args)
{
	assert(args != NULL);
	enum accao accao = ACCAO_INVALID;
	sscanf(args, "%08x,", &accao);
	return accao == ACCAO_RESET;
}

typedef estado_s (* accao_handler) (estado_s ret, char * args);
const accao_handler * accao_handlers (void)
{
	static const accao_handler ret[ACCAO_INVALID] = {
		[ACCAO_RESET] = accao_reset_handler,
		[ACCAO_MOVE] = accao_move_handler,
	};
	return ret;
}

estado_s corre_accao (estado_s ret, char * args)
{
	assert(args != NULL);

	/* se a query string nao for uma jogada nem uma das
	   accoes do menu */
	ifjmp(!link_is_jogada(&ret, args)
	      && !link_is_menu_action(args),
	      out);

	enum accao accao = ACCAO_INVALID;
	posicao_s jog = posicao_new(~0, ~0);
	posicao_s dest = posicao_new(~0, ~0);

	ifjmp(*args == '\0', out);

	sscanf(args,
	       "%08x,"
	       "%02hhx,"
	       "%02hhx,"
	       "%02hhx,"
	       "%02hhx",
	       &accao,
	       &jog.x,
	       &jog.y,
	       &dest.x,
	       &dest.y);

	ifjmp(accao >= ACCAO_INVALID, out);
	ifjmp(!posicao_valida(jog), out);
	ifjmp(!link_is_menu_action(args)
	      && !posicao_igual(jog, ret.jog.pos),
	      out);

	const accao_handler * handlers = accao_handlers();
	/* 12 da fmt string acima */
	ret = handlers[accao](ret, args + 12 + 3);
out:
	return ret;
}

estado_s ler_estado (char * args)
{
	estado_s ret = { 0 };
#if 1
	FILE * f = fopen(SHRUG, "rb");
	size_t read = 0;

	if (f == NULL)
		perror("could not open file to read");
	else if ((read = fread(&ret, sizeof(estado_s), 1, f)) != 1)
		perror("could not read from file");

	/* nao ha ficheiro ou nao consegue ler */
	ret = (f == NULL || read != 1) ?
		init_estado(0) :
		/* nao ha query string */
		(args != NULL && *args != '\0') ?
		corre_accao(ret, args) :
		ret; /* conseguiu ler */

	ifnnull(f, fclose);
#else
	ret = (args == NULL || *args == '\0') ?
		init_estado(0) :
		str2estado(args);
#endif
	return ret;
}

void escreve_estado (const estado_p e)
{
	assert(e != NULL);

	FILE * f = fopen(SHRUG, "wb");

	check(f == NULL, "could not open file to write");

	check(fwrite(e, sizeof(estado_s), 1, f) != 1,
	      "could not write to file");

	fclose(f);
}
