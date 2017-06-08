/** @file */
/** @mainpage LA1-1617: Rogue-like
 * # qq coisa aqui
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fcntl.h>  /* `open()` */
#include <unistd.h> /* `access()` */

#include "check.h"
#include "posicao.h"
#include "estado.h"
#include "html.h"

/**
 * @brief Cria uma gamefile.
 * @param fname Nome do jogador/ficheiro.
 */
void create_gamefile (const char * fname)
{
	assert(fname != NULL);

	char * path = pathname(fname);
	assert(path != NULL);

	/* if file exists and we can RW, GTFO */
	ifjmp(access(path, F_OK | R_OK | W_OK) == 0, out);

	int fd = open(path, O_CREAT | O_RDWR, 0666);
	check(fd < 0, "could not create state file");

	fd = close(fd);
	check(fd < 0, "could not close state file");

	estado_s e = init_estado(0, 0, MOV_TYPE_QUANTOS, fname);
	escreve_estado(&e);

out:
	return;
}

/**
 * @brief Le o nome do jogador da `QUERY_STRING`
 * @param args A `QUERY_STRING`
 * @returns Uma string com o nome do jogador
 */
char * ler_nome (char * args)
{
	assert(args != NULL);
	static char ret[11] = "";
	int read = sscanf(args, "nome=%s", ret);
	return (read == 1) ?
		ret :
		NULL;
}

/**
 * @brief Imprime a pagina de login
 */
void login (void)
{
	puts(
		"<body>\n"
		"<form action=\"http://localhost/cgi-bin/rogue\" method=\"get\">\n"
		"Nome do utilizador: <input type=\"text\" name=\"nome\"><br>\n"
		"<input type=\"submit\" value=\"login\">\n"
		"</form>\n"
		"</body>"
	    );
}

void print_highscore (const struct highscore * hs)
{
	puts("<table><tr><th>Jogador</th><th>Score</th></tr>");

	for (size_t i = 0; i < 3; i++)
		printf(
			"<tr>"
			"<td>%s</td>"
			"<td>%hhu</td>"
			"</tr>\n",
			hs[i].nome,
			hs[i].score
		      );

	puts("</table>");
}

/**
 * @brief O entry point do programa
 * @returns Codigo de sucesso
 */
int main (void)
{
	srand(time(NULL));
	CONTENT_TYPE;

	char * qs = getenv("QUERY_STRING");

	if (qs == NULL || *qs == '\0')
		login();
	ifjmp(qs == NULL || *qs == '\0', ok);

	bool is_nome = strncmp("nome=", qs, 5) == 0;

	char * nome = (is_nome) ?
		ler_nome(qs) :
		NULL;

	if (is_nome)
		create_gamefile(nome);

	accao_s accao = (is_nome) ?
		accao_new(nome,
			  ACCAO_IGNORE,
			  posicao_new(0, 0),
			  posicao_new(0, 0)) :
		str2accao(qs);

	estado_s e = ler_estado(accao);
	escreve_estado(&e);

	if (fim_de_jogo(&e)) {
		struct highscore * hs = ler_highscore();
		update_highscore(&e, hs);
		escreve_highscore(hs);
		login();
		print_highscore(hs);
	}

	imprime_jogo(&e);

ok:
	return EXIT_SUCCESS;
}
