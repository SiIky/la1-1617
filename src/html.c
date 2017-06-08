/** @file */
#include "check.h"

#include <stdlib.h>

#include "posicao.h"
#include "estado.h"
#include "jogo.h"

#include "html.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Imprime entidades do jogo.
 * @param p As entidades.
 * @param max O numero de entidades.
 * @param img A imagem da entidade.
 */
void imprime_entidades (const entidades p, size_t max, char * img)
{
	size_t i = 0;

	assert(p != NULL);
	assert(img != NULL);

	for (i = 0; i < max; i++)
		IMAGE(p[i].pos.x, p[i].pos.y, ESCALA, img);
}

/**
 * @brief Imprime os inimigos do jogo.
 * @param e O estado actual.
 */
void imprime_inimigos (const estado_p e)
{
	assert(e != NULL);
	imprime_entidades(e->inimigo, e->num_inimigos, IMG_INIMIGO);
}

/**
 * @brief Imprime os obstaculos do jogo.
 * @param e O estado actual.
 */
void imprime_obstaculos (const estado_p e)
{
	assert(e != NULL);
	imprime_entidades(e->obstaculo, e->num_obstaculos, IMG_OBSTACULO);
}

/**
 * @brief Imprime o link de uma jogada.
 * @param j A jogada.
 */
void imprime_jogada (const jogada_p j)
{
	assert(j != NULL);
	assert(j->link != NULL);

	GAME_LINK(j->link); {
		RECT_TRANSPARENTE(j->dest.y, j->dest.x, ESCALA);
	} FECHA_A;
}

/**
 * @brief Imprime as jogadas possiveis do jogador.
 * @param e O estado actual.
 */
void imprime_jogadas (const estado_p e)
{
	uchar N = 0;
	uchar i = 0;
	jogada_p j = NULL;

	assert(e != NULL);

	j = jogadas_possiveis(e);
	assert(j != NULL);

	/* imprimir o jogador */
	imprime_entidades(&e->jog, 1, IMG_JOGADOR);

	/* imprimir as jogadas */
	N = quantas_jogadas(j);
	for (i = 0; i < N; i++)
		imprime_jogada(j + i);
}

/**
 * @brief Numero de cores existentes.
 */
#define NUM_CORES	(1 << (3 * 8))

/**
 * @brief Calcula uma cor aleatoria.
 * @returns A cor.
 */
char * random_color (void)
{
	/*
	 * cada cor tem 3 bytes,
	 * logo existem 2 ^ (3 * 8)
	 * cores diferentes
	 */
	unsigned int rgb = rand() % NUM_CORES;

	/* "#rrggbb0" */
	static char ret[8] = "#";
	sprintf(ret+1, "%06x", rgb);
	ret[7] = '\0';

	return ret;
#undef NUM_CORES
}

/**
 * @brief Imprime o tabuleiro.
 * @param L A largura do tabuleiro.
 * @param C A altura do tabuleiro.
 */
void imprime_tabuleiro (abcissa L, ordenada C)
{
	size_t l = 0;
	size_t c = 0;
	for (l = 0; l < L; l++) {
		for (c = 0; c < C; c++)
			IMPRIME_CASA(l, c);
		putchar('\n');
	}
}

/**
 * @brief Imprime a porta.
 * @param e O estado actual.
 */
void imprime_porta (const estado_p e)
{
	assert(e != NULL);
	IMAGE(e->porta.x, e->porta.y, ESCALA, IMG_PORTA);
}

/**
 * @brief Imprime um link e um botao.
 * @param TXT O texto do botao.
 * @param I O indice do botao.
 * @param LINK O link.
 */
#define botao(TXT, I, LINK) \
	GAME_LINK(LINK); \
	BOTAO((BOTAO_X), (I) * (BOTAO_Y), (TXT), random_color()); \
	FECHA_A

/**
 * @brief Calcula o link da accao associada ao botao.
 */
#define link_reset accao2str(accao_new(e->nome, ACCAO_RESET, posicao_new(0, 0), posicao_new(0,0)))

/**
 * @brief Calcula o link da accao associada ao botao.
 * @param MT Tipo de movimento.
 */
#define link_mt(MT) \
		accao2str(accao_new(e->nome, ACCAO_CHANGE_MT, e->jog.pos, posicao_new(MT, 0)))

/**
 * @brief Imprime os botoes do jogo.
 * @param e O estado actual.
 */
void imprime_menu (const estado_p e)
{
	assert(e != NULL);

	COMMENT("RESET"); {
		botao("Reset", 1, link_reset);
	}

	if (!fim_de_jogo(e)) {
		COMMENT("MOVEMENT TYPE");

		enum mov_type mt = mov_type_next(e->mov_type);
		botao("Movement Type", 2, link_mt(mt));
	}
#undef link_mt
#undef link_reset
#undef botao
}

/**
 * @brief Imprime o fim de jogo.
 * @param e O estado actual.
 */
void game_over (const estado_p e)
{
	printf(
		"<TEXT Y=20 X=20 TEXT-ANCHOR=\"midle\" TEXT-ALIGN=\"center\""
		"FONT-FAMILY=\"serif\" FONT-WEIGHT=\"bold\">"
		"Game Over! Login as a new user or restart!\n O score do %s foi %hhu."
		"</TEXT>", e->nome,e->score
	      );
}

void imprime_jogo (const estado_p e)
{
	assert(e != NULL);

	ABRE_BODY(random_color()); {
		ABRE_SVG(SVG_WIDTH, SVG_HEIGHT); {
			if (fim_de_jogo(e)) {
				COMMENT("GAME OVER");
				game_over(e);
			} else {
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
			}

			COMMENT("menu");
			imprime_menu(e);

			printf(
				"<TEXT Y=160 X=460 TEXT-ANCHOR=\"midle\" TEXT-ALIGN=\"center\""
				"FONT-FAMILY=\"serif\" FONT-WEIGHT=\"bold\">"
				"vida: %hhu, score %hhu"
				"</TEXT>", e->jog.vida, e->score
			      );


			puts("<table><tr><th>ID</th><th>Posicao</th><th>Vida</th></tr>");

			for (size_t i = 0; i < e->num_inimigos; i++)
				printf(
					"<tr>"
					"<td>%lu</td>"
					"<td>(%hhu, %hhu)</td>"
					"<td>%hhu</td>"
					"</tr>\n",
					i,
					e->inimigo[i].pos.x,
					e->inimigo[i].pos.y,
					e->inimigo[i].vida
				      );

			puts("</table>");
		} FECHA_SVG;
	} FECHA_BODY;
}
