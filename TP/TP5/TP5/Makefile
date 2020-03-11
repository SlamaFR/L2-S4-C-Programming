CC=gcc
CFLAGS=-ansi -pedantic -Wall
OBJ=Pomme.o Case.o Direction.o Serpent.o Monde.o Main.o

Snake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lncurses

Main.o: Main.c Monde.h

Pomme.o: Pomme.c Pomme.h Case.h

Serpent.o: Serpent.c Direction.h Serpent.h Case.h

Pomme.o: Monde.c Monde.h POmme.h Serpent.h Case.h Direction.h

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f Snake

install: Snake
	mkdir bin
	mv Snake bin/Snake
	make mrproper

uninstall:
	rm -rf bin
