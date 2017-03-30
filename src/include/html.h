#ifndef _HTML_H
#define _HTML_H

#define SVG_WIDTH	600
#define SVG_HEIGHT	600
#define ESCALA		40UL
#define COR_PAR		"#00ff00"
#define COR_IMPAR	"#ff0000"

#include <stdio.h>

#define CONTENT_TYPE	(puts("Content-Type: text/html\n\n"))
#define ABRE_SVG(X, Y)	(printf("<SVG WIDTH=%u HEIGHT=%u>\n", (X), (Y)))
#define FECHA_SVG	(puts("\n</SVG>\n"))

#define QUADRADO(L, C, E, COR)	(printf("<RECT Y=%lu X=%lu WIDTH=%lu HEIGHT=%lu FILL=\"%s\"/>\n",\
			((L) * (E)),\
			((C) * (E)),\
			(E),\
			(E),\
			(COR)\
			))

void imprime_jogo (estado_p e);
void imprime_tabuleiro (void);
void imprime_casa (size_t l, size_t c);

#endif /* _HTML_H */
