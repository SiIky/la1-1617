#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "estado.h"
#include "html.h"
#include "posicao.h"

int main (void)
{
	CONTENT_TYPE;

	srandom(time(NULL));

	COMMENT("ler estado");
	estado_s e = ler_estado(getenv("QUERY_STRING"));

	COMMENT("abrir SVG");
	ABRE_SVG(SVG_WIDTH, SVG_HEIGHT); {
		COMMENT("imprimir jogo");
		imprime_jogo(&e);
		COMMENT("fechar SVG");
	} FECHA_SVG;

	return 0;
}
