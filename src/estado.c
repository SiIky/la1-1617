#include <stdio.h>
#include <stdlib.h>

#include "estado.h"
#include "jogo.h"

char *estado2str (estado_p e)
{
	static char buffer[MAX_BUFFER];
	char *p = (char *) e;
	buffer[0] = '\0';

	for (size_t i = 0; i < sizeof(estado_s); i++)
		sprintf(buffer, "%s%02x", buffer, p[i]);
	return buffer;
}

estado_s str2estado (char *argumentos)
{
	estado_s e;
	char * p = (char *) &e;

	for (size_t i = 0; i < sizeof(estado_s); i++, argumentos += 2) {
		unsigned int d;
		sscanf(argumentos, "%2x", &d);
		p[i] = (char) d;
	}

	return e;
}

void init_entidade (estado_p e, posicao_p p, unsigned char * num)
{
	abcissa x;
	ordenada y;

	do {
		x = random() % TAM;
		y = random() % TAM;
	} while (posicao_ocupada(e, x, y));

	p->x = x;
	p->y = y;
	(*num)++;
}

void init_inimigos (estado_p e)
{
	for (size_t i = 0; i < MAX_INIMIGOS; i++)
		init_entidade(e, (e->inimigo + i), &(e->num_inimigos));
}

void init_obstaculos (estado_p e)
{
	for (size_t i = 0; i < MAX_OBSTACULOS; i++)
		init_entidade(e, (e->obstaculo + i), &(e->num_obstaculos));
}
