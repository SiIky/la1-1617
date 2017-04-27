#include <assert.h>
#include <stdlib.h>

#include "posicao.h"
#include "estado.h"

#include "html.h"

void imprime_entidades (const entidades p, size_t max, char * img)
{
	size_t i = 0;

	assert(p != NULL);
	assert(img != NULL);

	for (i = 0; i < max; i++)
		IMAGE(p[i].pos.x, p[i].pos.y, ESCALA, img);
}

void imprime_inimigos (const estado_p e)
{
	assert(e != NULL);
	imprime_entidades(e->inimigo, e->num_inimigos, IMG_INIMIGO);
}

void imprime_jogada (const estado_p e, posicao_s p)
{
	estado_s ne;
	char * query = NULL;
	size_t i;

	assert(e != NULL);

	ne = *e;

	if (!posicao_valida(p)
	    || pos_inimigos(ne.obstaculo, p , ne.num_obstaculos)
	    || posicao_igual(ne.jog.pos, p))
		return;

	ne = (posicao_igual(ne.porta, p) && fim_de_ronda(&ne)) ?
		init_estado(ne.nivel + 1) :
		((i = pos_inimigos_ind(ne.inimigo, p, ne.num_inimigos)) < ne.num_inimigos) ?
		ataca(&ne, ne.inimigo, i) :
		move_jogador(ne, p);

	query = estado2str(&ne);

	assert(query != NULL);
	GAME_LINK(query);
	RECT_TRANSPARENTE(p.y, p.x, ESCALA);
	FECHA_A;
}

void imprime_jogadas (const estado_p e)
{
	abcissa x = (~0);
	ordenada y = (~0);

	assert(e != NULL);

	imprime_entidades(&e->jog, 1, IMG_JOGADOR);

	/*	abcissa mx = e->jog.x - 1; */
	/*	ordenada my = e->jog.y - 1; */

	/*	abcissa Mx = e->jog.x + 1; */
	/*	ordenada My = e->jog.y + 1; */

	/*	for (abcissa x = mx; x <= Mx; x++) */
	/*		for (ordenada y = my; y <= My; y++) */
	/*			imprime_jogada(e, x, y); */

	/* desta forma estupida o bug dos cantos nao acontece */
	x = e->jog.pos.x;
	y = e->jog.pos.y;

	imprime_jogada(e, posicao_new(x-1, y-1));
	imprime_jogada(e, posicao_new(x-1, y));
	imprime_jogada(e, posicao_new(x-1, y+1));
	imprime_jogada(e, posicao_new(x,   y-1));
	imprime_jogada(e, posicao_new(x,   y+1));
	imprime_jogada(e, posicao_new(x+1, y-1));
	imprime_jogada(e, posicao_new(x+1, y));
	imprime_jogada(e, posicao_new(x+1, y+1));
}

void imprime_obstaculos (const estado_p e)
{
	assert(e != NULL);
	imprime_entidades(e->obstaculo, e->num_obstaculos, IMG_OBSTACULO);
}

char * random_color (void)
{
	/*
	 * cada cor tem 3 bytes,
	 * logo existem 2 ^ (3 * 8)
	 * cores diferentes
	 */
#define NUM_CORES	(1 << (3 * 8))
	unsigned int rgb = rand() % NUM_CORES;
#undef NUM_CORES

	/* "#rrggbb0" */
	static char ret[8] = "#";
	sprintf(ret+1, "%06x", rgb);
	ret[7] = '\0';

	return ret;
}

void imprime_casa (size_t l, size_t c)
{
	RECT(l, c, ESCALA, random_color());
}

void imprime_tabuleiro (abcissa L, ordenada C)
{
	size_t l = 0;
	size_t c = 0;
	for (l = 0; l < L; l++) {
		for (c = 0; c < C; c++)
			imprime_casa(l, c);
		putchar('\n');
	}
}

void imprime_porta (const estado_p e)
{
	assert(e != NULL);
	IMAGE(e->porta.x, e->porta.y, ESCALA, IMG_PORTA);
}

void imprime_jogo (const estado_p e)
{
	assert(e != NULL);

	ABRE_SVG(SVG_WIDTH, SVG_HEIGHT); {
		COMMENT("tabuleiro");
		imprime_tabuleiro(TAM, TAM);

		COMMENT("porta");
		imprime_porta(e);

		COMMENT("obstaculos");
		imprime_obstaculos(e);

		COMMENT("inimigos");
		imprime_inimigos(e);

		COMMENT("jogadas");
		imprime_jogadas(e);
	} FECHA_SVG;
}
