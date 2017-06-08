/** @file */
#ifndef _HTML_H
#define _HTML_H

/**
 * @brief A largura do quadro SVG
 */
#define SVG_WIDTH	630

/**
 * @brief A altura do quadro SVG
 */
#define SVG_HEIGHT	400

/**
 * @brief A largura/altura dos quadrados do tabuleiro.
 */
#define ESCALA		40UL

/**
 * @brief A pasta das imagens.
 */
#define IMAGE_PATH	"http://localhost/images/"

/**
 * @brief A imagem dos obstaculos.
 */
#define IMG_OBSTACULO	(IMAGE_PATH "lava_pool1.png")

/**
 * @brief A imagem dos inimigos.
 */
#define IMG_INIMIGO	(IMAGE_PATH "Char_14.png")

/**
 * @brief A imagem do jogador.
 */
#define IMG_JOGADOR	(IMAGE_PATH "character_21.png")

/**
 * @brief A imagem da porta.
 */
#define IMG_PORTA	(IMAGE_PATH "tombstone.png")

#include <stdio.h>

/**
 * @brief Imprime um comentario HTML.
 * @param S O texto do comentario.
 */
#define COMMENT(S)	(puts("\n<!-- " S " -->\n"))

/**
 * @brief Imprime o cabecalho da CGI.
 */
#define CONTENT_TYPE	(puts("Content-Type: text/html\n\n"))

/**
 * @brief Abre o quadro SVG.
 * @param X Largura do quadro.
 * @param Y Altura do quadro.
 */
#define ABRE_SVG(X, Y)	(printf("<SVG WIDTH=%u HEIGHT=%u>\n", (X), (Y)))

/**
 * @brief Fecha o quadro SVG.
 */
#define FECHA_SVG	(puts("</SVG>\n"))

/**
 * @brief Abre a tag HTML `<BODY>`.
 * @param C Cor do background.
 */
#define ABRE_BODY(C)	(printf("<BODY STYLE=\"background-color:%s\">\n", (C)))

/**
 * @brief Fecha o tag `<BODY>`.
 */
#define FECHA_BODY	(puts("</BODY>\n"))

/**
 * @brief Abre um tag HTML `<A>` com um link.
 * @param Q O link.
 */
#define GAME_LINK(Q)	(printf("<A XLINK:HREF=\"http://localhost/cgi-bin/rogue?%s\">\n", (Q)))

/**
 * @brief Fecha um tag HTML `<A>`.
 */
#define FECHA_A		(puts("</A>\n"))

/**
 * @brief Imprime um rectangulo SVG.
 * @param L Ordenada.
 * @param C Abcissa.
 * @param E Escala.
 * @param COR A cor.
 */
#define RECT(L, C, E, COR)		(printf("<RECT Y=%lu X=%lu WIDTH=%lu HEIGHT=%lu FILL=\"%s\"/>\n",\
			((L) * (E)),\
			((C) * (E)),\
			(E),\
			(E),\
			(COR)\
			))

/**
 * @brief Imprime uma imagem.
 * @param X Abcissa.
 * @param Y Ordenada.
 * @param E Escala.
 * @param I Imagem.
 */
#define IMAGE(X, Y, E, I)		(printf("<IMAGE X=%lu Y=%lu WIDTH=%lu HEIGHT=%lu XLINK:HREF=\"%s\"/>\n",\
			((X) * (E)),\
			((Y) * (E)),\
			(E),\
			(E),\
			(I)\
			))

/**
 * @brief Imprime um rectangulo SVG transparente.
 * @param L Ordenada.
 * @param C Abcissa.
 * @param E Escala.
 */
#define RECT_TRANSPARENTE(L, C, E)	(printf("<RECT Y=%lu X=%lu WIDTH=%lu HEIGHT=%lu STYLE=\"fill-opacity:0\"/>\n",\
			((L) * (E)),\
			((C) * (E)),\
			(E),\
			(E)\
			))

/**
 * @brief Imprime uma casa do tabuleiro.
 * @param L Ordenada.
 * @param C Abcissa.
 */
#define IMPRIME_CASA(L, C)		RECT((L), (C), ESCALA, random_color())

/**
 * @brief Abcissa dos botoes do menu do jogo.
 */
#define BOTAO_X 440

/**
 * @brief Ordenada inicial dos botoes do menu do jogo.
 */
#define BOTAO_Y 40

/**
 * @brief Margem do texto dos botoes.
 */
#define TEXT_OFFSET 25

/**
 * @brief Imprime um botao.
 * @param X Abcissa.
 * @param Y Ordenada.
 * @param TXT Texto.
 * @param COR Cor.
 */
#define BOTAO(X, Y, TXT, COR) \
	(printf("<RECT Y=%u X=%u WIDTH=400 HEIGHT=40 FILL=\"%s\"/>" \
		"<TEXT Y=%u X=%u TEXT-ANCHOR=\"midle\" TEXT-ALIGN=\"center\"" \
		"FONT-FAMILY=\"serif\" FONT-WEIGHT=\"bold\">%s</TEXT>", \
		(Y), \
		(X), \
		(COR), \
		(Y) + (TEXT_OFFSET), \
		(X) + (TEXT_OFFSET), \
		(TXT)))
#include "jogo.h"

/**
 * @brief Imprime o jogo.
 * @param e O estado a imprimir.
 */
void imprime_jogo (const estado_p e);

#endif /* _HTML_H */
