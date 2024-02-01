/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module X-expose.c			     */
/*									     */
/*	Routines for marking exposed cards				     */
/*	written by Heiko Eissfeldt and Michael Bischoff			     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#include "X-pat.h"

static int rem_x = -1, rem_y = -1;
static Pixmap exp_bkp = 0;


static void hide_exposed_card(void) {
    if (rem_x < 0 || rem_y < 0)
	return;
    XCopyArea(dpy, exp_bkp, table, whitegc, 0, 0,
	      CARD_WIDTH, CARD_HEIGHT,
	      rem_x, rem_y);
    rem_x = rem_y = -1;
    graphic.zoomed_card = -1;
}

void show_exposed_card(boolean on) {
    if (graphic.zoomed_card < 0)
	return;
    if (!exp_bkp)
	exp_bkp = XCreatePixmap(dpy, table, CARD_WIDTH, CARD_HEIGHT,
			    DefaultDepth(dpy, screen));
    if (on) {
        struct pilegeometry *p;
	Cardindex ind;
	int num;
	ind = graphic.zoomed_card;
	p = geo.pg + getpile(ind);
	num = ind - INDEX_OF_FIRST_CARD(getpile(ind));
	rem_x = p->x + p->ox + p->cdx * num;
	rem_y = p->y + p->oy + p->cdy * num;
	/* save bk */
	XCopyArea(dpy, table, exp_bkp, whitegc, rem_x, rem_y,
		  CARD_WIDTH, CARD_HEIGHT, 0, 0);
	/* expose card */
	PaintCard(rem_x, rem_y,
		  (game.visible[ind] ? game.cards[ind] : CARDBACK), 0, 0);
    } else {
	hide_exposed_card();
    }
}
