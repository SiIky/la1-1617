#include <stdio.h>

#include "chtml.h"

void indent (unsigned int n)
{
    for (unsigned int I = 0; I < n; I++)
        putchar(' ');
}
