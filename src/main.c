#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "posicao.h"
#include "estado.h"
#include "html.h"

int main (void)
{
	estado_s e;

	srand(time(NULL));

	e = ler_estado(getenv("QUERY_STRING"));

	CONTENT_TYPE;

	imprime_jogo(&e);

	return 0;
}
