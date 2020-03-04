CC=gcc
CFLAGS=-ansi -pedantic -Wall
OBJ=main.o

Snake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

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
