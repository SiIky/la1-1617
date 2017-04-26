#include "entidades.h"





size_t pos_inimigos_ind (const entidades e, posicao_s p, size_t num_inimigos ){
	size_t i;
	for (i = 0; i < num_inimigos && !(posicao_igual(e[i].pos, p)) ; i++);
	return i;
}

bool pos_inimigos (const entidades e, posicao_s p, size_t num_inimigos ){
	return pos_inimigos_ind(e,p,num_inimigos)<num_inimigos;

}