#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "estado.h"
#include "jogo.h"

char * estado2str (estado_p e)
{
	if (e == NULL)
		return NULL;
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

void init_entidade (estado_p e, posicao_p p)
{
	if (e == NULL || p == NULL)
		return;
	abcissa x;
	ordenada y;

	do {
		x = random() % TAM;
		y = random() % TAM;
	} while (posicao_ocupada(e, x, y));

	p->x = x;
	p->y = y;
}

void init_entidades (estado_p e, posicao_p p, unsigned char * num, size_t max)
{
	if (e == NULL || p == NULL || num == NULL)
		return;
	for (*num = 0; *num < max; (*num)++)
		init_entidade(e, p + (*num));
}

void init_inimigos (estado_p e)
{
	if (e != NULL)
		init_entidades(e, e->inimigo, &(e->num_inimigos), MAX_INIMIGOS);
}

void init_obstaculos (estado_p e)
{
	if (e != NULL)
		init_entidades(e, e->obstaculo, &(e->num_obstaculos), MAX_OBSTACULOS);
}

void init_jogador (estado_p e)
{
	if (e != NULL)
		init_entidade(e, &(e->jog));
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
	return (args == NULL || strlen(args) == 0) ?
		init_estado() :
		str2estado(args);
}
