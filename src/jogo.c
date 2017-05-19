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

uchar pospos_xadrez_rei (posicao_p dst, const posicao_p o)
{
	assert(dst != NULL);
	assert(o != NULL);

	uchar ret = 0;
	for (abcissa x = o->x; x < o->x + 3; x++)
		for (ordenada y = o->y; y < o->y + 3; y++)
			dst[ret++] = posicao_new(x - 1, y - 1);

	return ret;
}

uchar pospos_xadrez_cavalo (posicao_p dst, const posicao_p o)
{
	assert(dst != NULL);
	assert(o != NULL);

	uchar ret = 0;

#define F(X, Y) \
	{                                              \
		posicao_s tmp = posicao_new((X), (Y)); \
		if (posicao_valida(tmp)) {             \
			dst[ret] = tmp;                \
			ret++;                         \
		}                                      \
	}
	F(o->x - 2, o->y - 1);
	F(o->x - 2, o->y + 1);
	F(o->x - 1, o->y - 2);
	F(o->x - 1, o->y + 2);
	F(o->x + 1, o->y - 2);
	F(o->x + 1, o->y + 2);
	F(o->x + 2, o->y - 1);
	F(o->x + 2, o->y + 1);
#undef F

	return ret;
}

typedef uchar (* pospos_handler) (posicao_p dst, const posicao_p o);
const pospos_handler * pospos_handlers (void)
{
	static const pospos_handler ret[MOV_TYPE_QUANTOS] = {
		[MOV_TYPE_XADREZ_REI]    = pospos_xadrez_rei,
		[MOV_TYPE_XADREZ_CAVALO] = pospos_xadrez_cavalo,
	};
	return ret;
}

posicao_p posicoes_possiveis (const estado_p e, posicao_s o)
{
	assert(e != NULL);
	assert(e->mov_type < MOV_TYPE_QUANTOS);
	assert(posicao_valida(o));

#define SIZE (1 + (sizeof(posicao_s) * NJOGADAS))
	static uchar arr[SIZE] = "";
	memset(arr, 0, SIZE);

	const pospos_handler * handlers = pospos_handlers();
	assert(handlers != NULL);

	posicao_p ret = (posicao_p) (arr + 1);
	quantas_jogadas(ret) = handlers[e->mov_type](ret, &o);

	return ret;
#undef SIZE
}

accao_s accao_new (const char * nome, enum accao accao, posicao_s jog, posicao_s dest)
{
	assert(nome != NULL);
	assert(strlen(nome) < JOGADA_LINK_MAX_BUFFER);
	assert(accao < ACCAO_INVALID);

	accao_s ret = (accao_s) {
		.accao = accao,
		.jog = jog,
		.dest = dest,
	};
	strcpy(ret.nome, nome);

	return ret;
}

char * accao2str (accao_s accao)
{
	assert(accao.nome != NULL);
	assert(accao.accao < ACCAO_INVALID);

	static char ret[JOGADA_LINK_MAX_BUFFER] = "";
	memset(ret, 0, JOGADA_LINK_MAX_BUFFER);
	sprintf(ret,
		"%s,"
		"%08x,"
		"%02hhx,"
		"%02hhx,"
		"%02hhx,"
		"%02hhx",
		accao.nome,
		accao.accao,
		accao.jog.x,
		accao.jog.y,
		accao.dest.x,
		accao.dest.y
	       );
	return ret;
}

accao_s str2accao (const char * str)
{
	assert(str != NULL);
	accao_s ret = { 0 };
#ifdef NDEBUG
	sscanf(str,
#else
	int r = sscanf(str,
#endif
	       "%[^,],"
	       "%08x,"
	       "%02hhx,"
	       "%02hhx,"
	       "%02hhx,"
	       "%02hhx",
	       ret.nome,
	       &ret.accao,
	       &ret.jog.x,
	       &ret.jog.y,
	       &ret.dest.x,
	       &ret.dest.y
	      );
	assert(r == 6);
	return ret;
}

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

	char * link = accao2str(accao_new(e.nome, ACCAO_MOVE, e.jog.pos, p));
	assert(link != NULL);

	strcpy(j->link, link);
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
		[MOV_TYPE_XADREZ_REI]    = mov_type_xadrez_rei,
		[MOV_TYPE_XADREZ_CAVALO] = mov_type_xadrez_cavalo,
	};
	return ret;
}

jogada_p jogadas_possiveis (const estado_p e)
{
	assert(e != NULL);
	assert(e->nome != NULL);
	assert(e->mov_type < MOV_TYPE_QUANTOS);

	/* tamanho do array em bytes */
#define SIZE (1 + (sizeof(jogada_s) * NJOGADAS))

	/*
	 * [0] uchar => quantas jogadas possiveis existem
	 * [1] jogada_s
	 * ..
	 * [N] jogada_s
	 */
	static uchar arr[SIZE] = "";
	memset(arr, 0, SIZE);

	const mov_handler * handlers = mov_handlers();
	assert(handlers != NULL);

	jogada_p ret = (jogada_p) (arr + 1);
	quantas_jogadas(ret) = handlers[e->mov_type](e, ret);

	return ret;
#undef SIZE
}

estado_s accao_reset_handler (estado_s e, accao_s accao)
{
	UNUSED(accao);
	assert(e.nome != NULL);
	assert(accao.accao == ACCAO_RESET);
	return init_estado(0, 0, e.nome);
}

estado_s accao_move_handler (estado_s ret, accao_s accao)
{
	assert(ret.nome != NULL);
	assert(accao.accao == ACCAO_MOVE);

	/*
	 * se a posicao da accao nao for igual a do jogador
	 * ou a posicao do jogador nao for valida
	 * ou a posicao de destino nao for valida
	 * nao faz nada
	 */
	ifjmp(!posicao_igual(accao.jog, ret.jog.pos), out);
	ifjmp(!posicao_valida(accao.jog), out);
	ifjmp(!posicao_valida(accao.dest), out);

	size_t i = pos_inimigos_ind(ret.inimigo, accao.dest, ret.num_inimigos);

	ret = (i < ret.num_inimigos) ? /* se tiver inimigo */
		ataca(&ret, ret.inimigo, i) :
		move_jogador(ret, accao.dest);

	if (ret.matou)
		ret = move_jogador(ret, accao.dest);

	if (fim_de_ronda(&ret) && posicao_igual(ret.jog.pos, ret.porta))
		ret = init_estado(ret.nivel, (ret.score + (ret.jog.vida / 5)), ret.nome);

out:
	return ret;
}

enum mov_type mov_type_next (enum mov_type ret)
{
	assert(ret < MOV_TYPE_QUANTOS);
	return (ret + 1) % MOV_TYPE_QUANTOS;
}

estado_s accao_change_mt_handler (estado_s ret, accao_s accao)
{
	assert(ret.nome != NULL);
	assert(accao.accao == ACCAO_CHANGE_MT);
	assert(accao.dest.x < MOV_TYPE_QUANTOS);

	ifjmp(!posicao_igual(ret.jog.pos, accao.jog), out);

	ret.mov_type = accao.dest.x;
	if (!fim_de_ronda(&ret))
		ret.jog.vida--;
out:
	return ret;
}

estado_s accao_ignore_handler (estado_s ret, accao_s accao)
{
	UNUSED(accao);
	assert(ret.nome != NULL);
	assert(accao.accao == ACCAO_IGNORE);
	return ret;
}

typedef estado_s (* accao_handler) (estado_s ret, accao_s accao);
const accao_handler * accao_handlers (void)
{
	static const accao_handler ret[ACCAO_INVALID] = {
		[ACCAO_RESET]     = accao_reset_handler,
		[ACCAO_MOVE]      = accao_move_handler,
		[ACCAO_CHANGE_MT] = accao_change_mt_handler,
		[ACCAO_IGNORE]    = accao_ignore_handler,
	};
	return ret;
}

estado_s corre_accao (estado_s ret, accao_s accao)
{
	ifjmp(accao.accao >= ACCAO_INVALID, out);

	const accao_handler * handlers = accao_handlers();
	ret = handlers[accao.accao](ret, accao);
out:
	return ret;
}

estado_s bot_xadrez_rei (estado_s ret, size_t I)
{
	UNUSED(I);
	assert(ret.nome != NULL);
	assert(ret.mov_type == MOV_TYPE_XADREZ_REI);
	assert(I < ret.num_inimigos);

	return ret;
}

estado_s bot_xadrez_cavalo (estado_s ret, size_t I)
{
	UNUSED(I);
	assert(ret.nome != NULL);
	assert(ret.mov_type == MOV_TYPE_XADREZ_CAVALO);
	assert(I < ret.num_inimigos);

	return ret;
}

typedef estado_s (* bot_handler) (estado_s ret, size_t I);
const bot_handler * bot_handlers (void)
{
	static const bot_handler ret[MOV_TYPE_QUANTOS] = {
		[MOV_TYPE_XADREZ_REI]    = bot_xadrez_rei,
		[MOV_TYPE_XADREZ_CAVALO] = bot_xadrez_cavalo,
	};
	return ret;
}

estado_s bot_joga_aux (estado_s ret, size_t I)
{
	assert(ret.nome != NULL);
	assert(ret.mov_type < MOV_TYPE_QUANTOS);
	assert(I < ret.num_inimigos);

	const bot_handler * handlers = bot_handlers();
	assert(handlers != NULL);
	return handlers[ret.mov_type](ret, I);
}

estado_s bot_joga (estado_s ret)
{
	assert(ret.nome != NULL);

	for (size_t i = 0; i < ret.num_inimigos; i++)
		ret = bot_joga_aux(ret, i);

	return ret;
}

char * pathname (const char * name)
{
	static char ret[11 + 20] = "";
	sprintf(ret, BASE_PATH "%s", name);
	return ret;
}

estado_s ler_estado (accao_s accao)
{
	assert(accao.nome != NULL);
	assert(accao.accao < ACCAO_INVALID);

	estado_s ret = { 0 };

	char * path = pathname(accao.nome);
	assert(path != NULL);

	FILE * f = fopen(path, "rb");

	check(f == NULL, "could not open state file to read");

	check(fread(&ret, sizeof(estado_s), 1, f) != 1,
	      "could not read from state file");

	fclose(f);

	ret = corre_accao(ret, accao);
	ret = bot_joga(ret);

	return ret;
}

void escreve_estado (const estado_p e)
{
	assert(e != NULL);
	assert(e->nome != NULL);

	char * path = pathname(e->nome);
	assert(path != NULL);

	FILE * f = fopen(path, "wb");

	check(f == NULL, "could not open state file to write");

	check(fwrite(e, sizeof(estado_s), 1, f) != 1,
	      "could not write to state file");

	fclose(f);
}

void update_highscore (const estado_p e, struct highscore hs[3])
{
	assert(e != NULL);
	assert(e->nome != NULL);
	assert(fim_de_jogo(e));
	assert(hs != NULL);

	size_t i = 0;
	for (i = 0; i < 3 && e->score < hs[i].score; i++);

	if (i < 3) {
		hs[i].score = e->score;
		strcpy(hs[i].nome, e->nome);
	}
}

void escreve_highscore (struct highscore hs[3])
{
	assert(hs != NULL);
	FILE * f = fopen(SCOREFILE_PATH, "wb");

	check(f == NULL,
	      "could not open highscore file to write");

	check(fwrite(hs, sizeof(struct highscore), 3, f) != 3,
	      "could not write to highscore file");

	fclose(f);
}

struct highscore * ler_highscore (void)
{
	static struct highscore ret[3] = {0};
	FILE * f = fopen(SCOREFILE_PATH, "rb");

	check(f == NULL,
	      "could not open highscore file to read");

	memset(ret, 0, 3 * sizeof(struct highscore));
	fread(ret, sizeof(struct highscore), 3, f);

	ifnnull(f, fclose);

	return ret;
}
