#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

#include <time.h>

#include "saisie.h"
#include "color.h"
#include "fonction.h"

int main()
{
	srand(time(NULL));
	int nb=0;
	while(nb<2 || nb>8){
		printf("Saisir la taille de la grille entre 2 et 8 inclus:\n");
		scanf("%d", &nb);
	}
	
	jouer(nb);

	return 0;
}
