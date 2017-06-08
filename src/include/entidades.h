/** @file */
#ifndef _ENTIDADES_H
#define _ENTIDADES_H

/**
 * @brief O tipo entidade
 */
typedef struct {
	/** A posicao da entidade */
	posicao_s pos;
	/** A vida da entidade */
	uchar vida;
	/** O id da entidade */
	uchar id;
} entidade;

/**
 * @brief Um apontador para uma entidade.
 */
typedef entidade * entidades;

/**
 * @brief Verifica se existe alguma entidade com uma certa posicao
 * @param e As entidades
 * @param p A posicao a testar
 * @param num_inimigos O numero de entidades
 * @returns Verdadeiro se existe alguma entidade com aquela posicao
 */
bool pos_inimigos (const entidades e, posicao_s p, size_t num_inimigos);

/**
 * @brief Procura a primeira entidade com uma certa posicao
 * @param e As entidades
 * @param p A posicao a testar
 * @param num_inimigos O numero de entidades
 * @returns O indice da primeira entidade com a posicao, ou num_inimigos caso nao exista nenhuma
 */
size_t pos_inimigos_ind (const entidades e, posicao_s p, size_t num_inimigos);

/**
 * @brief Remove uma entidade de um array de entidades
 * @param e As entidades
 * @param i O indice da entidade a remover
 * @param N O numero de entidades
 * @returns O novo numero de entidades
 */
uchar entidade_remove (entidades e, size_t i, size_t N);

/**
 * @brief Verifica se uma entidade esta morta
 * @param e A entidade
 * @returns Verdadeiro se a entidade estiver morta, falso caso contrario
 */
bool entidade_dead (const entidades e);

#endif /* _ENTIDADES_H */
