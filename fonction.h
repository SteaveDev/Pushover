#ifndef FONCTION_H
#define FONCTION_H
	typedef struct{
		int *grille;
		int n;
		int nb_cases_libres;
	}Gratte_ciel;
	Gratte_ciel * creer_gratte_ciel(int nb);
	void detruire_gratte_ciel(Gratte_ciel * p);
	int indice_grille_valide(Gratte_ciel * p, int i);
	int get_case(Gratte_ciel * p, int i, int j);
	int set_case(Gratte_ciel * p, int i, int j, int val);
	int get_nb_cases_libres(Gratte_ciel * p);
	void affichage_gratte_ciel(Gratte_ciel * p);
	int est_case_bordure(Gratte_ciel * p, int i, int j);
	int nb_immeubles_visibles(Gratte_ciel * p, int i, int j);
	void calcul_bordure(Gratte_ciel * p);
	int valeurs_differentes_ligne(Gratte_ciel * p, int ind);
	int valeurs_differentes_colonne(Gratte_ciel * p, int ind);
	int valeurs_differentes_quartier(Gratte_ciel * p);
	int bordure_correcte(Gratte_ciel * p);
	int quartier_est_solution(Gratte_ciel * p);
	void permute_lignes(Gratte_ciel * p, int i, int j);
	void permute_colonnes(Gratte_ciel * p, int i, int j);
	void permute_nombres(Gratte_ciel * p, int nb1, int nb2);
	void remplir_quartier(Gratte_ciel * p);
	int nombre_aleatoire(int min, int max);
	void quartier_aleatoire(Gratte_ciel * p);
	Gratte_ciel * creer_gratte_ciel_aleatoire(int n);
	int mouvement(Gratte_ciel * p);
	void jouer(int n);
#endif	
