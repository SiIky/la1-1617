#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "estado.h"
#include "jogo.h"
#include "html.h"

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
		printf("<!-- x=%u\ty=%u -->\n", x, y);
	} while (posicao_ocupada(e, x, y));

	*p = posicao_new(x, y);
}

void init_entidades (estado_p e, posicao_p p, unsigned char * num, size_t max)
{
	if (e == NULL || p == NULL || num == NULL)
		return;
	for (*num = 0; *num < max; (*num)++) {
		printf("<!-- *num = %u -->\n", *num);
		init_entidade(e, p + *num);
	}
}

void init_inimigos (estado_p e)
{
	if (e != NULL)
		init_entidades(e, e->inimigo, &e->num_inimigos, MAX_INIMIGOS);
}

void init_obstaculos (estado_p e)
{
	if (e != NULL)
		init_entidades(e, e->obstaculo, &e->num_obstaculos, MAX_OBSTACULOS);
}

void init_jogador (estado_p e)
{
	if (e != NULL)
		init_entidade(e, &e->jog);
}

estado_s init_estado (void)
{
	estado_s ret;

	COMMENT("init obstaculos");
	init_obstaculos(&ret);
	COMMENT("init inimigos");
	init_inimigos(&ret);
	COMMENT("init jogador");
	init_jogador(&ret);

	return ret;
}

estado_s ler_estado (char * args)
{
	return (args == NULL || strlen(args) == 0) ?
		init_estado() :
		str2estado(args);
}
