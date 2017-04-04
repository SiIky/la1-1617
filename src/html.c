#include "estado.h"
#include "jogo.c"
#include "posicao.h"

#include "html.h"

void imprime_entidades (const posicao_p p, size_t max, char * img)
{
	if (p == NULL)
		return;
	for (size_t i = 0; i < max; i++) {
		COMMENT_ENTIDADE(i, p[i].x, p[i].y);
		IMAGE(p[i].x, p[i].y, ESCALA, img);
	}
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
	estado_s ne = *e;
	ne = move_jogador(ne, posicao_new(x, y));
	char * query = estado2str(&ne);
	GAME_LINK(query);
	RECT_TRANSPARENTE(y, x, ESCALA);
	FECHA_A;
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

void imprime_porta (const estado_p e)
{
	if (e == NULL)
		return;
	bool fim = fim_de_ronda(e);
}

void imprime_jogo (const estado_p e)
{
	if (e == NULL)
		return;
	char * link = estado2str(e);

	if (link == NULL)
		return;

	COMMENT("imprimir tabuleiro");
	imprime_tabuleiro();

	imprime_porta();

	COMMENT("imprimir obstaculos");
	imprime_obstaculos(e);

	COMMENT("imprimir inimigos");
	imprime_inimigos(e);

	COMMENT("imprimir jogadas");
	imprime_jogadas(e);

	//printf("<A XLINK:HREF=http://localhost/cgi-bin/rogue?%s>", str); {
	//} printf("</A>");
}
