#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "posicao.h"
#include "estado.h"
#include "html.h"

int main (void)
{
	estado_s e = ler_estado(getenv("QUERY_STRING"));

	CONTENT_TYPE;

	srand(time(NULL));

	ABRE_SVG(SVG_WIDTH, SVG_HEIGHT); {
		imprime_jogo(&e);
	} FECHA_SVG;

	return 0;
}
