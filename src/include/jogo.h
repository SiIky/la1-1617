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
} jogada_s;

/**
 * @brief Um apontador para uma jogada_s.
 */
typedef jogada_s * jogada_p;

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

/**
 * @brief Calcula todas as jogadas possiveis do jogador.
 * @param e O estado actual.
 * @returns Uma lista de jogadas.
 */
jogada_p jogadas_possiveis (const estado_p e);

/**
 * @brief Le o estado a partir do ficheiro.
 * @param accao A accao a executar.
 * @returns O estado lido.
 */
estado_s ler_estado (accao_s accao);

/**
 * @brief Escreve o estado de jogo no ficheiro.
 * @param e O estado a guardar.
 */
void escreve_estado (const estado_p e);

/**
 * @brief Calcula o caminho de um ficheiro de jogo.
 * @param name Nome do jogador.
 * @returns O caminho do ficheiro.
 */
char * pathname (const char * name);

/**
 * @brief Cria uma nova accao.
 * @param nome Nome do jogador.
 * @param accao Tipo de accao.
 * @param jog posicao do jogador.
 * @param dest posicao do destino.
 * @returns A nova accao.
 */
accao_s accao_new (const char * nome, enum accao accao, posicao_s jog, posicao_s dest);

/**
 * @brief Gera um Link.
 * @param accao A accao.
 * @returns O link.
 */
char * accao2str (accao_s accao);

/**
 * @brief Le um link.
 * @param str O link.
 * @returns A nova accao.
 */
accao_s str2accao (const char * str);

/**
 * @brief Calcula o tipo de movimento seguinte.
 * @param ret Tipo de movimento actual.
 * @returns O novo tipo de movimento.
 */
enum mov_type mov_type_next (enum mov_type ret);

/**
 * @brief Le os highscores a partir do ficheiro.
 * @returns O array de highscores.
 */
struct highscore * ler_highscore (void);

/**
 * @brief Escreve os highscores no ficheiro
 * @param hs O array de highscores.
 */
void escreve_highscore (struct highscore hs[3]);

/**
 * @brief Actualiza o array de highscores com o score do jogador actual.
 * @param e O estado actual.
 * @param hs O array de highscores.
 */
void update_highscore (const estado_p e, struct highscore hs[3]);

#endif /* _JOGO_H */
