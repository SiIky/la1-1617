/** @file */
#include "check.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estado.h"
#include "entidades.h"

/**
 * @brief Testa se uma posicao contem algum inimigo, obstaculo ou o jogador
 * @param e O estado do jogo
 * @param p A posicao a testar
 * @returns Falso se estiver vazia, verdadeiro caso contrario
 */
bool posicao_ocupada (const estado_p e, posicao_s p)
{
	assert(e != NULL);
	return (pos_inimigos(e->inimigo, p,  e->num_inimigos)
		|| pos_inimigos(e->obstaculo, p,  e->num_obstaculos)
		|| posicao_igual(e->jog.pos, p));
}

/**
 * @brief Cria uma posicao aleatoria nao ocupada
 * @param e O estado do jogo
 * @returns A nova posicao unica
 */
posicao_s nova_posicao_unica (const estado_p e)
{
	assert(e != NULL);
	posicao_s ret = { (~0), (~0) };

	do {
		ret.x = rand() % TAM;
		ret.y = rand() % TAM;
	} while (posicao_ocupada(e, ret));

	return ret;
}

bool fim_de_jogo (const estado_p e)
{
	assert(e != NULL);
	return e->jog.vida == 0;
}

bool fim_de_ronda (const estado_p e)
{
	assert(e != NULL);
	return e->num_inimigos == 0;
}

/**
 * @brief Inicializa um array de entidades
 * @param e O estado do jogo
 * @param p Um array de entidades
 * @param N O comprimento do array
 * @param num O numero de entidades que foram inicializadas
 * @param vida Vida a dar as entidades
 */
void init_entidades (estado_p e, entidades p, uchar N, uchar * num, uchar vida)
{
	assert(e != NULL);
	assert(p != NULL);
	assert(num != NULL);
	assert(vida > 0);

	for ((*num) = 0; (*num) < N; (*num)++) {
		p[(*num)].pos = nova_posicao_unica(e);
		p[(*num)].vida = vida;
		p[(*num)].id = *num;
	}
}

/**
 * @brief Calcula o minimo entre dois numeros
 * @param A Um numero
 * @param B Um numero
 * @returns O minimo entre A e B
 */
#define min(A, B)	((A) < (B)) ? (A) : (B)
/**
 * @brief Inicializa os inimigos
 * @param e O estado do jogo
 * @returns O novo estado
 */
estado_s init_inimigos (estado_s e)
{
	uchar N = min(MIN_INIMIGOS + e.nivel, MAX_INIMIGOS);
	init_entidades(&e, e.inimigo, N, &e.num_inimigos, 1);
	return e;
}

/**
 * @brief Inicializa os obstaculos
 * @param e O estado do jogo
 * @returns O novo estado
 */
estado_s init_obstaculos (estado_s e)
{
	uchar N = min(MIN_OBSTACULOS + e.nivel, MAX_OBSTACULOS);
	init_entidades(&e, e.obstaculo, N, &e.num_obstaculos, 1);
	return e;
}
#undef min

/**
 * @brief Inicializa o jogador
 * @param e O estado do jogo
 * @returns O novo estado
 */
estado_s init_jogador (estado_s e)
{
	e.jog.pos = nova_posicao_unica(&e);
	e.jog.vida = 20 + e.nivel;
	return e;
}

/**
 * @brief Inicializa a porta
 * @param e O estado do jogo
 * @returns O novo estado
 */
estado_s init_porta (estado_s e)
{
	e.porta = nova_posicao_unica(&e);
	return e;
}

estado_s init_estado (uchar nivel, uchar score, enum mov_type mt, const char * nome)
{
	assert(nome != NULL);

	estado_s ret = {0};

	strcpy(ret.nome, nome);

	ret.nivel = nivel + 1;
	ret.score = score;
	ret.matou = false;
	ret.mov_type = (mt >= MOV_TYPE_QUANTOS) ?
		(random() % MOV_TYPE_QUANTOS) :
		mt;

	ret = init_jogador(ret);
	ret = init_obstaculos(ret);
	ret = init_porta(ret);
	ret = init_inimigos(ret);

	return ret;
}

estado_s move_jogador (estado_s e, posicao_s p)
{
	e.jog.pos = p;
	/* nao perde vida no fim de uma ronda */
	if (!fim_de_ronda(&e) && !e.matou)
		e.jog.vida--;
	e.matou = false;
	return e;
}

bool nao_tem_inimigos (const estado_p e, const posicao_p p)
{
	assert(e != NULL);
	assert(p != NULL);
	return !pos_inimigos(e->inimigo, *p, e->num_inimigos);
}

estado_s ataca_inimigo (estado_s ret, uchar I)
{
	assert(ret.inimigo[I].vida > 0);

	ret.inimigo[I].vida--;

	ifjmp(!entidade_dead(ret.inimigo + I), out);

	ret.num_inimigos = entidade_remove(ret.inimigo, I, ret.num_inimigos);
	ret.matou = true;
	ret.score++;

out:
	return ret;
}

estado_s ataca_jogador (const estado_p e, uchar I)
{
	assert(e != NULL);

	estado_s ne = *e;

	ifjmp(fim_de_jogo(&ne), out);

	ne.jog.vida--;
	ne.inimigo[I].vida++;

out:
	return ne;
}
