/**
 * \file io.h
 * \brief Affichage des grilles
 *
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/**
 * @brief      Affichage d'un trait horizontal
 *
 * @param[in]  c     taille d'un trait horizontal
 */
void affiche_trait (int c);

/**
 * @brief      Affichage d'une ligne de la grille
 *
 * @param[in]  c      taille d'un trait horizontal
 * @param      ligne  un pointeur sur la ligne à afficher
 */
void affiche_ligne (int c, int* ligne);

/**
 * @brief      Affichage d'une grille
 *
 * @param[in]  g               une grille
 * @param[in]  temps           temps d'évolution
 * @param[in]  cyclique        Type de voisinage (cyclique / non-cyclique)
 * @param[in]  vieillissement  Vieillissement on /off
 */
void affiche_grille (grille g, int temps, int cyclique, int vieillissement);

/**
 * @brief      Effacement d'une grille
 *
 * @param[in]  g     une grille
 */
void efface_grille (grille g);

/**
 * @brief      Debute le jeu
 *
 * @param      g     une grille
 * @param      gc    la grille avec la même taille de memoire comme grille g
 */
void debut_jeu(grille *g, grille *gc);

#endif
