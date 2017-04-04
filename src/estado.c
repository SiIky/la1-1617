#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "estado.h"
#include "jogo.h"
#include "html.h"

char * estado2str (const estado_p e)
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

bool fim_de_ronda (const estado_p e)
{
	return e != NULL && e->num_inimigos == 0;
}

posicao_s nova_posicao_unica (const estado_p e)
{
	abcissa x;
	ordenada y;

	do {
		x = random() % TAM;
		y = random() % TAM;
	} while (posicao_ocupada(e, x, y));

	return posicao_new(x, y);
}

estado_s init_inimigos (estado_s e)
{
	for (size_t i = 0; i < MAX_INIMIGOS; i++) {
		e.inimigo[i] = nova_posicao_unica(&e);
		e.num_inimigos++;
	}
	return e;
}

estado_s init_obstaculos (estado_s e)
{
	for (size_t i = 0; i < MAX_OBSTACULOS; i++) {
		e.obstaculo[i] = nova_posicao_unica(&e);
		e.num_obstaculos++;
	}
	return e;
}

estado_s init_jogador (estado_s e)
{
	e.jog = nova_posicao_unica(&e);
	return e;
}

estado_s init_estado (void)
{
	estado_s ret;

	ret.porta = nova_posicao_unica(&ret);

	ret = init_obstaculos(ret);
	ret = init_inimigos(ret);
	ret = init_jogador(ret);

	return ret;
}

estado_s ler_estado (char * args)
{
	return (args == NULL || strlen(args) == 0) ?
		init_estado() :
		str2estado(args);
}

estado_s move_jogador (estado_s e, posicao_s p)
{
	e.jog = p;
	return e;
}
