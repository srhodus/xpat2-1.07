/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module Xlib-main.c			     */
/*									     */
/*	main function for the Xlib interface				     */
/*	written by Heiko Eissfeldt and Michael Bischoff			     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#ifdef useXlib

#include "X-pat.h"
#include "version.h"

Window table, mainwindow;
char *loadfilename = NULL;

static int audio = 1;
int checksound(void) {
    return audio;
}

void cmd_LeavePat(void) {
    play_sound("goodbye");
    exit(0);
}

static unsigned long color_to_pixel(const char *colorname) {
    if (colorname) {
	XColor color;
	Colormap cmap;
	cmap = DefaultColormap(dpy, screen);
	color.flags = DoRed | DoGreen | DoBlue;
	XAllocNamedColor(dpy, cmap, colorname, &color, &color);
	return color.pixel;
    } else
	return BlackPixel(dpy, screen);
}

#include "usage.c"

static void init_display(const char *display) {
    if ((dpy = XOpenDisplay(display)) == NULL)	{
	fprintf(stderr,"Can't open display %s\n", 
		(display ? display : getenv("DISPLAY")));
	exit(EXIT_FAILURE);
    }
    screen = DefaultScreen(dpy);
    graphic.is_color = (DisplayCells(dpy, screen) > 2);
#ifdef DEBUG
    XSynchronize(dpy, True);
#endif
}


int main(int argc, char *argv[]) {
#include "options.c"

    init_display(display);		/* connect to X-server */

    for (i = 0; i < NUMOPTIONS; ++i) {  /* get resources from server */
	char *s;
        if (options[i].cmdarg)
	    options[i].value = options[i].cmdarg;
        else if ((s = XGetDefault(dpy, "XPat", options[i].resource)))
	    options[i].value = s;
    }

    for (i = 0; i < NUMOPTIONS; ++i) {  /* value-check Numbers */
	int n;
	struct option *o;
	o = options + i;
        if (o->type == Number) {
	    n = o->value ? atoi(o->value) : -1;
	    if (n < o->minval || n > o->maxval) {
		char s[100];
		sprintf(s, "argument to option \"%s\" / resource \"%s\"",
                    o->option, o->resource);
                usage(s);
            }
            *(int *)(o->where) = n;
        } else if (o->type == Self) {
            *(int *)(o->where) = 1;
        } else /* type == String */
            *(const char **)(o->where) = o->value;
    }
    if (!sound)
	audio = 0;

    if (restoregame &&
       (decks != -1 || Xslots != -1 || faceup != -1 || facedown != -1))
	  fprintf(stderr, "warning: customization parameters are ignored\n");


    read_message_file("messages");
    read_keyboard_file("keys");

    graphics_control(Disable);
    if (restoregame)
        load_game(restoregame);
    else {
	new_rules(ruleset, decks, Xslots, faceup, facedown, jokers, tmps, p0, p1, p2, p3);
	newgame(seed);
    }

#if defined(GFX2) && defined(LOADCARDS)
    if (!graphic.is_color && !cardset)
	cardset = "french";	/* use B&W cardset, xpm requires too much colours */
#endif

    init_gfx();
    init_fonts(statusfont, buttonfont);	/* make GCs */
    init_cards(cardset, cround, cround,
	       color_to_pixel("Red3"), color_to_pixel(cbcolor),
	       mem, xpmdir, xpmcls);	/* set size of cards, make pixmaps */
    init_windows(argc, argv, geometry, gapx, gapy, bround, bround,
	bx, by, autolayout, bkcolor); /* size window */
    init_mark(color_to_pixel(markcolor), linewidth);	/* initialize card marks */
    init_arrow(arrowcolor, arrw, arrh);

    graphics_control(Enable);
    init_layout();			/* position the piles in a nice way */
    for (i = 0; i < game.numpiles; ++i)
	pile_resize(i);
    /* refresh_screen(); */
    show_message(TXT_WELCOME, VERSION);
    mainwindow = table;
    event_loop();		/* does not return */
    return 0;			/* keep compiler happy */
}

void Force_Resize(XSize_t w, XSize_t h) {
    /* for Xlib, we can use this size. It does include space for buttons and messagebox */
#if 0
    h += calc_yoff(w);	/* w, h are tableau size */
#endif
    XResizeWindow(dpy, mainwindow, w, h);
    /* or should XSetWMSizeHints() be used? */
}
#endif

