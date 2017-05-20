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

#define file_frw_ok(FNAME) (access(FNAME, F_OK | R_OK | W_OK) == 0)

void create_gamefile (const char * fname)
{
	assert(fname != NULL);

	char * path = pathname(fname);
	assert(path != NULL);

	/* if file exists and we can RW, GTFO */
	ifjmp(file_frw_ok(path), out);

	int fd = open(path, O_CREAT | O_RDWR);
	check(fd < 0, "could not create state file");

	fd = close(fd);
	check(fd < 0, "could not close state file");

	estado_s e = init_estado(0, 0, MOV_TYPE_QUANTOS, fname);
	escreve_estado(&e);

out:
	return;
}

char * ler_nome (char * args)
{
	assert(args != NULL);
	static char ret[11] = "";
	int read = sscanf(args, "nome=%s", ret);
	return (read == 1) ?
		ret :
		NULL;
}

void login (void)
{
	puts(
		"<body>\n"
		"<form action=\"http://localhost/cgi-bin/rogue\" method=\"get\">\n"
		"Merdas: <input type=\"text\" name=\"nome\"><br>\n"
		"<input type=\"submit\" value=\"login\">\n"
		"</form>\n"
		"</body>"
	    );
}

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
	}

	imprime_jogo(&e);

ok:
	return EXIT_SUCCESS;
}
