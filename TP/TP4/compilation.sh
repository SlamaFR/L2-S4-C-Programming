gcc -c player.h player.c
gcc -c tablet.h tablet.c
gcc -c position.h position.c
gcc -c move.h move.c
gcc -c main.c
gcc main.o player.o tablet.o position.o move.o -o chomp -Wall -pedantic -lncurses
