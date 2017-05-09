#ifndef _CHECK_H
#define _CHECK_H

#if 0
#define NDEBUG
#endif
#include <assert.h>

#include <stdlib.h>

#define check(COND, STR)            \
	if (COND) {                 \
		perror(STR);        \
		exit(EXIT_FAILURE); \
	}

#define ifjmp(COND, LBL)    if (COND) goto LBL
#define ifnnull(V, F)       if ((V) != NULL) F(V)
#define UNUSED(V)           ((void) (V))

#endif /* _CHECK_H */
