#include <stdio.h>

#include "estado.h"

char *estado2str (estado_p e)
{
	static char buffer[MAX_BUFFER];
	char *p = (char *) e;
	int i;
	buffer[0] = '\0';
	for (i = 0; i < sizeof(estado_s); i++)
		sprintf(buffer, "%s%02x", buffer, p[i]);
	return buffer;
}

estado_s str2estado (char *argumentos)
{
	estado_s e;
	char *p = (char *) e;
	int i;

	for (i = 0; i < sizeof(estado_s); i++, argumentos += 2) {
		int d;
		sscanf(argumentos, "%2x", &d);
		p[i] = (char) d;
	}
	return e;
}
