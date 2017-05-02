#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "posicao.h"
#include "estado.h"
#include "html.h"

int main (void)
{
	srand(time(NULL));

	estado_s e = ler_estado(getenv("QUERY_STRING"));

	CONTENT_TYPE;

	imprime_jogo(&e);

	escreve_estado(&e);

	return 0;
}
