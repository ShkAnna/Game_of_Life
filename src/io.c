#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "io.h"


#define SIZEX 1200
#define SIZEY 800

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i)
		if (ligne[i] == -2 ) printf ("|   "); else if (ligne[i] == -1) printf ("| X "); else printf ("| %d ",ligne[i]);
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
	printf("\n\e[%dA",g.nbl*2 + 6);
}

void paint(cairo_surface_t *surface, grille g, int temps, int cyclique, int vieillissement){
	cairo_t *cr;
	cr=cairo_create(surface);

	cairo_set_source_rgb (cr, 0.2, 0.0, 0.2);
	cairo_paint(cr);

	cairo_select_font_face (cr, "Sans",
		CAIRO_FONT_SLANT_NORMAL,
		CAIRO_FONT_WEIGHT_NORMAL);

	cairo_set_source_rgba (cr, 1, 0.1, 0.2, 0.7);
	cairo_set_line_width (cr, 6.0);

	int gl = g.nbl;
	int gc = g.nbc;
	float taille_carre_x = (SIZEX/2)/gc;
	float taille_carre_y = (SIZEX/2)/gl;
	double x_carre;
	double y_carre;
	double x;
	double y;
	int chiffre_cel;
	char str_cel[50];
	int i,j;

	cairo_set_source_rgb (cr, 0.7, 0.7, 0.7);
	cairo_set_font_size (cr, 30);
	cairo_move_to (cr, SIZEX/2+50, 50);
	sprintf(str_cel, "Temps d'evolution: %d", temps);
	cairo_show_text (cr, str_cel);
	cairo_move_to (cr, SIZEX/2+50, 100);
	if (cyclique == 1) 
	{	
		cairo_show_text (cr, "Type de voisinage: cyclique");
	}else 
		cairo_show_text (cr, "Type de voisinage: non-cyclique");
		
	cairo_move_to (cr, SIZEX/2+50, 150);
	if (vieillissement == 1) 
	{	
		cairo_show_text (cr,"Vieillissement: oui");
	}else 
		cairo_show_text (cr,"Vieillissement: non");

	for(x_carre = 0.0, j=0;j<gc;++j) {
		for(y_carre = 0.0, i=0;i<gl;++i) {
			if(g.cellules[i][j] >=0){
				cairo_set_source_rgba (cr, 0.6, 0.9, 0.0, 0.7); //green
			} else if (g.cellules[i][j] == -1){
				cairo_set_source_rgba (cr, 0.0, 0.0, 0.0, 0.7); //black
			} else { cairo_set_source_rgba (cr, 1, 0.1, 0.2, 0.7); }//red
				

			cairo_rectangle(cr, x_carre, y_carre, taille_carre_x-8, taille_carre_y-8);
			cairo_stroke_preserve(cr);
			cairo_fill(cr);

			if(g.cellules[i][j] >=0){
				x = taille_carre_x/3.5+x_carre;
				y = taille_carre_y/1.8+y_carre;
				cairo_set_source_rgba (cr, 0.0, 0.0, 0.0, 0.9);
				cairo_set_font_size (cr, taille_carre_x/2);
				cairo_move_to (cr, x, y);
				chiffre_cel = g.cellules[i][j];
				sprintf(str_cel, "%d", chiffre_cel);
				cairo_show_text (cr, str_cel);
			}

			y_carre += taille_carre_y;
		}
		x_carre += taille_carre_x;
	}	
	cairo_destroy(cr);
}

void showText(cairo_surface_t *surface, XEvent e, Display *dpy, char* nom){
	int cel_number = -1;
	char number[100];
	cairo_t *cr;
	cr=cairo_create(surface);
	cairo_set_source_rgb (cr, 0.7, 0.7, 0.7);
	cairo_set_font_size (cr, 30);
	cairo_move_to (cr, 10, 700);
	cairo_show_text (cr,"Ecris le numero de la grille et valide avec Entree: ");

	while (1)
    {
        XNextEvent(dpy, &e);
		if (e.type == KeyPress)
        {
			if(e.xkey.keycode>=10 && e.xkey.keycode<=19 ) {
				cel_number = e.xkey.keycode;
				cel_number = (cel_number+1)%10;
				sprintf(number, "%d", cel_number);
				cairo_show_text (cr, number);
				strcat(nom, number);
			} else if(cel_number != -1 && e.xkey.keycode==36){break;}
		}
	}
}

void debut_jeu(grille *g, grille *gc){
	//char c = getchar();
	char nom[10];
	int temps = 0;
	int cyclique = 1;
	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cyclique;
	int vieillissement = 0;
	//int nouvelleGrille = 0;
	FILE * fileexists = NULL;

	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;

	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}
	// init the display
	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0,
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "Jeu de la vie");
	XSelectInput(dpy, win, ExposureMask | ButtonPressMask | KeyPressMask);
	XMapWindow(dpy, win);

// create cairo surface
	cairo_surface_t *cs;
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	while (1) // touche 'q' pour quitter
	{
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			paint(cs, *g, temps, cyclique, vieillissement);
		} else if (e.type == KeyPress) {
			if(e.xkey.keycode==36) { // \n

					temps++;
					evolue(g,gc,compte_voisins_vivants,vieillissement);
					efface_grille(*g);
					paint(cs, *g, temps, cyclique, vieillissement);
					affiche_grille(*g, temps, cyclique, vieillissement);
			} else if(e.xkey.keycode==57) {//n + touche pour chargee dynamiquement le nom du nouveau grille
					char fname[100] = "grilles/grille";
					do {
						paint(cs, *g, temps, cyclique, vieillissement);
						showText(cs, e, dpy, nom);
						strcat(fname, nom);
						strcat(fname, ".txt");
						fileexists = fopen(fname, "r");
						if (fileexists == NULL) {
							strcpy(nom, "");
							strcpy(fname, "grilles/grille");
						}
					} while(fileexists == NULL);
					fclose(fileexists);
					fileexists = NULL;

					libere_grille(g);
					libere_grille(gc);
					temps = 0;
					init_grille_from_file(fname, g);

					alloue_grille (g->nbl, g->nbc, gc);
					paint(cs, *g, temps, cyclique, vieillissement);
					affiche_grille(*g, temps, cyclique, vieillissement);
					// nouvelleGrille = 1;
					strcpy(nom, "");
					strcpy(fname, "grilles/grille");
				} else if (e.xkey.keycode==54) { // c + touche pour changer le type de voisinage
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
					paint(cs, *g, temps, cyclique, vieillissement);
				} else if(e.xkey.keycode==55) {// v
					if (vieillissement == 0)
					{

						vieillissement = 1;
					}
					else
					{

						vieillissement = 0;
					}
					paint(cs, *g, temps, cyclique, vieillissement);
				} else if (e.xkey.keycode==24) {//q
					break;
				} /*else { // touche non traitée
					//printf("\n\e[1A");
				}*/
		}
		//c = getchar();
	}
	cairo_surface_destroy(cs);
	XCloseDisplay(dpy);// close the display
	return;
}
