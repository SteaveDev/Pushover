projet: projet.o saisie.o color.o fonction.o
	gcc -Wall -o projet projet.o saisie.o color.o fonction.o

saisie.o: saisie.c saisie.h
	gcc -Wall -c saisie.c

color.o: color.c color.h
	gcc -Wall -c color.c

fonction.o: fonction.c fonction.h saisie.h color.h
	gcc -Wall -c fonction.c

projet.o: projet.c saisie.h color.h fonction.h
	gcc -Wall -c projet.c

