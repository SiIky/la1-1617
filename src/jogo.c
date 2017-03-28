#include "jogo.h"
#include "bool.h"

bool tem_merdas (posicao_p p, size_t num, abcissa x, ordenada y)
{
	for (size_t i = 0; i < num; i++)
		if (posicao_igual(p[i], x, y))
			return 1;
	return 0;
}
