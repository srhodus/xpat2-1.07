/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module X-markcard.c			     */
/*									     */
/*	Routines for marking selected cards				     */
/*	written by Heiko Eissfeldt and Michael Bischoff			     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#include "X-pat.h"

#ifndef NO_ROUND_CARDS
#include	<X11/Xmu/Drawing.h>
#endif


#include "stipple.bm"

/* game.for set-mark / clear-mark */

static GC stipplegc;
static Pixmap mark_storage = 0;
static int mark_height = 0, mark_width = 0;

static int rem_x, rem_y;
static XSize_t rem_w, rem_h;	   /* h = 0: only horizontal bars saved */

void init_mark(unsigned long pixel, int markwidth) {
    /* make GCs for dashed lines or colored lines (to mark cards) */
    XGCValues gcv;
    long gcflags;
    Pixmap stipplemap;

    stipplemap = XCreateBitmapFromData(dpy,
				       RootWindow(dpy, screen),
				       stipple_bits,
				       stipple_width,
				       stipple_height);
    gcflags = GCForeground | /* GCBackground | */ GCGraphicsExposures |
	GCFillStyle | GCStipple;
    gcv.graphics_exposures = True;
    gcv.foreground = BlackPixel(dpy, screen);
    gcv.background = WhitePixel(dpy, screen);
    gcv.stipple = stipplemap;
    gcv.fill_style = FillStippled;
    stipplegc = XCreateGC(dpy, RootWindow(dpy, screen), gcflags, &gcv);
}

static void create_mark_storage(void) {
    mark_storage = XCreatePixmap(dpy, table, mark_width, mark_height, /* geo.lsw, geo.lsh, */
				 DefaultDepth(dpy, screen));

}

static void free_mark(void) {
    if (mark_storage)
	XFreePixmap(dpy, mark_storage);
    mark_storage = 0;
}

static void set_mark(int x, int y, XSize_t W, XSize_t h) {
    if (h > mark_height) {	/* make sure there's enough space */
	free_mark();
	mark_height = h;
    }
    if (W > mark_width) {
	free_mark();
	mark_width = W;
    }
    if (!mark_storage)
	create_mark_storage();

    rem_h = h;
    rem_w = W;
    rem_x = x;
    rem_y = y;
    XCopyArea(dpy, table, mark_storage, whitegc, x, y,
	      rem_w, rem_h, 0, 0);
#ifndef NO_ROUND_CARDS
    if (ROUND_W)
	XmuFillRoundedRectangle(dpy, table, stipplegc, x, y,
				rem_w, rem_h, ROUND_W, ROUND_H);
    else
#endif
	XFillRectangle(dpy, table, stipplegc, x, y, rem_w, rem_h);
    XFlush(dpy);
}

static void clear_mark(void) {
    XCopyArea(dpy, mark_storage, table, whitegc, 0, 0,
	      rem_w, rem_h, rem_x, rem_y);
    XFlush(dpy);
}

/* pile is completely drawn and unmarked. */
/* check, if pile has to be marked.       */
/* if so, do it                           */

void show_mark(boolean on) {
    if (!game.graphic)
	return;
    if (on) {
	struct pilegeometry *p;
	int f, l;
	int pile, m_x, m_y, m_w, m_h;

 	if (game.srcind < 0)
	    return;
	if (!mark_storage) {
	    mark_height = geo.lsh;
	    mark_width = geo.lsw;
	    create_mark_storage();
	}
	
	p = geo.pg + (pile = getpile(game.srcind));
	f = game.srcind - INDEX_OF_FIRST_CARD(pile);
	l = CARDS_ON_PILE(pile)-1;
	if (p->cdx >= 0) {
	    m_x = p->x + p->ox + f * p->cdx;
	    m_w = (l-f)*p->cdx + geo.cw;
	} else {
	    m_x = p->x + p->ox + l * p->cdx;
	    m_w = (f-l)*p->cdx + geo.cw;
	}
	if (p->cdy >= 0) {
	    m_y = p->y + p->oy + f * p->cdy;
	    m_h = (l-f)*p->cdy + geo.ch;
	} else {
	    m_y = p->y + p->oy + l * p->cdy;
	    m_h = (f-l)*p->cdy + geo.ch;
	}
	set_mark(m_x, m_y, m_w, m_h);
    } else {
	clear_mark();
    }
}
