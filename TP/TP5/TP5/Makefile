CC=gcc
CFLAGS=-ansi -pedantic -Wall
OBJ=Main.o

Snake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

Main.o: Main.c

# Pomme.o: Case.o

# Serpent.o: Case.o Direction.o

# Monde.o: Pomme.o Serpent.o

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f Snake

install: Snake
	mkdir ../bin
	mv Snake ../bin/Snake
	make mrproper

uninstall:
	rm -rf ../bin
