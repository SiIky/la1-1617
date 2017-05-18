#ifndef _JOGO_H
#define _JOGO_H

#include "posicao.h"
#include "estado.h"

#define NJOGADAS 8
#define quantas_jogadas(J) (*(((uchar *) (J)) - 1))

/*
 * 10 for player name
 * 8 for action type
 * 4 for player position (x/y)
 * 4 for target position (x/y)
 * 5 for comma (,)
 * 1 for '\0'
 */

#define JOGADA_LINK_MAX_BUFFER \
	((((sizeof(enum accao)) + (sizeof(posicao_s) << 1)) << 1) \
	 + 10 + 5 + 1)

#define BASE_PATH	"/var/www/html/files/"
enum accao {
	ACCAO_RESET,
	ACCAO_MOVE,
	ACCAO_CHANGE_MT,
	ACCAO_IGNORE,
	ACCAO_INVALID,
};

typedef struct {
	char nome[11];
	enum accao accao;
	posicao_s jog;
	posicao_s dest;
} accao_s;

typedef struct {
	posicao_s dest;
	char link[JOGADA_LINK_MAX_BUFFER];
} jogada_s, *jogada_p;

#define SCOREFILE_PATH	"/var/www/html/highscoresfile"
struct highscore {
	char nome[11];
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
