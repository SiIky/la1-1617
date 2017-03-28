#include "posicao.h"
#include "jogo.h"

bool posicao_valida (abcissa x, ordenada y)
{
	/*
	 * Como `abcissa` e `ordenada` sao inteiros sem
	 * sinal, nao e preciso comparar com 0
	 */
	return x < TAM && y < TAM;
}

bool posicao_igual (posicao_s p, abcissa x, ordenada y)
{
	return p.x == x && p.y == y;
}

bool posicao_ocupada (estado_p e, abcissa x, ordenada y)
{
	return tem_merdas(e->inimigo, e->num_inimigos, x, y)
		|| tem_merdas(e->obstaculo, e->num_obstaculos, x, y)
		|| tem_merdas(&e->jog, 1, x, y);
}
