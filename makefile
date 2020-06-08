all: ./Objects/main.o ./Objects/Cidades.o
	gcc -o TP2 ./Objects/main.o ./Objects/Cidades.o -lm
./Objects/Cidades.o: ./Partials/Cidades.c ./Partials/Headers/Cidades.h
	gcc -c -lm ./Partials/Cidades.c -o ./Objects/Cidades.o
./Objects/main.o: main.c
	mkdir -p Objects
	gcc -c -lm main.c -o ./Objects/main.o
