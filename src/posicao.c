#include "posicao.h"

int posicao_valida (int x, int y)
{
	return x >= 0 && y >= 0 && x < TAM && y < TAM;
}

int posicao_igual (posicao_s p, int x, int y)
{
	return p.x == x && p.y == y;
}

int posicao_ocupada (estado_p e, int x, int y)
{
	return tem_merdas(e->inimigo, e->num_inimigos, x, y)
		|| tem_merdas(e->obstaculo, e->num_obstaculos, x, y)
		|| tem_merdas(*e->jog, 1, x, y);
}
