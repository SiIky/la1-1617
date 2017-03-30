#ifndef _HTML_H
#define _HTML_H

#define SVG_WIDTH	600
#define SVG_HEIGHT	600
#define ESCALA		40UL
#define COR_PAR		"#00ff00"
#define COR_IMPAR	"#ff0000"

#define IMAGE_PATH	"http://localhost/images/"
#define IMG_OBSTACULO	(IMAGE_PATH "lava_pool1.png")
#define IMG_INIMIGO	(IMAGE_PATH "DwellerN_03.png")
#define IMG_JOGADOR	(IMAGE_PATH "Driders_04.png")

#include <stdio.h>

#define CONTENT_TYPE	(puts("Content-Type: text/html\n\n"))
#define ABRE_SVG(X, Y)	(printf("<SVG WIDTH=%u HEIGHT=%u>\n", (X), (Y)))
#define FECHA_SVG	(puts("\n</SVG>\n"))

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

void imprime_casa (size_t l, size_t c);
void imprime_jogo (estado_p e);
void imprime_obstaculos (estado_p e);
void imprime_tabuleiro (void);

#endif /* _HTML_H */
