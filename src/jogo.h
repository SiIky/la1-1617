#ifndef _JOGO_H
#define _JOGO_H

#define TAM	10
#define ESCALA	40

#include <stdio.h>

#include "bool.h"
#include "estado.h"
#include "posicao.h"

bool tem_merdas (posicao_p p, size_t num, abcissa x, ordenada y);
bool posicao_ocupada (estado_p e, abcissa x, ordenada y);

#endif /* _JOGO_H */
