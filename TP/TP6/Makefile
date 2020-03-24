NAME=clm
CC=gcc
CFLAGS=-ansi -pedantic -Wall
OBJ=main.o liste.o lecteur.o tests.o analyseur.o

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

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
