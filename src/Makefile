EXEC=rogue
CFLAGS=-Wall -Wextra -Werror -O3 -pedantic -g -Iinclude/
IMAGENS=images/Char_14.png images/character_21.png images/lava_pool1.png images/tombstone.png
FICHEIROS=estado.c html.c main.c Makefile posicao.c include/bool.h include/estado.h include/html.h include/posicao.h
OBJS=estado.o html.o main.o posicao.o

all: object $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(EXEC)

object: $(FICHEIROS)
	cc $(CFLAGS) -c estado.c
	cc $(CFLAGS) -c html.c
	cc $(CFLAGS) -c main.c
	cc $(CFLAGS) -c posicao.c

install: all $(IMAGENS)
	sudo mkdir -p /var/www/html/images/
	sudo cp -f $(IMAGENS) -t /var/www/html/images/
	sudo cp $(EXEC) -t /usr/lib/cgi-bin
	touch install

entrega: $(FICHEIROS) $(IMAGENS)
	zip -n : -9 entrega.zip $(FICHEIROS) $(IMAGENS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf *.o entrega.zip Doxyfile latex html install $(EXEC)
