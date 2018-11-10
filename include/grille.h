/**
 * \file grille.h
 * \brief Travail sur les grilles
 *
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/** @struct grille
 *  @brief Structure de notre grille
 *  @var grille::nbl
 *  Nombre de lignes de la grille
 *  @var grille::nbc
 *  Nombre de colonnes de la grille
 *  @var grille::cellules
 *  Tableau de tableau de cellules
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;

/**
 * @brief      Alloue une grille de taille l*c, et initialise toutes les cellules à mortes
 *
 * @param[in]  l     nombre des lignes
 * @param[in]  c     nombres des colonnes
 * @param      g     un pointeur sur une grille
 */
void alloue_grille (int l, int c, grille* g);

/**
 * @brief      Libère une grille
 *
 * @param      g     un pointeur sur une grille
 */
void libere_grille (grille* g);

/**
 * @brief      Alloue et initalise la grille g à partir d'un fichier
 *
 * @param      filename  nom du fichier avec la grille
 * @param      g         une grille
 */
void init_grille_from_file (char * filename, grille* g);

/**
 * @brief      Rend vivante la cellule de coordonnées (i,j) de la grille g
 *
 * @param[in]  i     indice de la ligne
 * @param[in]  j     indice de la colonne
 * @param[in]  g     une grille
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 0;}

/**
 * @brief      Rend morte la cellule (i,j) de la grille g
 *
 * @param[in]  i     indice de la ligne
 * @param[in]  j     indice de la colonne
 * @param[in]  g     une grille
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = -1;}

/**
 * @brief      Teste si la cellule (i,j) de la grille g est vivante
 *
 * @param[in]  i     indice de la ligne
 * @param[in]  j     indice de la colonne
 * @param[in]  g     une grille
 *
 * @return     { description_of_the_return_value }
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] >= 0;}

/**
 * @brief      Recopie gs dans gd (sans allocation)
 *
 * @param[in]  gs    une grille
 * @param[in]  gd    copie de grille gs
 */
void copie_grille (grille gs, grille gd);

#endif
