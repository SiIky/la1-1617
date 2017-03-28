#include "jogo.h"

int tem_merdas (posicao_p *p, int num, int x, int y)
{
	for (int i = 0; i < num; i++)
		if (posicao_igual(p, x, y))
			return 1;
	return 0;
}
