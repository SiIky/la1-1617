#ifndef _ENTIDADES_H
#define _ENTIDADES_H


typedef struct {
	posicao_s pos;
	int vida;
} entidade, *entidades;


bool pos_inimigos (const entidades e, posicao_s p, size_t num_inimigos );
size_t pos_inimigos_ind (const entidades e, posicao_s p, size_t num_inimigos );

#endif /* _ENTIDADES_H */

