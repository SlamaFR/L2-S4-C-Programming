CC = gcc
CFLAGS = -ansi -pedantic -Wall -lncurses
OBJ = Main.o Graphe.o Grille.o Regles.o Dictionnaire.o

main: $(OBJ)
	$(CC) -o main $(OBJ) $(CFLAGS) 

%.o: %.c
	$(CC) -c $< $(CFLAGS)

mrproper:
	rm -f *.o
	
clean:
	rm -f main

vacuum:
	make mrproper
	make clean