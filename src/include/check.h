/** @file */
#ifndef _CHECK_H
#define _CHECK_H

#if 0
#define NDEBUG
#endif
#include <assert.h>

#include <stdlib.h>

/**
 * @brief Testa `COND` e, caso seja verdadeira, imprime uma mensagem de erro e `exit()`
 * @param COND A condicao a testar
 * @param STR A mensagem de erro
 */
#define check(COND, STR)            \
	if (COND) {                 \
		perror(STR);        \
		exit(EXIT_FAILURE); \
	}

/**
 * @brief Salta para `LBL` caso `COND` seja verdadeira
 * @param COND Condicao a testar
 * @param LBL Label para onde salta
 */
#define ifjmp(COND, LBL)    if (COND) goto LBL

/**
 * @brief Se `V` nao for `NULL` chama a funcao `F` com argumento `V`
 * @param V Valor a testar
 * @param F Funcao a chamar
 */
#define ifnnull(V, F)       if ((V) != NULL) F(V)

/**
 * @brief Marca uma variavel como nao usada
 * @param V Variavel a marcar como nao usada
 */
#define UNUSED(V)           ((void) (V))

#endif /* _CHECK_H */
