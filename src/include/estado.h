/** @file */
#ifndef _ESTADO_H
#define _ESTADO_H

#include <stdio.h>

#include "posicao.h"
#include "entidades.h"

/**
 * @brief O numero minimo de inimigos
 */
#define MIN_INIMIGOS	(TAM)

/**
 * @brief O numero minimo de obstaculos
 */
#define MIN_OBSTACULOS	(MIN_INIMIGOS << 1)

/**
 * @brief O numero maximo de obstaculos
 */
#define MAX_OBSTACULOS	((TAM * TAM) >> 1)

/**
 * @brief O numero maximo de inimigos
 */
#define MAX_INIMIGOS	(MAX_OBSTACULOS >> 1)

/**
 * @brief O tipo de movimento
 */
enum mov_type {
	MOV_TYPE_XADREZ_REI,
	MOV_TYPE_XADREZ_CAVALO,
	MOV_TYPE_QUANTOS,
};

/**
 * @brief O estado do jogo
 */
typedef struct {
	/** O nome do jogador */
	char nome[11];
	/** O nivel actual */
	uchar nivel;
	/** O numero de inimigos vivos */
	uchar num_inimigos;
	/** O numero de obstaculos */
	uchar num_obstaculos;
	/** O score actual */
	uchar score;
	/** Flag que indica se o ultimo ataque do jogador matou */
	bool matou;
	/** O tipo de movimento actual */
	enum mov_type mov_type;
	/** O jogador */
	entidade jog;
	/** A porta de saida do nivel */
	posicao_s porta;
	/** Os inimigos */
	entidade inimigo[MAX_INIMIGOS];
	/** Os obstaculos */
	entidade obstaculo[MAX_OBSTACULOS];
} estado_s, *estado_p;

/**
 * @brief Verifica se o jogo chegou ao fim
 * @param e O estado do jogo
 * @returns Verdadeiro se o jogo tiver acabado, falso caso contrario
 */
bool fim_de_jogo (const estado_p e);

/**
 * @brief Verifica se a ronda chegou ao fim
 * @param e O estado do jogo
 * @returns Verdadeiro se a ronda tiver acabado, falso caso contrario
 */
bool fim_de_ronda (const estado_p e);

/**
 * @brief Inicializa o estado do jogo
 * @param nivel O ultimo nivel completado
 * @param score Score obtido ate agora
 * @param mt O tipo de movimento actual
 * @param nome O nome do jogador
 * @returns O estado inicializado
 */
estado_s init_estado (uchar nivel, uchar score, enum mov_type mt, const char * nome);

/**
 * @brief Move o jogador pra uma posicao
 * @param e O estado do jogo
 * @param p A posicao pra onde o jogador vai ser movido
 * @returns O novo estado
 */
estado_s move_jogador (estado_s e, posicao_s p);

/**
 * @brief Ataca um inimigo
 * @param ret O estado do jogo
 * @param I O indice do inimigo a atacar
 * @returns O novo estado
 */
estado_s ataca_inimigo (estado_s ret, uchar I);

/**
 * @brief Ataca o jogador
 * @param e O estado do jogo
 * @param I Indice do inimigo que atacou
 * @returns O novo estado
 */
estado_s ataca_jogador (const estado_p e, uchar I);

/**
 * @brief Verifica se uma posicao contem algum inimigo
 * @param e O estado do jogo
 * @param p A posicao a testar
 * @returns Verdadeiro se a posicao nao tiver nenhum inimigo, falso caso contrario
 */
bool nao_tem_inimigos (const estado_p e, const posicao_p p);

#endif /* _ESTADO_H */
