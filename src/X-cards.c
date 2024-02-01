/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module X-cards.c			     */
/*									     */
/*	Card drawing interface for X11					     */
/*	written by Heiko Eissfeldt and Michael Bischoff			     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#include "X-pat.h"

struct graphic graphic;
struct card card;
int table_clear = 1;

void win_game(void) {
#if 0
#ifdef useXlib
    XMoveWindow(dpy, finished_win, (graphic.width - FINISHED_W) / 2,
		(graphic.height - FINISHED_H) / 2);
    XMapWindow(dpy, finished_win);
    redraw_finwin((XExposeEvent *)0);	/* must unmap it later! */
#endif
#endif
#ifdef useXview
    xv_set(xv_default_server, SERVER_SYNC, FALSE, 0);
#else
    XSync(dpy, 0);	/* show all requests and let it be for now */
#endif
}


void init_gfx(void) {
    XGCValues gcv;
    long gcflags;

    blackpixel = BlackPixel(dpy, screen);
    whitepixel = WhitePixel(dpy, screen);
    
    
    /* make gc for white */
    gcv.foreground = WhitePixel(dpy, screen);
    gcv.background = BlackPixel(dpy, screen);
    gcv.graphics_exposures = False;
    gcflags = GCForeground | GCBackground | GCGraphicsExposures;
    
    whitegc = XCreateGC(dpy, RootWindow(dpy, screen), gcflags, &gcv);
    
    /* make gc for black */
    gcv.foreground = BlackPixel(dpy, screen);
    gcv.background = WhitePixel(dpy, screen);
    gcflags = GCForeground | GCBackground | GCGraphicsExposures;
    
    blackgc = XCreateGC(dpy, RootWindow(dpy, screen), gcflags, &gcv);
}


/* this is a helper routine only called by do_move(): */
/* it transfers card game.which is unknown to the generic part */
/* these transfers do not necessarily affect the appearance on the screen, */
/* they are needed due to the design of the game.structures as arrays */
/* instead of linked lists */


void move_card_data(Cardindex dst, Cardindex src) {
    game.cards[dst] = game.cards[src];
    game.visible[dst] = game.visible[src];
/*    graphic.cardy[dst] = graphic.cardy[src]; */
}


void refresh_screen(void) {
#ifdef LABER
    printf("refresh_screen called\n");
#endif
    if (table_clear) {
#ifdef LABER
	printf("(ignored)\n");
#endif
	return;
    }
    table_clear = 1;
    XClearArea(dpy, table, 0, 0, 0, 0, True);	/* force redraw */
}

/* all card drawings go through this routine:			     */
/* inform the graphics interface that cards are added (delta > 0)    */
/* or removed (delta < 0) from the specified pile. if delta = 0,     */
/* then redrawing of the complete pile is necessary (possibly caused */
/* by "new game" commands)					     */
/* if cards on the pile are marked (selected), the mark is refreshed */

void draw_pileupdate(int pile, int delta) {
    struct pilegeometry *p = geo.pg + pile;
    int cx, cy;

    if (!game.graphic) {        /* this is off when replaying saved games */
	/* only log changes */
	if (game.pile_changed[pile] == PILE_UNCHANGED)
	    game.pile_changed[pile] = delta;
	else
	    if ((delta > 0 && game.pile_changed[pile] > 0) ||
		(delta < 0 && game.pile_changed[pile] < 0))
		game.pile_changed[pile] += delta;
	    else
		game.pile_changed[pile] = 0;
        return;
    }
    if (game.disable[pile])	/* don't draw THIS pile */
	return;
    if (NOT_DISPLAYED(geo.pg+pile))
	return;			/* draw nothing */
    
    cx = p->x + p->ox;		/* card position of lowest card */
    cy = p->y + p->oy;
    if (EMPTY(pile)) {		/* draw empty pile */
	int c;
	XClearArea(dpy, table, p->x, p->y, p->w, p->h, False);
	switch (game.piletype[pile]) {
	case Stack:
	    c = SUITSYMBOL + SUIT(pile);
	    break;
	default:
	    c = OUTLINE;
	    break;
	}
	PaintCard(cx, cy, c, 0, 0);
	return;
    }
    if (!p->cdx && !p->cdy) {	/* only topmost card is visible */
	Cardindex c;
	c = INDEX_OF_LAST_CARD(pile);
	PaintCard(cx, cy, game.visible[c] ? game.cards[c] : CARDBACK, 0, 0);
    } else {
	if (pile_resize(pile))	/* delta changed => complete redraw */
	    delta = 0;
	
	if ((p->cdx < 0 || p->cdy < 0) && delta < 0)
	    /* this does not work correctly yet. simply avoid the case */
	    delta = 0;
	
	if (delta < 0) {	/* cards were removed. Clear area and redraw top */
	    int x, y;
	    if (p->cdx) {
		x = (CARDS_ON_PILE(pile)-1) * p->cdx + geo.cw - geo.rx;
		y = (CARDS_ON_PILE(pile)-1) * p->cdy;
		XClearArea(dpy, table, p->x+x, p->y+y, p->w-x, p->h-y, False);
	    }
	    if (p->cdy) {
		x = (CARDS_ON_PILE(pile)-1) * p->cdx;
		y = (CARDS_ON_PILE(pile)-1) * p->cdy + geo.cw - geo.rx;
		XClearArea(dpy, table, p->x+x, p->y+y, p->w-x, p->h-y, False);
	    }
	    delta = 1;	/* only last card is to be drawn new */
	} else if (!delta) {	/* draw complete pile */
	    XClearArea(dpy, table, p->x, p->y, p->w, p->h, False);
	    delta = CARDS_ON_PILE(pile);
	}
	/* (delta > 0) */
	/* draw last cards */
	{   Cardindex c = INDEX_OF_LAST_CARD(pile) + 1 - delta;
	    int i = c - INDEX_OF_FIRST_CARD(pile); 
/*	    printf("Drawing %d cards on slot %d: d=%d,%d\n",
		   delta, pile, p->cdx, p->cdy); */
	    while (--delta >= 0) {
		int pw, ph;	/* paint-width and height */
		pw = geo.cw;
		ph = geo.ch;
		if (delta) {
		    /* Not the last card. May use card clipping optimisation */
		    if (p->cdx == 0 && p->cdy > 0)
			ph = p->cdy + geo.ry;
		    if (p->cdy == 0 && p->cdx > 0)
			pw = p->cdx + geo.rx;
		}
		PaintCard(cx + p->cdx*i,
			  cy + p->cdy*i,
			  (game.visible[c] ? game.cards[c] : CARDBACK),
			  pw, ph);
		++c;
		++i;
	    }
	}
    }
    if (game.srcind >= 0 && getpile(game.srcind) == pile)
	show_mark(True);
}
