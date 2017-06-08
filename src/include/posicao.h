/** @file */
#ifndef _POSICAO_H
#define _POSICAO_H

/**
 * @brief O tamanho do tabuleiro.
 */
#define TAM		10

/**
 * @brief Um char sem sinal.
 */
typedef unsigned char uchar;

/**
 * @brief Uma abcissa.
 */
typedef uchar abcissa;

/**
 * @brief Uma ordenada.
 */
typedef uchar ordenada;

/**
 * @brief Uma posicao.
 */
typedef struct {
	/** A abcissa da posicao. */
	abcissa x;
	/** A ordenada da posicao. */
	ordenada y;
} posicao_s;

/**
 * @brief Um apontador para uma posicao_s.
 */
typedef posicao_s * posicao_p;

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Verifica se duas posicoes sao iguais
 * @param p1 Uma posicao
 * @param p2 Uma posicao
 * @returns Verdadeiro caso as duas posicoes sejam iguais, falso caso contrario
 */
bool posicao_igual (posicao_s p1, posicao_s p2);

/**
 * @brief Verifica se uma posicao esta dentro do mapa
 * @param p A posicao a testar
 * @returns Verdadeiro caso a posicao esteja dentro do mapa, falso caso contrario
 */
bool posicao_valida (posicao_s p);

/**
 * @brief Cria uma nova posicao
 * @param x A abcissa da posicao
 * @param y A ordenada da posicao
 * @returns A nova posicao
 */
posicao_s posicao_new (abcissa x, ordenada y);

/**
 * @brief Filtra um array de posicoes.
 * @param p Array de posicoes a filtrar.
 * @param num Numero de elementos do array.
 * @param f Funcao a testar em cada posicao.
 * @returns Numero de posicoes que satisfazem o predicado.
 */
size_t pos_filter (posicao_p p, size_t num, bool (* f) (posicao_s));

/**
 * @brief Calcula posicao mais proxima dentro de um conjunto de posicoes.
 * @param ps Array de posicoes.
 * @param N Numero de elementos do array.
 * @param p Posicao do alvo.
 * @return Indice da posicao mais perto.
 */
size_t pos_mais_perto (const posicao_p ps, size_t N, posicao_s p);

#endif /* _POSICAO_H */
