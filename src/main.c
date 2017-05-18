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
	check(fd < 0, "could not create file");

	fd = close(fd);
	check(fd < 0, "could not close file");

	estado_s e = init_estado(0, 0, fname);
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
	char * nome = (qs != NULL) ?
		ler_nome(qs) :
		NULL;

	if (qs == NULL || *qs == '\0')
		login();
	ifjmp(qs == NULL || *qs == '\0', ok);

	if (strncmp("nome=", qs, 5) == 0)
		create_gamefile(nome);

	accao_s accao = (strncmp("nome=", qs, 5) == 0) ?
		accao_new(nome,
			  ACCAO_IGNORE,
			  posicao_new(0, 0),
			  posicao_new(0, 0)) :
		str2accao(qs);

	estado_s e = ler_estado(accao);
	imprime_jogo(&e);
	escreve_estado(&e);

ok:
	return EXIT_SUCCESS;
}
