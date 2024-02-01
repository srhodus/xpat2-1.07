/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module r_Oonsoo.c			     */
/*						       			     */
/*	Characteristics of the ``Oonsoo'' rules				     */
/*	by Bradford W. Mott (bwmott@eos.ncsu.edu)			     */
/*	written by Michael Bischoff					     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#include "xpatgame.h"

static int Oonsoo_valid(int srccard, int dstcard) {
    if (RANK(srccard) != RANK(dstcard))
	return 0;
    return SUIT(srccard) > SUIT(dstcard);
}

static int Oonsoo_won(void) {
    Pileindex i;
    for (i = FIRST_SLOT; i <= LAST_SLOT; ++i)
	if (CARDS_ON_PILE(i) != 4 ||
	    slotsequence(i, INDEX_OF_LAST_CARD(i), 0) !=
	    INDEX_OF_FIRST_CARD(i))
	    return 0;
    return 1;
}

#include "xpatgeo.h"

static int Oonsoo_Layout(void) {
    int i, y, x;
    struct pilegeometry *p = geo.pg;

    for (i = 0; i < game.numpiles; ++i) {
	p = geo.pg+i;
	p->x = -1;
	p->y = -1;
    }


    y = geo.dy;
    x = 2 * geo.dx + geo.cw;

    p = geo.pg+FIRST_SLOT;
    for (i = 0; i < rules.numslots; ++i) {
	p->x = x;
	p->y = y;
	p->h = 2 * geo.ch + geo.dy;
	if (i & 1) {
	    p->y += p->h + geo.dy;
	    x += geo.cw + geo.dx;
	}
	++p;
    }
    p = geo.pg+IDECK;
    p->x = geo.dx;
    p->y = geo.dy + geo.ch + geo.dy;
    return OONSOO_MAGIC;
}

struct rules Oonsoo_rules = {
    "Oonsoo",	/* shortname */
    NULL,	/* longname */
    "oonsoo",	/* abbrev */
    9,		/* layout_hints */
    0,		/* variant */
    0,		/* customizable */
    0,		/* customized */
    48,		/* numcards */
    0,		/* numstacks */
    12,		/* numslots */
    0,		/* numtmps */
    1,		/* numdecks */
    12,		/* cards_per_color */
    0,		/* numjokers */
    {0, 0, 0, 0},/* param[0], param[1], param[2], param[3] */
    1,		/* facedown */
    1,		/* faceup */
    0,		/* newgame_bits */
    NULL,	/* new_game */
    Oonsoo_won,	/* game_won */
    NULL,	/* new_cards */
    ES_CLUBS | ST_NONE | DC_ALWAYS,/* every card to empty stack, no card to stack */
    NULL,	/* deal_cards */
    NULL,	/* undeal_cards */
    NULL,	/* stackable */
    NULL,	/* movevalid */
    Oonsoo_valid,/* valid */
    Oonsoo_valid,/* relaxed_valid */
    NULL,	/* good_hint */
    NULL,	/* automove */
    NULL,	/* score */
    0,		/* maxscore */
    {0, 0, 0, 0}, /* paramstring blocks */
    0,		/* used */
    NULL,	/* initfunc */
    NULL,	/* local keyboard bindings */
    NULL, Oonsoo_Layout
};
