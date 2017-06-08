/** @file */
#ifndef _JOGO_H
#define _JOGO_H

#include "posicao.h"
#include "estado.h"

/**
 * @brief Numero maximo de jogadas possiveis.
 */
#define NJOGADAS 8

/**
 * @brief Calcula o numero de jogadas de um array de jogadas ou posicoes.
 * @param J Array de jogadas ou posicoes.
 * @returns Numero de jogadas de um array de jogadas ou posicoes.
 */
#define quantas_jogadas(J) (*(((uchar *) (J)) - 1))

/*
 * 10 for player name
 * 8 for action type
 * 4 for player position (x/y)
 * 4 for target position (x/y)
 * 5 for comma (,)
 * 1 for '\0'
 */

/**
 * @brief Tamanho maximo do link de uma jogada.
 */
#define JOGADA_LINK_MAX_BUFFER \
	((((sizeof(enum accao)) + (sizeof(posicao_s) << 1)) << 1) \
	 + 10 + 5 + 1)

/**
 * @brief Pasta para guardar os ficheiros de estado dos jogadores.
 */
#define BASE_PATH	"/var/www/html/files/"

/**
 * @brief Tipo de accao.
 */
enum accao {
	/** Comecar um jogo novo. */
	ACCAO_RESET,
	/** Mover o jogador. */
	ACCAO_MOVE,
	/** Mudar o tipo de movimento. */
	ACCAO_CHANGE_MT,
	/** Ignorar accao. */
	ACCAO_IGNORE,
	/** Accao invalida. */
	ACCAO_INVALID,
};

/**
 * @brief Accao.
 */
typedef struct {
	/** Nome do jogador. */
	char nome[11];
	/** O tipo da accao. */
	enum accao accao;
	/** A posicao do jogador antes de executar a accao. */
	posicao_s jog;
	/** A posicao de destino da accao. */
	posicao_s dest;
} accao_s;

/**
 * @brief O tipo de jogada.
 */
typedef struct {
	/** A posicao de destino da accao. */
	posicao_s dest;
	/** O link com a accao. */
	char link[JOGADA_LINK_MAX_BUFFER];
} jogada_s, *jogada_p;

/**
 * @brief Ficheiro de highscore.
 */
#define SCOREFILE_PATH	"/var/www/html/highscoresfile"

/**
 * @brief Tipo de highscore.
 */
struct highscore {
	/** Nome do jogador. */
	char nome[11];
	/** Score. */
	uchar score;
};

jogada_p jogadas_possiveis (const estado_p e);
estado_s ler_estado (accao_s accao);
void escreve_estado (const estado_p e);
char * pathname (const char * name);

accao_s accao_new (const char * nome, enum accao accao, posicao_s jog, posicao_s dest);
char * accao2str (accao_s accao);
accao_s str2accao (const char * str);
enum mov_type mov_type_next (enum mov_type ret);

struct highscore * ler_highscore (void);
void escreve_highscore (struct highscore hs[3]);
void update_highscore (const estado_p e, struct highscore hs[3]);

#endif /* _JOGO_H */
