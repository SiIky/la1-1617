/** @file */
#ifndef _ENTIDADES_H
#define _ENTIDADES_H

typedef struct {
	posicao_s pos;
	uchar vida;
	uchar id;
} entidade, *entidades;

bool pos_inimigos (const entidades e, posicao_s p, size_t num_inimigos);
size_t pos_inimigos_ind (const entidades e, posicao_s p, size_t num_inimigos);
uchar entidade_remove (entidades e, size_t i, size_t N);
bool entidade_dead (const entidades e);

#endif /* _ENTIDADES_H */
