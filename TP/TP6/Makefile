NAME=clm
CC=gcc
CFLAGS=-ansi -pedantic -Wall
OBJ=main.o hachage.o tri.o lecteur.o tests.o

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lncurses

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(NAME)

install: $(NAME)
	mkdir bin
	mv $(NAME) bin/$(NAME)
	make mrproper

uninstall:
	rm -rf bin
