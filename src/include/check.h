#ifndef _CHECK_H
#define _CHECK_H

#include <assert.h>

/* enable/disable assert */
#if 0
#define check(COND) assert(COND)
#else
#define check(COND) ((void)0)
#endif

#endif /* _CHECK_H */
