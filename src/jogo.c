#include "bool.h"
#include "estado.h"
#include "posicao.h"

#include "jogo.h"

bool posicao_ocupada (estado_p e, abcissa x, ordenada y)
{
	return (e != NULL)
		&& (tem_merdas(e->inimigo, e->num_inimigos, x, y)
		|| tem_merdas(e->obstaculo, e->num_obstaculos, x, y)
		|| posicao_igual(e->jog, x, y));
}
