/**
 * \file io.h
 * \brief Affichage des grilles
 *
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "grille.h"
#include "jeu.h"

#if GUI

#define SIZEX 1200
#define SIZEY 800

/**
 * @brief      Affichage de la grille dans la fenetre X avec cairo
 *
 * @param      surface         Surface de cairo
 * @param[in]  g               une grille
 * @param[in]  temps           temps d'évolution
 * @param[in]  cyclique        Type de voisinage (cyclique / non-cyclique)
 * @param[in]  vieillissement  Vieillissement on /off
 */
void paint(cairo_surface_t *surface, grille g, int temps, int cyclique, int vieillissement);

/**
 * @brief      Affiche une proposition de changer la grille
 *
 * @param      surface  Surface de cairo
 * @param      e        XEvent
 * @param      dpy      Display
 * @param      nom      Tableau de caractere 
 */
void showText(cairo_surface_t *surface, XEvent e, Display *dpy, char* nom);

#else

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

#endif

/**
 * @brief      Debute le jeu
 *
 * @param      g     une grille
 * @param      gc    la grille avec la même taille de memoire comme grille g
 */
void debut_jeu(grille *g, grille *gc);

#endif
