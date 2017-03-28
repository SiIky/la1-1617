#ifndef _HTML_H
#define _HTML_H

#define CONTENT_TYPE	(puts("Content-Type: text/html\n\n"))

#define SVG_WIDTH	600
#define SVG_HEIGHT	600

#include <stdio.h>

#define ABRE_SVG(X, Y)	(printf("<SVG WIDTH=%u HEIGHT=%u>\n", (X), (Y)))
#define FECHA_SVG	(puts("</SVG>\n"))

#endif /* _HTML_H */
