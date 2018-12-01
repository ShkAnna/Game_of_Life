#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "grille.h"
#include "io.h"
#include "jeu.h"

#define SIZEX 800
#define SIZEY 800

//#define M_PI 3.14
/*
void paint(cairo_surface_t *surface, grille g)
{
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	// background
	cairo_set_source_rgb (cr, 0.2, 0.0, 0.2);
	cairo_paint(cr);

	// line
  cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	cairo_move_to (cr, 50.0, 50.0);
	cairo_line_to(cr, 50.0, 500.0);
	cairo_line_to(cr, 500.0, 500.0);
	cairo_set_line_width (cr, 3);
	cairo_stroke (cr);

	cairo_destroy(cr); // destroy cairo mask
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);
	//cairo_text_extents_t extents;
	cairo_set_source_rgb (cr, 0.2, 0.0, 0.2);
	cairo_paint(cr);

	const char *utf8 = "cairo";
	double x,y;
	// background
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);

	cairo_select_font_face (cr, "Sans",
  	CAIRO_FONT_SLANT_NORMAL,
    CAIRO_FONT_WEIGHT_NORMAL);

	cairo_set_font_size (cr, 52.0);
	cairo_text_extents (cr, utf8, &extents);
	x = 128.0-(extents.width/2 + extents.x_bearing);
	y = 128.0-(extents.height/2 + extents.y_bearing);

	cairo_move_to (cr, x, y);
	//cairo_show_text (cr, utf8);

	//draw helping lines
	//cairo_set_source_rgba (cr, 1, 0.7, 0.8, 0.6);
	cairo_set_source_rgba (cr, 1, 0.1, 0.2, 0.7);
	cairo_set_line_width (cr, 6.0);

	int gl = g.nbl;
	int gc = g.nbc;
	int i;

	for (i=0; i<gl; ++i) {
		dessiner_cellules(surface, gc, g.cellules[i], g);
	}
	  cairo_rectangle(cr, 0, 0, 80, 80);
	  cairo_stroke_preserve(cr);
	  cairo_fill(cr);
}*/




int main (int argc, char ** argv) {
	/*// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;*/

	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;

	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g, 0, 1, 0);

	debut_jeu(&g, &gc);
	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
