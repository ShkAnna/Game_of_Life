/**
 * \file jeu.h
 * \brief Fonctions permettant l'avancement du jeu
 *
 */
#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 * @brief      Modulo modifié pour traiter correctement les bords i=0 et j=0 \n
 * 			   dans le calcul des voisins avec bords cycliques.
 *
 * @param[in]  i     indice de la ligne / colonne
 * @param[in]  m     nombre de lignes / colonnes de la grille
 *
 * @return     modulo de deux parametres
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 * @brief      Compte le nombre de voisins vivants de la cellule (i,j). \n
 * 			   Les bords sont cycliques.
 *
 * @param[in]  i     indice de la ligne
 * @param[in]  j     indice de la colonne
 * @param[in]  g     une grille
 *
 * @return     nombre des voisins vivants
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g);

/**
 * @brief      Compte le nombre de voisins vivants de la cellule (i,j). \n
 * 			   Les bords sont non-cycliques.
 *
 * @param[in]  i     indice de la ligne
 * @param[in]  j     indice de la colonne
 * @param[in]  g     une grille
 *
 * @return     nombre des voisins vivants
 */
int compte_voisins_vivants_noncyclique (int i, int j, grille g);

/**
 * @brief      Fait évoluer la grille g d'un pas de temps.
 *
 * @param      g     une grille
 * @param      gc    une grille alloue avec même espace memoire que la grille g
 */
void evolue (grille *g, grille *gc, int (*compte_voisins_vivants) (int, int, grille), int vieillissement);

#endif
