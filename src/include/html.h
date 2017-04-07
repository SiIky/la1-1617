#ifndef _HTML_H
#define _HTML_H

#define SVG_WIDTH	600
#define SVG_HEIGHT	600
#define ESCALA		40UL
#define COR_PAR		"#00ff00"
#define COR_IMPAR	"#ff0000"

#define IMAGE_PATH	"http://localhost/images/"
#define IMG_OBSTACULO	(IMAGE_PATH "lava_pool1.png")
#define IMG_INIMIGO	(IMAGE_PATH "Char_14.png")
#define IMG_JOGADOR	(IMAGE_PATH "character_21.png")
#define IMG_PORTA	(IMAGE_PATH "tombstone.png")

#include <stdio.h>

#define COMMENT(S)	(puts("\n<!-- " S " -->\n"))
#define CONTENT_TYPE	(puts("Content-Type: text/html\n\n"))
#define ABRE_SVG(X, Y)	(printf("<SVG WIDTH=%u HEIGHT=%u>\n", (X), (Y)))
#define FECHA_SVG	(puts("</SVG>\n"))

#define GAME_LINK(Q)	(printf("<A XLINK:HREF=\"http://localhost/cgi-bin/rogue?%s\">\n", (Q)))
#define FECHA_A		(puts("</A>\n"))

#define RECT(L, C, E, COR)		(printf("<RECT Y=%lu X=%lu WIDTH=%lu HEIGHT=%lu FILL=\"%s\"/>\n",\
			((L) * (E)),\
			((C) * (E)),\
			(E),\
			(E),\
			(COR)\
			))

#define IMAGE(X, Y, E, I)		(printf("<IMAGE X=%lu Y=%lu WIDTH=%lu HEIGHT=%lu XLINK:HREF=\"%s\"/>\n",\
			((X) * (E)),\
			((Y) * (E)),\
			(E),\
			(E),\
			(I)\
			))

#define RECT_TRANSPARENTE(L, C, E)		(printf("<RECT Y=%lu X=%lu WIDTH=%lu HEIGHT=%lu STYLE=\"fill-opacity:0\"/>\n",\
			((L) * (E)),\
			((C) * (E)),\
			(E),\
			(E)\
			))

void imprime_entidades (const posicao_p p, size_t max, char * img);
void imprime_inimigos (const estado_p e);
void imprime_jogada (const estado_p e, posicao_s p);
void imprime_jogadas (const estado_p e);
void imprime_obstaculos (const estado_p e);
void imprime_casa (size_t l, size_t c);
void imprime_tabuleiro (abcissa L, ordenada C);
void imprime_jogo (const estado_p e);
void imprime_porta (estado_s e);

#endif /* _HTML_H */
