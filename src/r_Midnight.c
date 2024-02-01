/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module r_Midnight.c			     */
/*									     */
/*	Characteristics of the ``Midnight Oil'' rules			     */
/*	written by Michael Bischoff (mbi@mo.math.nat.tu-bs.de)		     */
/*	04-Apr-1994							     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#include "xpatgame.h"

/* won't work with facedown > 0 */

static int MO_new_cards(void) {
    return rules.param[1] > game.counter[1];
}


/* shuffle the cards */
static Move MO_DealCards(void) {
    int remgraphic;
    int cardsperpile = rules.faceup + rules.facedown;
    Pileindex i;
    int remember_count = game.n_moves;

    assert(rules.param[1] > game.counter[1]);
    ++game.counter[1];

    /* we are moving a lot, so keep the graphics for later */
    if ((remgraphic = game.graphic))
	graphics_control(Disable);
    store_move(COMPOUND_BEGIN);

    /* first, we put all cards on the first slot */
    /* this won't move any game.*/
    for (i = FIRST_SLOT+1; i <= LAST_SLOT; ++i)
	if (!EMPTY(i))
	    store_move(do_move(INDEX_OF_FIRST_CARD(i), FIRST_SLOT));
    /* now, we redistribute the cards on the slots */
    /* again, this won't move any game.*/
    for (i = FIRST_SLOT; i <= LAST_SLOT; ++i)
	if (CARDS_ON_PILE(i) > cardsperpile)
	    store_move(do_move(INDEX_OF_FIRST_CARD(i)+cardsperpile, i+1));
	else
	    break;
    /* now, shuffle the cards */
    store_move(SlotShuffle(1));
    if (remgraphic)
	graphics_control(EnableAndRedraw);
    game.n_moves = remember_count;
    return COMPOUND_END;
}

#include "xpatgeo.h"

static int MO_Layout(void) {
    int i, y, x;
    struct pilegeometry *p = geo.pg;

    y = geo.dy;
    x = geo.dx;

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
    if (rules.numslots & 1)
	/* correctly advance x position */
	x += geo.dx + geo.cw;

    p = geo.pg+FIRST_STACK;
    for (i = 0; i < rules.numstacks; ++i) {
	p->x = x;
	p->y = y + (i & 3) * (geo.dy + geo.ch);
	if ((i&3) == 3)
	    x += geo.cw + geo.dx;
	++p;
    }
    return MIDNIGHTOIL_MAGIC;
}

struct rules MidnightOil_rules = {
    "Midnight Oil",/* shortname */
    NULL,	/* longname */
    "mo",       /* abbrev */
    4,		/* layout_hints */
    0,		/* variant (DECK_SOURCE) */
    CUSTOM_PARAM1|CUSTOM_PARAM3,/* customizable */
    0,		/* customized */
    52,		/* numcards */
    4,		/* numstacks */
    18,		/* numslots */
    0,		/* numtmps */
    1,		/* numdecks */
    13,		/* cards_per_color */
    0,		/* numjokers */
    {0, 2, 0, 1},/* param[1], param[2], param[3] */
    0,		/* facedown */
    3,		/* faceup */
    SEQUENTIAL,	/* newgame_bits */
    NULL,	/* new_game */
    NULL,	/* game_won */
    MO_new_cards,/* new_cards */
    ES_NONE|US_RS|MG_NONE|DC_ALWAYS|ST_ONE, /* move_bits */
    MO_DealCards,/* deal_cards */
    NULL,	/* undeal_cards */
    NULL,	/* stackable */
    NULL,	/* movevalid */
    NULL,	/* valid */
    NULL,	/* relaxed_valid */
    NULL,	/* good_hint */
    NULL,	/* automove */
    NULL,	/* score */
    0,		/* maxscore */
    {0, TXTI_SHUFFLE,/* paramstring 0, 1 */
    0, TXTI_ROTATE},/* paramstring 2,3 */
    0,		/* used */
    NULL,	/* initfunc */
    NULL,	/* local keyboard bindings */
    NULL, MO_Layout
};
