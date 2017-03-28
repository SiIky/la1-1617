#ifndef _POSICAO_H
#define _POSICAO_H
typedef struct {
	unsigned char x, y;
} posicao_s, *posicao_p;

int posicao_ocupada (estado_p e, int x, int y);
int posicao_igual (posicao_s p, int x, int y);
int posicao_valida (int x, int y);
#endif /* _POSICAO_H */
