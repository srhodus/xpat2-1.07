/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module r_Royal.c			     */
/*									     */
/*	Characteristics of the ``Royal Cotillion'' rules		     */
/*	written by Michael Bischoff (mbi@mo.math.nat.tu-bs.de)		     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#include "xpatgame.h"

static int Royal_valid(Cardindex srcind, Pileindex dstpile) {
    int srcpile, dstcard, srccard;

    srcpile = getpile(srcind);
    if (srcpile == dstpile)
	return 0;
    if (game.piletype[srcpile] == Stack)
	return 0;
    dstcard = EMPTY(dstpile) ? -1 : game.cards[game.ind[dstpile+1]-1];
    srccard = game.cards[srcind];
    switch (game.piletype[dstpile]) {
    case Slot:	/* moves to Slot not allowed */
    case Tmp:
    case FacedownDeck:
	return 0;
    case FaceupDeck:
	return game.piletype[srcpile] == FacedownDeck;
    case Stack:
	if (srcind != INDEX_OF_LAST_CARD(srcpile) || CARDS_ON_PILE(dstpile) == 13)
	    return 0;	/* only one card at a time, no overfull stacks */
	if (SUIT(srccard) != SUIT(dstpile))
	    return 0;
	if (EMPTY(dstpile))
	    return RANK(srccard) == dstpile/4;
	return RANK(srccard) == (2 + RANK(
		  game.cards[INDEX_OF_LAST_CARD(dstpile)])) % 13;
    }
    return 0;
}

static void Royal_newgame(void) {
    int i;
    /* specific part: one card on a stack, 3 on the talon (VDECK) */
    for (i = 0; i < rules.numcards; ++i)
	game.visible[i] = 1;			/* TODO */
    for (i = 0; i <= rules.numstacks; ++i)
	game.ind[i] = 0;
    for (i = 0; i < rules.numslots; ++i)
	game.ind[FIRST_SLOT+i+1] = (i+1) * (rules.faceup+rules.facedown);
    for (i = LAST_SLOT+1; i < IDECK; ++i)
	game.ind[i+1] = game.ind[i] + 1;	/* one card each tmp */
    game.ind[IDECK+1] = rules.numcards;
}

static void Royal_minwindow(int w, int h, int dx, int dy, int *x, int *y) {
    /* No deck, 4 stacks, 4 Tmps, the slots */
    int min1 = max(2, rules.numslots) + rules.numdecks + (rules.numtmps+3)/4;

    *x = 3 * dx + min1 * (w + dx);
    *y = 4 * h + 5 * dy;
}

#include "xpatgeo.h"


static int Royal_Layout(void) {
    int i, x = geo.dx;
    struct pilegeometry *p = geo.pg;

    if (rules.numslots > 2)
	x += (rules.numslots - 2) * (geo.cw+geo.dx) / 2;
    p = geo.pg + IDECK;
    p->x = x;
    p->y = geo.dy;
    --p;	/* VDECK */
    p->x = x + geo.dx + geo.cw;
    p->y = geo.dy;
    x = geo.dx;
    for (i = FIRST_SLOT; i <= LAST_SLOT; ++i) {
	p = geo.pg+i;
	p->x = x;
	p->y = geo.dy + geo.ch + geo.dy;
	x += geo.dx + geo.cw;
	p->h = 3 * geo.ch + 2 * geo.dy;
    }
    x = 2 * geo.dx + max(rules.numslots, 2) * (geo.cw + geo.dx);
    for (i = FIRST_STACK; i <= LAST_STACK; ++i) {
	p = geo.pg+i;
	p->x = x + (i / 4) * (geo.cw + geo.dx);
	p->y = geo.dy + (i & 3) * (geo.ch + geo.dy);
    }
    x += rules.numdecks * (geo.dx + geo.cw) + geo.dx;
    for (i = 0; i < rules.numtmps; ++i) {
	p = geo.pg+LAST_SLOT+1+i;
	p->x = x + (i / 4) * (geo.cw + geo.dx);
	p->y = geo.dy + (i & 3) * (geo.ch + geo.dy);
    }
    return ROYAL_MAGIC;
}

struct rules Royal_rules = {
    "Royal Cotillion",	/* shortname */
    NULL,	/* longname */
    "rc",       /* abbrev */
    6,		/* layout_hints */
    DECK_SOURCE|DECK_VISIBLE|STACKS_MULTI|AUTOFILL_TMPS|KLONDIKE_DEAL,/* variant */
    CUSTOM_SLOTS|CUSTOM_TMPS|CUSTOM_FACEUP|CUSTOM_FACEDOWN,	/* customizable */
    0,		/* customized */
    104,	/* numcards */
    8,		/* numstacks */
    3,		/* numslots */
    12,		/* numtmps */
    2,		/* numdecks */
    13,		/* cards_per_color */
    0,		/* numjokers */
    {0, 0, 1, 0},/* param[0], param[1], param[2], param[3] */
    0,		/* facedown */
    3,		/* faceup */
    0,		/* newgame_bits */
    Royal_newgame,/* new_game */
    NULL,	/* game_won */
    NULL,	/* new_cards */
    ES_NONE|US_NONE|MG_NONE|ST_ONE|DC_ALWAYS, /* move_bits */
    NULL,	/* deal_cards */
    NULL,	/* undeal_cards */
    NULL,	/* stackable */
    Royal_valid,/* movevalid */
    NULL,	/* valid */
    NULL,	/* relaxed_valid */
    NULL,	/* good_hint */
    NULL,	/* automove */
    NULL,	/* score */
    0,		/* maxscore */
    {0, 0, 0, 0}, /* paramstring blocks */
    0,		/* used */
    NULL,	/* initfunc */
    NULL,	/* local keyboard bindings */
    Royal_minwindow, Royal_Layout
};
