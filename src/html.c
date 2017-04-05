#include "estado.h"
#include "jogo.c"
#include "posicao.h"

#include "html.h"

void imprime_entidades (const posicao_p p, size_t max, char * img)
{
	if (p == NULL)
		return;
	for (size_t i = 0; i < max; i++)
		IMAGE(p[i].x, p[i].y, ESCALA, img);
}

void imprime_inimigos (const estado_p e)
{
	if (e != NULL)
		imprime_entidades(e->inimigo, e->num_inimigos, IMG_INIMIGO);
}

void imprime_jogada (const estado_p e, abcissa x, ordenada y)
{
	if (e == NULL || !posicao_valida(x, y) || posicao_ocupada(e, x, y))
		return;

	estado_s ne = move_jogador(*e, posicao_new(x, y));

	char * query = estado2str(&ne);
	if (query != NULL) {
		GAME_LINK(query);
		RECT_TRANSPARENTE(y, x, ESCALA);
		FECHA_A;
	}
}

void imprime_jogadas (const estado_p e)
{
	if (e == NULL)
		return;
	imprime_entidades(&e->jog, 1, IMG_JOGADOR);

	size_t jx = e->jog.x;
	size_t jy = e->jog.y;

	size_t mx = e->jog.x + 1;
	size_t my = e->jog.y + 1;

	for (size_t x = jx - 1; x <= mx; x++)
		for (size_t y = jy - 1; y <= my; y++)
			imprime_jogada(e, x, y);
}

void imprime_obstaculos (const estado_p e)
{
	if (e != NULL)
		imprime_entidades(e->obstaculo, e->num_obstaculos, IMG_OBSTACULO);
}

void imprime_casa (size_t l, size_t c)
{
	char * cores[] = { COR_PAR, COR_IMPAR };
	char * cor = cores[(l + c) % 2];
	RECT(l, c, ESCALA, cor);
}

void imprime_tabuleiro (void)
{
	for (size_t l = 0; l < TAM; l++) {
		for (size_t c = 0; c < TAM; c++)
			imprime_casa(l, c);
		putchar('\n');
	}
}

void imprime_porta (estado_s e)
{
	IMAGE(e.porta.x, e.porta.y, ESCALA, IMG_PORTA);

	if (fim_de_ronda(&e)) {
		e = init_estado();
		char * link = estado2str(&e);
		GAME_LINK(link);
		RECT_TRANSPARENTE(e.porta.x, e.porta.y, ESCALA);
		FECHA_A;
	}
}

void imprime_jogo (const estado_p e)
{
	char * link = NULL;

	if (e == NULL || (link = estado2str(e)) == NULL)
		return;

	imprime_tabuleiro();
	imprime_porta(*e);
	imprime_obstaculos(e);
	imprime_inimigos(e);
	imprime_jogadas(e);
}
