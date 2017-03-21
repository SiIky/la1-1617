#ifndef _CHTML_H
# define _CHTML_H 1

void indent (unsigned int n);

# ifndef INDENT_VAR
#  define INDENT_VAR    chtml_indent
# endif /* INDENT_VAR */

# ifdef INDENT_VAR
#  define INDENT(...)   { indent(INDENT_VAR); __VA_ARGS__; }

/* HTML comments template (for debugging) */
#  define COMMENT(...) \
{ \
    indent(INDENT_VAR); \
    puts("<!--"); \
    { \
        __VA_ARGS__ \
    } \
    indent(INDENT_VAR); \
    puts("-->"); \
}

/* Default tag template */
#  define TAG(T, ...) \
{ \
    indent(INDENT_VAR); \
    puts("<" T ">"); \
    { \
        INDENT_VAR++; \
        __VA_ARGS__ \
        INDENT_VAR--; \
    } \
    indent(INDENT_VAR); \
    puts("</" T ">"); \
}

/* Common HTML tags */
#  define HTML(...)     TAG("HTML", __VA_ARGS__)
#   define HEAD(...)    TAG("HEAD", __VA_ARGS__)
#   define BODY(...)    TAG("BODY", __VA_ARGS__)
#    define P(...)      TAG("P", __VA_ARGS__)
#    define DIV(...)    TAG("DIV", __VA_ARGS__)
# endif /* INDENT_VAR */

#endif /* _CHTML_H */
