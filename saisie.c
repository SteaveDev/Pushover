#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

#include <string.h>
#include "saisie.h"

void purger()
{
  int c;
  while ((c = getc(stdin)) != '\n' && c != EOF)
    	;
}


void clean (char *chaine)
{
   char *p = strchr(chaine, '\n');
   if (p)
    *p = 0;
   else
    purger();
}

void saisie_avec_espaces(char * chaine, int n)
{
    fgets(chaine, n, stdin);
    clean(chaine);
}
