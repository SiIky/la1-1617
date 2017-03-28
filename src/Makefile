EXEC=rogue
CFLAGS=-Wall -Wextra -O3 -pedantic -g
FICHEIROS=bool.h estado.c estado.h html.c html.h inimigos.c jogo.c jogo.h main.c Makefile posicao.c posicao.h

all: object
	cc $(CFLAGS) *.o -o $(EXEC)

object: $(FICHEIROS)
	cc $(CFLAGS) -c estado.c
	cc $(CFLAGS) -c html.c
	cc $(CFLAGS) -c inimigos.c
	cc $(CFLAGS) -c jogo.c
	cc $(CFLAGS) -c main.c
	cc $(CFLAGS) -c posicao.c

install: all
	sudo cp exemplo /usr/lib/cgi-bin
	touch install

exemplo.zip: $(FICHEIROS)
	zip -9 exemplo.zip $(FICHEIROS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf *.o exemplo Doxyfile latex html install $(EXEC)
