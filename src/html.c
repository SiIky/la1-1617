#include "estado.h"
#include "jogo.c"

#include "html.h"

void imprime_entidades (posicao_p p, size_t max, char * img)
{
	if (p == NULL)
		return;
	for (size_t i = 0; i < max; i++) {
		COMMENT_ENTIDADE(i, p->x, p->y);
		IMAGE(p->x, p->y, ESCALA, img);
	}
}

void imprime_inimigos (estado_p e)
{
	if (e == NULL)
		return;
	imprime_entidades(e->inimigo, e->num_inimigos, IMG_INIMIGO);
}


void imprime_jogada (estado_p e, size_t x, size_t y)
{
	if (e == NULL || !posicao_valida(x, y) || posicao_ocupada(e, x, y))
			return;
	RECT_TRANSPARENTE(y, x, ESCALA);
}

void imprime_jogadas (estado_p e)
{
	if (e == NULL)
		return;
	imprime_entidades(&e->jog, 1, IMG_JOGADOR);

	size_t jx = e->jog.x;
	size_t jy = e->jog.y;

	size_t mx = e->jog.x + 1;
	size_t my = e->jog.y + 1;

	for (size_t x = jx - 1; x < mx; x++)
		for (size_t y = jy - 1; y < my; y++)
			imprime_jogada(e, x, y);
}

void imprime_obstaculos (estado_p e)
{
	if (e == NULL)
		return;
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
	for (size_t l = 0; l < TAM; l++)
		for (size_t c = 0; c < TAM; c++)
			imprime_casa(l, c);
}

void imprime_jogo (estado_p e)
{
	char * str = NULL;

	if (e == NULL || (str = estado2str(e)) == NULL)
		return;

	COMMENT("imprimir tabuleiro");
	imprime_tabuleiro();

	COMMENT("imprimir obstaculos");
	imprime_obstaculos(e);

	COMMENT("imprimir inimigos");
	imprime_inimigos(e);

	COMMENT("imprimir jogadas");
	imprime_jogadas(e);

	//printf("<A XLINK:HREF=http://localhost/cgi-bin/rogue?%s>", str); {
	//} printf("</A>");
}
