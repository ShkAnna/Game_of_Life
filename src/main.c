#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "grille.h"
#include "io.h"
#include "jeu.h"

int main (int argc, char ** argv) {
char fname[100] = "grilles/grille";
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;

	strcat(fname, argv[1]);
	strcat(fname, ".txt");

	init_grille_from_file(fname,&g);
	alloue_grille (g.nbl, g.nbc, &gc);

	#ifndef GUI
		affiche_grille(g, 0, 1, 0, -1);
	#endif

	debut_jeu(&g, &gc);
	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
