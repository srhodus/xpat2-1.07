/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module r_BlueMoon.c			     */
/*									     */
/*	Characteristics of the ``Blue Moon'' rules			     */
/*	attempted to be written by Willem Monsuwe			     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#include "xpatgame.h"

#define ROWS (rules.numstacks)
#define COLUMNS (rules.cards_per_color + 1)
#define ROW(r) (FIRST_SLOT + ((r) * COLUMNS))
#define CARD(s) (game.cards[game.ind[(s)]])

/* No limit */
static int
BM_new_cards(void)
{
    return 1;
}

static void
BM_new_game(void)
{
    Pileindex s;
    int r;

    /* all cards visible */
    for (r = 0; r < rules.numcards; r++)
	game.visible[r] = 1;

    /* one card on every slot, except the first slot of every column */
    for (r = 0; r < ROWS; r++)
    {
	s = ROW(r);
	game.ind[s+1] = game.ind[s];
	while (++s < ROW(r + 1))
	{
	    game.ind[s+1] = game.ind[s] + 1;
	}
    }
    game.ind[IDECK+1] = rules.numcards;

    /* Move aces to the first slots */
    for (r = 0; r < ROWS; r++)
    {
	/* Look for the next ace */
	for (s = FIRST_SLOT;; s++)
	{
	    assert(s <= LAST_SLOT);
	    if (EMPTY(s))
		continue;
	    if ((RANK(CARD(s)) == Ace) && ((s - FIRST_SLOT) % COLUMNS))
		break;
	}

	/* Move it to the empty slot */
	do_move(game.ind[s], ROW(r));
    }
}

static Move
BM_deal_cards(void)
{
    Pileindex s = 0;	/* keep compiler happy */
    int i, r, remgraphic;
    int remember_count = game.n_moves;

    /* we are moving a lot, so keep the graphics for later */
    if ((remgraphic = game.graphic))
	graphics_control(Disable);
    store_move(COMPOUND_BEGIN);

    /* Remove cards that are 'in sequence' to the stack */
    for (r = 0; r < ROWS; r++)
    {
	for (s = ROW(r);;)
	{
	    assert(s < ROW(r + 1));
	    store_move(do_move(game.ind[s], STACK(r)));
	    s++;
	    if (EMPTY(s))
		break;
	    if (SUIT(game.cards[INDEX_OF_LAST_CARD(STACK(r))]) != SUIT(CARD(s)))
		break;
	    if (RANK(game.cards[INDEX_OF_LAST_CARD(STACK(r))]) != (RANK(CARD(s)) - 1))
		break;
	}
    }

    /* redistribute the empty spaces to the beginning of each row */
    for (r = 0; r < ROWS; r++)
    {
	if (EMPTY(ROW(r) + CARDS_ON_PILE(STACK(r))))
	    continue;
	/* Find an empty space */
	for (i = 0; i < ROWS; i++)
	{
	    for (s = ROW(i) + CARDS_ON_PILE(STACK(i)) + 1; s < ROW(i + 1); s++)
	    {
		if (EMPTY(s))
		{
		    i = ROWS;
		    break;
		}
	    }
	}
	assert(EMPTY(s));
	store_move(do_move(game.ind[ROW(r) + CARDS_ON_PILE(STACK(r))], s));
    }
    store_move(SlotShuffle(1));
    store_move(ADD_CHEAT | 1);

    /* Restore the cards from the stacks to the slots */
    for (r = 0; r < ROWS; r++)
	for (s = ROW(r) + CARDS_ON_PILE(STACK(r)); --s >= ROW(r); )
	    store_move(do_move(INDEX_OF_LAST_CARD(STACK(r)), s));

    if (remgraphic)
	graphics_control(EnableAndRedraw);
    
    game.counter[1]++;

    game.n_moves = remember_count;
    return COMPOUND_END;
}

static int
BM_move_valid(Cardindex src, Pileindex dstpile)
{
    Pileindex srcpile = getpile(src);

    /* Only move a card to an empty slot whose left 
     * neighbour is of the same sout and the next lower in rank */
    if (EMPTY(srcpile) || !EMPTY(dstpile) || EMPTY(dstpile - 1))
	return 0;
    if (game.piletype[srcpile] != Slot || game.piletype[dstpile] != Slot)
	return 0;
    
    if (SUIT(CARD(dstpile - 1)) != SUIT(CARD(srcpile)))
	return 0;
    return ((RANK(CARD(dstpile - 1)) + 1) == RANK(CARD(srcpile)));
}

static int
BM_good_hint(Cardindex src, Pileindex dstpile)
{
    int r, v = 100;
    Pileindex s;

    r = ((dstpile - FIRST_SLOT) / COLUMNS);

    /* Sequencing after an ace is very good */
    for (s = ROW(r); ++s; )
    {
	assert(s < ROW(r + 1));
	if (s == dstpile)
	    v += 50;
	if (EMPTY(s))
	    break;
	if (SUIT(CARD(s)) != SUIT(CARD(s - 1)))
	    break;
	if ((RANK(CARD(s)) - 1) != RANK(CARD(s - 1)))
	    break;
    }

    /* An empty space to the right of a king is useless */
    if (RANK(CARD(dstpile - 1)) == King)
	v -= 20;
    if (((RANK(game.cards[src])) == King)
	    && (((dstpile + 1) - FIRST_SLOT) % COLUMNS)
	    && EMPTY(dstpile + 1))
	v -= 20;

    return v;
}

static int
BM_game_won(void)
{
    int r;
    Pileindex s;

    for (r = 0; r < ROWS; r++)
    {
	for (s = ROW(r); s++; )
	{
	    assert(s < ROW(r + 1));
	    if (EMPTY(s))
		break;
	    if (SUIT(CARD(s)) != SUIT(CARD(s - 1)))
		break;
	    if ((RANK(CARD(s)) - 1) != RANK(CARD(s - 1)))
		break;
	}
	if ((s + 1) != ROW(r + 1))
	    return 0;
    }
    return 1;
}

/* Scoring for Blue Moon, just guessed something.. */
static int
BM_score(void)
{
    int r, v;
    Pileindex s;

    /* Ten points penalty for every deal */
    v = -10 * game.counter[1];

    for (r = 0; r < ROWS; r++)
    {
	/* Two points for every card sequenced after an ace */
	for (s = ROW(r); s++; v += 2)
	{
	    assert(s < ROW(r + 1));
	    if (EMPTY(s))
		break;
	    if (SUIT(CARD(s)) != SUIT(CARD(s - 1)))
		break;
	    if ((RANK(CARD(s)) - 1) != RANK(CARD(s - 1)))
		break;
	}
	/* Plus 1 makes it 25 for a complete row. */
	if ((s + 1) == ROW(r + 1))
	    v++;
    }
    return v;
}

#include "xpatgeo.h"

static int BM_Layout(void) {
    int i, y, x;
    struct pilegeometry *p = geo.pg;

    y = geo.dy;
    p = geo.pg+FIRST_SLOT;
    x = geo.dx;
    for (i = 0; i < rules.numslots; ++i) {
	p->x = x + (i%14) * (geo.cw + geo.dx);
	p->y = y + (i/14) * (geo.ch + geo.dy);
	p->dx = 0;
	p->dy = 0;
	++p;
    }
    return BLUEMOON_MAGIC;
}

struct rules BlueMoon_rules = {
    "Blue Moon",	/* shortname */
    NULL,	/* longname */
    "bm",       /* abbrev */
    10,		/* layout_hints */
    0,		/* variant */
    0,		/* customizable */
    0,		/* customized */
    52,		/* numcards */
    4,		/* numstacks */
    56,		/* numslots */
    0,		/* numtmps */
    1,		/* numdecks */
    13,		/* cards_per_color */
    0,		/* numjokers */
    {0, 0, 0, 0},/* param[0], param[1], param[2], param[3] */
    0,		/* facedown */
    1,		/* faceup */
    0,		/* newgame_bits */
    BM_new_game,	/* new_game */
    BM_game_won,	/* game_won */
    BM_new_cards,	/* new_cards */
    ES_NONE,		/* move_bits */
    BM_deal_cards,	/* deal_cards */
    NULL,	/* undeal_cards */
    NULL,	/* stackable */
    BM_move_valid,	/* movevalid */
    NULL,	/* valid */
    NULL,	/* relaxed_valid */
    BM_good_hint,	/* good_hint */
    NULL,	/* automove */
    BM_score,	/* score */
    100,		/* maxscore */
    {0, 0, 0, 0}, /* paramstring blocks */
    0,		/* used */
    NULL,	/* initfunc */
    NULL,	/* local keyboard bindings */
    NULL, BM_Layout
};
