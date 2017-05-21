HIGHSCOREFILE=/var/www/html/highscoresfile
CC=gcc
#CC=musl-gcc
EXEC=rogue

FLAGS=-static -Wall -Wextra -Werror -lm -pedantic -Iinclude/
DFLAGS=$(FLAGS) -g
CFLAGS=$(FLAGS) -O3

IMAGENS=images/Char_14.png images/character_21.png images/lava_pool1.png images/tombstone.png

INCLUDE=include/check.h include/entidades.h include/estado.h include/html.h include/jogo.h include/posicao.h

SRC=entidades.c \
    estado.c    \
    html.c      \
    jogo.c      \
    main.c      \
    posicao.c

OBJS=entidades.o \
     estado.o    \
     html.o      \
     jogo.o      \
     main.o      \
     posicao.o

DEPS=$(SRC) $(INCLUDE) Makefile

debug: $(DEPS)
	$(CC) $(DFLAGS) -c $(SRC)
	$(CC) $(DFLAGS) $(OBJS) -o $(EXEC)

all: $(DEPS)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)
	strip -s $(EXEC)

install: all $(IMAGENS)
	sudo mkdir -p /var/www/html/images/
	sudo mkdir -p -m 0777 /var/www/html/files/
	sudo touch $(HIGHSCOREFILE)
	sudo chmod 0666 $(HIGHSCOREFILE)
	sudo cp -f $(IMAGENS) -t /var/www/html/images/
	sudo cp $(EXEC) -t /usr/lib/cgi-bin

entrega: $(DEPS) $(IMAGENS)
	zip -n : -9 entrega.zip $(DEPS) $(IMAGENS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf entrega.zip Doxyfile latex html $(OBJS) $(EXEC)
