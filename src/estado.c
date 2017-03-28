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

estado_s str2estado (char * args)
{
	estado_s e;
	char * p = (char *) &e;

	for (size_t i = 0; i < sizeof(estado_s); i++, args += 2) {
		unsigned int d;
		sscanf(args, "%2x", &d);
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

	// para funcionar pro jogador tb
	if (num != NULL)
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

void init_jogador (estado_p e)
{
	init_entidade(e, &(e->jog), NULL);
}

estado_s init_estado (void)
{
	estado_s ret;

	init_obstaculos(&ret);
	init_inimigos(&ret);
	init_jogador(&ret);

	return ret;
}

estado_s ler_estado (char * args)
{
	return (args == NULL) ?
		init_estado() :
		str2estado(args);
}
