#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

#include "color.h"
#include "saisie.h"

typedef struct{
	int *grille;
	int n;
	int nb_cases_libres;
}Gratte_ciel;


Gratte_ciel * creer_gratte_ciel(int nb){	//parametre : nb de case a allouer
	Gratte_ciel *g1 = (Gratte_ciel *)malloc(sizeof(Gratte_ciel));	//on fait une allocation
	if(nb>=2 && nb<=8){	//verifie si nb est correct
		if(g1==NULL)	//verifie memoire
			exit(1);	//sinon on sort du fichier
		else{
			g1->grille=(int*)malloc((nb+2)*(nb+2) * sizeof(int));	//on fait une allocation 
			if(g1->grille==NULL)	//verifie memoire
				exit(1);	//on sort du fichier
			g1->n=nb;	//n quartier = nb
			g1->nb_cases_libres=nb*nb;	//nb case libre = longeur * largeur
		}
		return g1;
	}
	else{
		printf("Valeur incorrecte !\n");	//parametre incorrect
		return g1=NULL;
	}
}


/*QUESTION 3*/
void detruire_gratte_ciel(Gratte_ciel * p){
	if(p==NULL)
		exit(-1);
	free(p->grille); //libere p->grille
	free(p);	//libere p
	p=NULL;		//on pointe sur NULL pour ne pas avoir de probleme
}

/*QUESTION 4*/
int indice_grille_valide(Gratte_ciel * p, int i){
	if(p==NULL || !(i>=0 && i<p->n+2))
		return 0;	//on verifie si i n'est pas compris entre le depart (0) et la limite 
	return 1;
}

/*QUESTION 5*/
int get_case(Gratte_ciel * p, int i, int j){
	if(p==NULL || !(indice_grille_valide(p,i) && indice_grille_valide(p,j)))
		return -1;
	return p->grille[i*(p->n+2) + j];
}


/*QUESTION 6*/
int set_case(Gratte_ciel * p, int i, int j, int val){
	if(p==NULL)
		return 0;
	if(indice_grille_valide(p,i) && indice_grille_valide(p,j) && val>=0 && val <=p->n){ //si i et j sont dans la grille		
		if(i>=1 && i<=p->n && j>=1 && j<=p->n){	//si i et j sont dans le quartier
			if(p->grille[i*(p->n+2)+j]==0 && val>0)	//si case=0 et val>0 -> caselibre--
				p->nb_cases_libres--;
			else if(p->grille[i*(p->n+2)+j]!=0 && val==0)	//si case!=0 et val=0 -> caselibre++
				p->nb_cases_libres++;
		}
		p->grille[i*(p->n+2)+j]=val;	//on affecte val a la case
		return 1;
	}
	return 0;
}


/*QUESTION 7*/
int get_nb_cases_libres(Gratte_ciel * p){
	if(p==NULL)
		return 0;
	return p->nb_cases_libres;	//retourne le nb de case libre
}


void affichage_gratte_ciel(Gratte_ciel * p){
	if(p==NULL)
		exit(-1);
	int i,j,lettre=65;
	for(i=1; i<=p->n; i++){
		if(i==1)
			printf("                      ");
		printf("%d            ", i);
	}
	printf("\n");
	for(i=0;i<=p->n+1;i++){
		for(j=0;j<=p->n+1;j++){ 
			if((i==0 && j==0) || (i==0 && j==p->n+1 ) || ( i==p->n+1 && j==0) || (i==p->n+1 && j==p->n+1))
				printf("               ");
			else if(i==0 || i==p->n+1 || j==0 || j==p->n+1){
				if(j==0)
					printf("    ");
				color_printf(YELLOW,MAGENTA, "           ");
			}
			else
				color_printf(GREEN,CYAN, "           ");
			printf("  ");
		}
		printf("\n");
		for(j=0;j<=p->n+1;j++){
			if((i==0 && j==0)|| (i==0 && j==p->n+1 ) || ( i==p->n+1 && j==0) || (i==p->n+1 && j==p->n+1))
				printf("               ");
			else if(i==0 || i==p->n+1 || j==0 || j==p->n+1){
				if(j==0){
					printf(" %c  ", (char)lettre);
					lettre++;
				}
				color_printf(YELLOW,MAGENTA, "     %d     ",p->grille[i*(p->n+2)+j]);
			}
			else
				color_printf(GREEN,CYAN, "     %d     ",p->grille[i*(p->n+2)+j]);
			printf("  ");
		}
		printf("\n");
		for(j=0;j<=p->n+1;j++){ 
			if((i==0 && j==0)|| (i==0 && j==p->n+1 ) || ( i==p->n+1 && j==0) || (i==p->n+1 && j==p->n+1))
				printf("               ");
			else if(i==0 || i==p->n+1 || j==0 || j==p->n+1){
				if(j==0)
					printf("    ");
				color_printf(YELLOW,MAGENTA, "           ");
			}
			else
				color_printf(GREEN,CYAN, "           ");
			printf("  ");
		}
		printf("\n\n");
	}
}


int est_case_bordure(Gratte_ciel * p, int i, int j){
	if(p==NULL || !((i==0 && j>=1 && j<=p->n) || ((i>=1 && i<=p->n) && (j==0 || j==p->n+1)) || (i==p->n+1 && j>=1 && j<=p->n)))
		return 0;		//bordure nord//est-ouest//sud
	return 1;		
}


int nb_immeubles_visibles(Gratte_ciel * p, int i, int j){
	if(p==NULL || est_case_bordure(p, i, j)==0) //si ce n'est pas une case de la bordure
		return -1;
	int cpt=0, nb; //sinon
	if(i==0 || i==p->n+1){		//si c'est la bordure nord ou sud
		if(i==0){	//bordure nord
			i++;	//on descend, on rentre dans le quatier
			nb = get_case(p,i,j);
			if(nb!=0)	//on verifie si la premiere case contient une valeur
				cpt++;
			for(; i<=p->n; i++){
				if(nb < get_case(p,i,j)){
					nb = get_case(p,i,j);	//on verifie si les autres cases sont plus grandes que la precedente
					cpt++;
				}
			}
			return cpt;
		}
		else{
			i--;
			nb = get_case(p,i,j);
			if(nb!=0)
				cpt++;
			i--;
			for(; i>0; i--){
				if(nb < get_case(p,i,j)){
					nb = get_case(p,i,j);
					cpt++;
				}
			}
			return cpt;
		}
	}
	if(j==0){
		j++;
		nb = get_case(p,i,j);
		if(nb!=0)
			cpt++;
		j++;
		for(; j<=p->n; j++){
			if(nb < get_case(p,i,j)){
				nb = get_case(p,i,j);
					cpt++;
			}
		}
		return cpt;
		}
	j--;
	nb = get_case(p,i,j);
	if(nb!=0)
		cpt++;
	j--;
	for(; j>0; j--){
		if(nb < get_case(p,i,j)){
			nb = get_case(p,i,j);
			cpt++;
		}
	}
	return cpt;
}
	


void calcul_bordure(Gratte_ciel * p){
	if(p==NULL)
		exit(-1);
	int i, j;	//coordonnees
	for(i=0; i<p->n+2; i++)		//on test tout les cases de la grille
		for(j=0; j<p->n+2; j++)
			if(est_case_bordure(p,i,j))	//si la case de la grille est une bordure
				set_case(p,i,j,nb_immeubles_visibles(p,i,j));//on affecte le nombre d'immeuble visible grace a la fonction
}

int valeurs_differentes_ligne(Gratte_ciel * p, int ind){
	if(p==NULL)
		return 0;
	int cpt=0, i, j;	//coordonnees
	if(ind>=1 && ind<=p->n)		//on verifie si l'indice est bien dans le quartier
		for(i=1; i<=p->n; i++)		//on test la case principale
			for(j=1; j<=p->n; j++)		//on test la case principale avec toute les autres cases
				if(get_case(p,ind,i)==get_case(p,ind,j))
					cpt++;
	if(cpt==p->n)
		return 1;
	return 0;
}


int valeurs_differentes_colonne(Gratte_ciel * p, int ind){
	if(p==NULL)
		return 0;
	int cpt=0, i, j;	//coordonnees
	if(ind>0 && ind<p->n+1)		//on verifie si l'indice est bien dans le quartier
		for(i=1; i<p->n+1; i++)		//on test la case principale
			for(j=1; j<p->n+1; j++)	//on test la case principale avec toute les autres cases
				if(get_case(p,i,ind)==get_case(p,j,ind)) //i et j
					cpt++;
	if(cpt==p->n)
		return 1;
	return 0;
}


int valeurs_differentes_quartier(Gratte_ciel * p){
	if(p==NULL)
		return 0;
	int cpt=0, i, j;	//coordonnees
	for(i=1; i<p->n+1; i++)		//on test tout les cases de la grille
		for(j=1; j<p->n+1; j++)
			if(valeurs_differentes_ligne(p, i) && valeurs_differentes_colonne(p, j))
				cpt++;
	if(cpt==p->n*p->n)
		return 1;
	return 0;
}

int bordure_correcte(Gratte_ciel * p) {
	if(p==NULL)
		return 0;
	int i, j;	//coordonnees
	for(i=0; i<p->n+2; i++)		//on test tout les cases de la grille
		for(j=0; j<p->n+2; j++)
			if(est_case_bordure(p,i,j) && p->grille[(i*(p->n+2))+j]!=0 && p->grille[(i*(p->n+2))+j] != nb_immeubles_visibles(p,i,j))
				return 0;
	return 1;
} 


int quartier_est_solution(Gratte_ciel * p){
	if(p==NULL || !(valeurs_differentes_quartier(p) && bordure_correcte(p) && get_nb_cases_libres(p)==0))
		return 0;
	return 1;
}

void permute_lignes(Gratte_ciel * p, int i, int j){
	if(p==NULL || i==j)
		exit(-1);
	int a, val;
	for(a=1; a<p->n+1; a++){
		val=get_case(p,i,a);
		set_case(p, i, a, get_case(p,j,a));
		set_case(p, j, a, val);
	}
}

void permute_colonnes(Gratte_ciel * p, int i, int j){
	if(p==NULL || i==j)
		exit(-1);
	int a, val;
	for(a=1; a<p->n+1; a++){
		val=get_case(p, a, i);
		set_case(p, a, i, get_case(p,a,j));
		set_case(p, a, j, val);
	}
}

void permute_nombres(Gratte_ciel * p, int nb1, int nb2){
	if(p==NULL || get_nb_cases_libres(p)!=0 || nb1==nb2 || nb1<1 || nb1>p->n || nb2<1 || nb2>p->n)
		exit(-1);
	int i, j;
	for(i=1; i<=p->n; i++)
		for(j=1; j<=p->n; j++){
			if(get_case(p,i,j)==nb1)
				set_case(p,i,j,nb2);
			else if(get_case(p,i,j)==nb2)
				set_case(p,i,j,nb1);
		}
}



void remplir_quartier(Gratte_ciel * p){
	if(p==NULL)
		exit(-1);
	int i, j, nb=1;
	for(i=1; i<p->n+1; i++)
		for(j=1; j<=p->n; j++){
			if(nb<=p->n){
				set_case(p,i,j,nb);
				if(j<p->n)
					nb++;
			}
			else{
				nb=1;
				set_case(p,i,j,nb);
				nb++;
			}
		}
}

int nombre_aleatoire(int min, int max){
	return rand()%(max-min)+min;
}

void quartier_aleatoire(Gratte_ciel * p){
	if(p==NULL)
		exit(-1);
	remplir_quartier(p);
	int nb = nombre_aleatoire(50,101);
	int i, nb1, nb2, nb3, nb4, nb5, nb6;
	for(i=0; i<nb; i++){
		do{
			nb1=nombre_aleatoire(1,p->n+1);
			nb2=nombre_aleatoire(1,p->n+1);
			nb3=nombre_aleatoire(1,p->n+1);
			nb4=nombre_aleatoire(1,p->n+1);
			nb5=nombre_aleatoire(1,p->n+1);
			nb6=nombre_aleatoire(1,p->n+1);
		}while(nb1==nb2 || nb3==nb4 || nb5==nb6);
		permute_lignes(p, nb5, nb6);
		permute_nombres(p, nb1, nb2);
		permute_colonnes(p, nb3, nb4);
	}	
}


Gratte_ciel * creer_gratte_ciel_aleatoire(int n){
	Gratte_ciel * g1 = (Gratte_ciel *)malloc(((n+2)*(n+2))*sizeof(Gratte_ciel));
	if(g1==NULL)
		exit(1);
	g1->grille=(int*)malloc(((n+2)*(n+2)) * sizeof(int));
	if(g1->grille==NULL)
		exit(1);
	g1->n=n;
	g1->nb_cases_libres=n*n;
	quartier_aleatoire(g1);
	calcul_bordure(g1);

	int i, j;
	for(i=1; i<=g1->n; i++)
		for(j=1; j<=g1->n; j++)
			set_case(g1, i, j, 0);

	return g1;
}



int mouvement(Gratte_ciel * p){
	if(p==NULL)
		return 0;
	char ch1[5];
	do{
		printf("\nCOORDONNEES : (Ligne) (Colonne) - VALEUR ou (stop): (0 -> %d inclus)\n", p->n);
		saisie_avec_espaces(ch1,5);
		printf("Vous avez saisi les coordonnees : '%s'", ch1);
		printf("\n");
	}while( ( (ch1[0]<65 || ch1[0]>=65+p->n) || (ch1[1]<48 || ch1[1]>48+p->n) || (ch1[3]<48 || ch1[3]>48+p->n) ) && !(ch1[0]=='s' && ch1[1]=='t' && ch1[2]=='o' && ch1[3]=='p') );

	if(ch1[0]=='s' && ch1[1]=='t' && ch1[2]=='o' && ch1[3]=='p')
		return 0;
	set_case(p, (int)(ch1[0]-64), (int)(ch1[1]-48), (int)(ch1[3]-48));
	return 1;
}

void jouer(int n){
	Gratte_ciel * g1 = creer_gratte_ciel_aleatoire(n);
	do{
		affichage_gratte_ciel(g1);
	}while(g1->nb_cases_libres!=0 && mouvement(g1)==1);

	if(g1->nb_cases_libres!=0)
		printf("Jeu arrete\n");
	else if(quartier_est_solution(g1)==1)
		printf("Partie gagnée\n");
	else
		printf("Partie perdue\n");
}








