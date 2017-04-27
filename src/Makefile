EXEC=rogue
FLAGS=-ansi -static -Wall -Wextra -Werror -pedantic -Iinclude/
DFLAGS=$(FLAGS) -g
CFLAGS=$(FLAGS) -O3
IMAGENS=images/Char_14.png images/character_21.png images/lava_pool1.png images/tombstone.png
FICHEIROS=entidades.c estado.c html.c include/entidades.h include/estado.h include/html.h include/posicao.h main.c posicao.c
OBJS=entidades.o estado.o html.o main.o posicao.o

debug: $(FICHEIROS)
	cc $(DFLAGS) -c entidades.c
	cc $(DFLAGS) -c estado.c
	cc $(DFLAGS) -c html.c
	cc $(DFLAGS) -c main.c
	cc $(DFLAGS) -c posicao.c
	cc $(DFLAGS) $(OBJS) -o $(EXEC)

all: $(FICHEIROS)
	cc $(CFLAGS) -c entidades.c
	cc $(CFLAGS) -c estado.c
	cc $(CFLAGS) -c html.c
	cc $(CFLAGS) -c main.c
	cc $(CFLAGS) -c posicao.c
	cc $(CFLAGS) $(OBJS) -o $(EXEC)
	strip -s $(EXEC)

install: all $(IMAGENS)
	sudo mkdir -p /var/www/html/images/
	sudo cp -f $(IMAGENS) -t /var/www/html/images/
	sudo cp $(EXEC) -t /usr/lib/cgi-bin

entrega: $(FICHEIROS) $(IMAGENS)
	zip -n : -9 entrega.zip $(FICHEIROS) $(IMAGENS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf entrega.zip Doxyfile latex html install $(OBJS) $(EXEC)
