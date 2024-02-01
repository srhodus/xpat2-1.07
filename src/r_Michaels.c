/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module r_Michaels.c			     */
/*									     */
/*	Characteristics of the ``Michael's Fantasy'' rules		     */
/*	written by Michael Bischoff					     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#include "xpatgame.h"

#include "xpatgeo.h"

static int Michaels_Layout(void) {
    int i, j, y, x = geo.dx;
    struct pilegeometry *p = geo.pg;

    for (i = 0; i < game.numpiles; ++i) {
	p = geo.pg+i;
	p->x = -1;
	p->y = -1;
    }
    y = geo.dy;
    /* first the slots */
    for (i = FIRST_SLOT; i <= LAST_SLOT; ++i) {
	if (i == FIRST_SLOT+rules.numslots/2)
	    x += 5 * geo.dx + 3 * geo.cw;
	p = geo.pg+i;
	p->x = x;
	p->y = y;
	x += geo.dx + geo.cw;
	p->h = geo.h - geo.dy + BOTTOM_INC;
    }
    /* now the tmps */
    x = 2 * geo.dx + rules.numslots/2 * (geo.cw + geo.dx);
    for (j = 0; j < rules.numtmps; ++j) {
	p = geo.pg+i+j;
	p->x = x + ((j & 2) ? 2 * (geo.dx + geo.cw) : 0);
	p->y = y + ((j & 1) ? 2 * (geo.dy + geo.ch) : 0);
    }
    /* at last the stacks */
    for (i = FIRST_STACK; i <= LAST_STACK; ++i) {
	static int xoff[] = { 0, 1, 1, 2 };
	static int yoff[] = { 2, 1, 3, 2 };
	p = geo.pg+i;
	p->x = x + xoff[i] * (geo.cw + geo.dx);
	p->y = y + (yoff[i] * (geo.ch + geo.dy)) / 2;
    }
    return MICHAELS_MAGIC;
}

struct rules Michaels_rules = {
    "Michael's Fantasy",/* shortname */
    NULL,	/* longname */
    "mf",       /* abbrev */
    5,		/* layout_hints */
    NODEAL,	/* variant */
    CUSTOM_PARAM3|CUSTOM_FACEUP|CUSTOM_FACEDOWN|CUSTOM_SLOTS,/* customizable */
    0,		/* customized */
    52,		/* numcards */
    4,		/* numstacks */
    6,		/* numslots */
    4,		/* numtmps */
    1,		/* numdecks */
    13,		/* cards_per_color */
    0,		/* numjokers */
    {0, 0, 0, 5},/* param[0], param[1], param[2], param[3] */
    3,		/* facedown */
    5,		/* faceup */
    FORCE_SLOTS,/* newgame_bits */
    NULL,	/* new_game */
    NULL,	/* game_won */
    NULL,	/* new_cards */
    ES_ALL|US_RA|MG_RA|DC_ALWAYS|ST_ONE|STACK_SOURCE, /* move_bits */
    NULL,	/* deal_cards */
    NULL,	/* undeal_cards */
    NULL,	/* stackable */
    NULL,	/* movevalid */
    NULL,	/* valid */
    NULL,	/* relaxed_valid */
    std_good_hint,/* good_hint */
    NULL,	/* automove */
    NULL,	/* score */
    0,		/* maxscore */
    {0, 0, 0, TXTI_ROTATE}, /* paramstring blocks */
    0,		/* used */
    NULL,	/* initfunc */
    NULL,	/* local keyboard bindings */
    NULL, Michaels_Layout
};
