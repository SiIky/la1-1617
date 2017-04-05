EXEC=rogue
CFLAGS=-Wall -Wextra -Werror -O3 -pedantic -g -Iinclude/
FICHEIROS=estado.c html.c main.c Makefile posicao.c include/bool.h include/estado.h include/html.h include/posicao.h

all: object
	cc $(CFLAGS) *.o -o $(EXEC)

object: $(FICHEIROS)
	cc $(CFLAGS) -c estado.c
	cc $(CFLAGS) -c html.c
	cc $(CFLAGS) -c main.c
	cc $(CFLAGS) -c posicao.c

install: all
	sudo cp $(EXEC) /usr/lib/cgi-bin
	touch install

exemplo.zip: $(FICHEIROS)
	zip -9 exemplo.zip $(FICHEIROS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf *.o exemplo Doxyfile latex html install $(EXEC)
