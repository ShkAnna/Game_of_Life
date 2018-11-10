#include<string.h>
#include "io.h"

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i)
		if (ligne[i] == -1 ) printf ("|   "); else printf ("| %d ",ligne[i]);
	printf("|\n");
	return;
}

void affiche_grille (grille g, int temps, int cyclique, int vieillissement){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	printf("\e[K");
	printf("Temps d'evolution: %d; Type de voisinage: ", temps);
	if (cyclique == 1) printf("cyclique; ");
	else printf("non-cyclique; ");
	printf("Vieillissement: ");
	if (vieillissement == 1) printf("oui\n\n");
	else printf("non\n\n");

	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 7);
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	char nom[100];
	int temps = 1;
	int cyclique = 1;
	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cyclique;
	int vieillissement = 0;

	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				evolue(g,gc,compte_voisins_vivants,vieillissement);
				efface_grille(*g);
				affiche_grille(*g, temps, cyclique, vieillissement);
				temps++;
				break;
			}

			case 'n' :
			{//touche pour chargee dynamiquement le nom du nouveau grille
				printf("Ecris grilles/ et le nom de grille laquelle tu veux charger (grille1.txt/grille2.txt...): ");
				scanf("%s", nom);
				libere_grille(g);
				temps = 0;
				init_grille_from_file(nom,g);
				alloue_grille (g->nbl, g->nbc, gc);
				affiche_grille(*g, temps, cyclique, vieillissement);
				printf("\n");
				break;
			}

			case 'c' :
			{//touche pour changer le type de voisinage
				if (cyclique == 1)
				{
					compte_voisins_vivants = compte_voisins_vivants_noncyclique;
					cyclique = 0;
				}
				else
				{
					compte_voisins_vivants = compte_voisins_vivants_cyclique;
					cyclique = 1;
				}
				break;
			}

			case 'v' :
			{
				if (vieillissement == 0)
				{

					vieillissement = 1;
				}
				else
				{

					vieillissement = 0;
				}
				break;
			}

			default :
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar();
	}
	return;
}
