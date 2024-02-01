#include "xpatgame.h"
#include "xpatgeo.h"

struct geometry geo = { 0 };

/* return the cardindex of the card displayed at the mouse position.
   return -1 if the pile in empty
   return -2 if the pile is not empty, but the user missed any card

   on entry, (mx, my) are the mouse coordinates relative to the pile */

Cardindex FindCardOfMousePos(Pileindex pileno, int mx, int my) {
    Cardindex c;
    int cx, cy;
    if (!EMPTY(pileno)) {
	/* find topmost card on which we clicked */
	int i;
	struct pilegeometry *p = geo.pg + pileno;
	c = INDEX_OF_LAST_CARD(pileno);
	i = CARDS_ON_PILE(pileno);
	while (i-- > 0) {
	    cx = p->ox + p->cdx * i;
	    cy = p->oy + p->cdy * i;
	    
	    if (mx >= cx && mx < cx + geo.cw && my >= cy && my < cy + geo.ch) {
		/* found card on which we clicked */
		break;
	    }
	    --c;
	}
	if (i < 0)
	    c = -2;	/* error */
    } else {
	c = -1;		/* empty */
    }
    return c;
}

int pile_resize(Pileindex pileno) {
    int new_dx = 32767, new_dy = 32767;
    int cards_on_pile = CARDS_ON_PILE(pileno);
    struct pilegeometry *p = geo.pg + pileno;

    if (game.piletype[pileno] != Slot) {
	p->cdx = 0;
	p->cdy = 0;
	return 0;
    }

    if (cards_on_pile) {
	new_dx = (p->w - geo.cw) / cards_on_pile;
	new_dy = (p->h - geo.ch) / cards_on_pile;
    }
    if (!new_dx) new_dx = 1;	/* at least one pixel ? */
    if (!new_dy) new_dy = 1;
    if (p->dx >= 0) {
	if (new_dx > p->dx)		/* maximum distance */
	    new_dx = p->dx;
    } else {
	if (new_dx > -p->dx)		/* maximum distance */
	    new_dx = -p->dx;
	new_dx = -new_dx;
    }
    if (p->dy >= 0) {
	if (new_dy > p->dy)		/* maximum distance */
	    new_dy = p->dy;
    } else {
	if (new_dy > -p->dy)		/* maximum distance */
	    new_dy = -p->dy;
	new_dy = -new_dy;
    }

    if (new_dx != p->cdx || new_dy != p->cdy) {
	/* a change has occured */
        p->cdx = new_dx;
	p->cdy = new_dy;
	return 1;			/* indicate change */
    }
    return 0;				/* nothing is different */
}

/* list of directions for the star layout (counting clockwise) */
static int dxtab[8] = {  1,  1,  1,  0, -1, -1, -1,  0 };
static int dytab[8] = { -1,  0,  1,  1,  1,  0, -1, -1 };

void indep_generic_minwindow(int *xcards, int *xgaps,
			     int *ycards, int *ygaps) {
    int min1;

    switch (rules.layout_hints) {
    case 0:
	if (!rules.numtmps) {
	    int area1, area2;
	    if (rules.numstacks > rules.numslots)
		min1 = rules.numstacks;
	    else if (rules.numstacks == rules.numslots)
		min1 = rules.numstacks + (rules.variant & DECK_SOURCE ? 1 : 0);
	    else  /* stacks < slots */ if (rules.variant & DECK_SOURCE)
		min1 = max(rules.numstacks+2, rules.numslots);
	    else
		min1 = rules.numslots;
	    
	    /* stacks on the top */
	    *xcards = min1;
	    *ycards = SLOTFACTOR + 1;
	    area1 = min1 * (SLOTFACTOR + 1);

	    /* second variant is with stacks on the right side */
	    min1 = rules.numslots + rules.numdecks;
	    if (rules.variant & DECK_SOURCE)
		++min1;
	    area2 = min1 * 4;

	    /* as a selection rule, minimize the size of the window needed */
	    if (area2 < area1) {
		/* stacks on the right side */
		*xcards = min1;
		*ycards = 4;
	    }
	    break;
	}
	/* else fall thru to SeaHaven type */
    case 1:
	*xcards = max(rules.numslots, rules.numstacks + rules.numtmps);
	*ycards = SLOTFACTOR+1;
	break;
    case 2:
	/* The deck, the stack, the slots */
	*xcards = rules.numslots + 1;
	*ycards = SLOTFACTOR+1;
	break;
    /* case 3:	Monte Carlo is EXTERNAL */
    case 9:	/* Oonsoo: a deck and twelve slots */
    case 4:	/* Midnight Oil: 18 Slots */
	*xcards = rules.numslots/2 + rules.numdecks;
	*ycards = 4;
	break;
    case 5:	/* Michael's Fantasy */
	/* No deck, 4 stacks, 4 Tmps, the slots */
	*xcards = 3 + rules.numslots;
	*ycards = max(3, SLOTFACTOR);
	*xgaps = *xcards + 3;	/* 2 extra gaps */
	*ygaps = *ycards + 1;
	return;
    /* case 6: Royal Cotillion is EXTERNAL */
    case 7:	/* Baker's Dozen */
	/* No deck, 4 stacks, a dozen slots */
	min1 = rules.numdecks + (rules.numslots+1)/2;
	*xcards = min1;
	*ycards = 4;
	break;
    case 8:	/* Canfield */
	/* No deck, 4 stacks, a dozen slots */
	*xcards = 5;
	*ycards = 4;
	break;
    case 10:	/* Blue Moon */
	*xcards = 14;
	*ycards = 4;
	break;
    }
    /* default gap count: */
    *xgaps = *xcards + 1;
    *ygaps = *ycards + 1;
}

static int gen_low_layout(void) {
    struct pilegeometry *p = geo.pg;
    int i, off;
    int new_layout_type = -1;
    int cols, rows = 1 + SLOTFACTOR;
    int xnum = (geo.w - geo.dx) / (geo.cw + geo.dx);

/*    printf("generating low layout for %d,%d\n", geo.w, geo.h); */

    if (rules.numstacks > rules.numslots) {
	new_layout_type = 2;
	cols = rules.numstacks;
    } else if (rules.numstacks == rules.numslots) {
	if (rules.variant & DECK_SOURCE) {
	    new_layout_type = 5;
	    cols = rules.numstacks + 1;
	} else {
	    new_layout_type = 4; /* only case without a deck */
	    cols = rules.numstacks;
/*	    printf("xnum = %d, cols = %d\n", xnum, cols); */
	    if (xnum >= cols + 1) { /* have a deck anyway */
		++cols;
		++new_layout_type;	
	    }
	}
    } else {
	new_layout_type = 6;
	if (rules.variant & DECK_SOURCE)
	    cols = max(rules.numstacks + 2, rules.numslots);
	else
	    cols = rules.numslots;
    }
    
    off = cols - rules.numstacks;
    for (i = 0; i < rules.numstacks; ++i) {
	p->x = geo.dx + (geo.dx + geo.cw) * (i+off);
	p->y = geo.dy;
	++p;
    }
    off = cols - rules.numslots;
    for (i = 0; i < rules.numslots; ++i) {
	p->x = geo.dx + (geo.dx + geo.cw) * (i+off);
	p->y = geo.dy + geo.dy + geo.ch;
	p->h = geo.h - 3 * geo.dy - geo.ch + BOTTOM_INC;
	++p;
    }
/*    printf("  did low layout with %5d cols\n", cols); */
    geo.preferred_width  = cols * (geo.dx + geo.cw) + geo.dx;
    geo.preferred_height = rows * (geo.dy + geo.ch) + geo.dy;

    if (!(rules.variant & NODEAL)) {
	switch (new_layout_type) {
	case 2: /* case 3: */
	    p->x = geo.dx;
	    p->y = geo.dy + geo.dy + geo.ch;
	    break;
	case 0:	case 4:
	    /* p->x = p->y = -1; */	/* no deck */
	    break;
	case 1: case 5:
	    p->x = geo.dx;
	    p->y = geo.dy + (geo.dy + geo.ch) / 2;
	    break;
	case 6: /* case 7: */
	    p->x = geo.dx;
	    p->y = geo.dy;
	    break;
	default:
	    fprintf(stderr, "xpat2: don't know where to place deck for layout type %d\n", new_layout_type);
	    abort();	/* some new layout? */
	}
    }
    /* do a second deck? */
    if (rules.variant & DECK_SOURCE) {
	p[1] = p[0];	/* IDECK is one more back */
	if (new_layout_type == 6) {
	    p->y = geo.dy;
	    p->x = 2 * geo.dx + geo.cw;
	} else {
	    p->x = geo.dx;
	    p->y = geo.dy + ((rules.variant & NODEAL) ? 1 : 3)
		* (geo.dy + geo.ch) / 2;
	}
    }
    return new_layout_type;
}

/* layout for standard game without Tmp piles */
/* this variant places the stacks of one deck in vertical direction */
static int gen_high_layout(void) {
    Pileindex i;
    struct pilegeometry *p = geo.pg;
    int rem_x, required;
    int cdx = geo.cw / 5, cdy = geo.ch / 5;
    int new_layout_type = GEN_BIG_LAYOUT_NO_DECK;
    /* int xnum = (geo.w - geo.dx) / (geo.cw + geo.dx); */

    rem_x = geo.w - geo.dx - rules.numdecks * (geo.cw + geo.dx);
    /* for all variants here, the stacks are at the same position */
    for (i = 0; i < rules.numstacks; ++i) {
	p->x = geo.dx + rem_x + (i / 4) * (geo.cw + geo.dx);
	p->y = geo.dy +         (i & 3) * (geo.ch + geo.dy);
	++p;
    }
    geo.preferred_width = (rules.numslots + rules.numdecks)
	* (geo.dx + geo.cw) + geo.dx; /* may be increased if deck visible */
    geo.preferred_height = 4 * (geo.dy + geo.ch) + geo.dy;

    required = rules.numslots + ((rules.variant & DECK_SOURCE) ? 1 : 0);
/*    printf("space for %d piles (%d needed)\n", rem_x / (geo.cw + geo.dx), required); */
    if (rem_x < required * (geo.cw + geo.dx)) {
	if (0 && rules.numslots == 8) {	/* disable star layout! */
	    /* generate a star layout */
	    int slw, slh, deckx, decky;
	    int num;
	    slw = (rem_x - geo.cw - 3 * geo.dx) / 2;
	    slh = (geo.h - geo.ch - 3 * geo.dy) / 2;
	    deckx = 2 * geo.dx + slw;
	    decky = 2 * geo.dy + slh;
	    num = (slh - geo.ch) / cdy;	/* number of cards to display before resize */
	    cdx = (slw - geo.cw) / num;	/* should be the same for x direction */
/*	    printf("generating star layout for %d,%d; deck at %d,%d, sls=%d,%d\n",
		   geo.w, geo.h, deckx, decky, slw, slh); */
	    
	    for (i = 0; i < rules.numslots; ++i) {
		p->w = slw;
		p->h = slh;
		p->x = deckx;
		p->y = decky;
		p->dx = dxtab[i] * cdx;
		p->dy = dytab[i] * cdy;
		/* Korrekturen */
		switch (dxtab[i]) {
		case 0:
		    p->w = geo.cw;
		    break;
		case 1:
		    p->x += geo.cw + geo.dx;
		    break;
		case -1:
		    p->x -= slw + geo.dx;
		    p->ox = slw - geo.cw;
		    break;
		}
		switch (dytab[i]) {
		case 0:
		    p->h = geo.ch;
		    break;
		case 1:
		    p->y += geo.ch + geo.dy;
		    break;
		case -1:
		    p->y -= slh + geo.dy;
		    p->oy = slh - geo.ch;
		    break;
		}
		/*	    printf("Slot %d at %3d,%3d o=%3d,%3d, d=%3d,%3d\n",
			    i, p->x, p->y, p->ox, p->oy, p->dx, p->dy); */
		++p;
	    }
	    p->x = deckx;
	    p->y = decky;
	    return GEN_BIG_STAR_LAYOUT;
	} else {	/* not enough, fall back to low res layout */
	    return gen_low_layout();
	}
    } else {
	/* enough space for the slots! */
	int currentx = geo.dx;
/*	printf("generating high layout for %d,%d\n", geo.w, geo.h); */
	if (rem_x >= (rules.numslots + 1) * (geo.cw + geo.dx) &&
	    !(rules.variant & NODEAL)) {
	    /* there is space for the deck, and we can use one! */
	    geo.pg[game.numpiles-1].x = geo.dx;
	    geo.pg[game.numpiles-1].y = geo.dy + geo.ch + geo.dy;
	    currentx += geo.cw + geo.dx;
	    new_layout_type = GEN_BIG_LAYOUT_WITH_DECK;
	    geo.preferred_width += geo.dx + geo.cw;
	}
	for (i = 0; i < rules.numslots; ++i) {
	    /* create slot of full window height */
	    p->x = currentx;
	    p->y = geo.dy;
	    p->h = geo.w - 2 * geo.dy + BOTTOM_INC;
	    currentx += geo.cw + geo.dx;
	    ++p;
	}
	/* redo pos. of stacks */
	p = geo.pg;
	for (i = 0; i < rules.numstacks; ++i) {
	    p->x = currentx + (i / 4) * (geo.cw + geo.dx);
	    p->y = geo.dy   + (i & 3) * (geo.ch + geo.dy);
	    ++p;
	}
    }
    return new_layout_type;
}


static int FreeCell_layout(void) {
    int i, cols, off;
    struct pilegeometry *p = geo.pg;

/*    printf("generating FreeCell layout for %d,%d\n", geo.w, geo.h); */
    cols = max(rules.numslots, rules.numstacks + rules.numtmps);

    off = cols - rules.numstacks;
    for (i = 0; i < rules.numstacks; ++i) {
	p->x = geo.dx + (geo.dx + geo.cw) * (i+off);
	p->y = geo.dy;
	++p;
    }
    off = cols - rules.numslots;
    for (i = 0; i < rules.numslots; ++i) {
	p->x = geo.dx + (geo.dx + geo.cw) * (i+off);
	p->y = 2 * geo.dy + geo.ch;
	p->h = geo.h - p->y - geo.dy + BOTTOM_INC;
	++p;
    }
    off = 0;
    for (i = 0; i < rules.numtmps; ++i) {
	p->x = geo.dx + (geo.dx + geo.cw) * (i+off);
	p->y = geo.dy;
	++p;
    }
    p->x = p->y = -1;		/* deck is invisible */
    geo.preferred_width  = (cols+1) * geo.dx + cols * geo.cw;
    geo.preferred_height = (1 + SLOTFACTOR) * (geo.dy + geo.ch) + geo.dy;
    return FREECELL_MAGIC;
}

/* set slot positions and sizes for a given Tableau size and card sizes */
/* geo.w and geo.h are guaranteed to be at least the minimum sizes */
int generate_layout(void) {
    /* assign defaults */
    Pileindex i;
    struct pilegeometry *p;
    int xnum, ynum, new_layout_type;

    for (i = 0; i < game.numpiles; ++i) {
	p = geo.pg+i;
	p->x = -1;
	p->y = -1;
	p->w = geo.cw;
	p->h = geo.ch;
	p->ox = 0;
	p->oy = 0;
	p->dx = 0;
	p->dy = game.piletype[i] == Slot ? geo.ch / 5 : 0;
	p->cdx = p->dx;
	p->cdy = p->dy;
    }

    /* the default is that there is only one layout per rule set,
       which is minsize and preferred size at the same time.
       So we set it here. It can be overridden by the special
       layout functions */
    geo.preferred_width = geo.min_width;
    geo.preferred_height = geo.min_height;
    xnum = (geo.w - geo.dx) / (geo.cw + geo.dx);
    ynum = (geo.h - geo.dy) / (geo.ch + geo.dy);

    if (rules.special_layout) {
	new_layout_type = (*rules.special_layout)();
    } else {
	/* compute number of cards in either direction with standard layout */
	
	switch (rules.layout_hints) {
	case 0:
	case 1:
	    new_layout_type = rules.numtmps ?
		FreeCell_layout() :
		    ynum >= 4 ?
			gen_high_layout() : gen_low_layout();
	    break;
	default:
	    new_layout_type = -1;
	}
    }
    /* provide size of largest slot */
    geo.lsw = geo.cw;
    geo.lsh = geo.ch;
    for (i = 0; i < game.numpiles; ++i) {
	p = geo.pg+i;
	if (!NOT_DISPLAYED(p)) {
	    if (p->w > geo.lsw)
		geo.lsw = p->w;
	    if (p->h > geo.lsh)
		geo.lsh = p->h;
	}
    }
/*    printf("layout done (type 0x%x), min=%d,%d, pref=%d,%d\n", new_layout_type,
	   geo.min_width, geo.min_height, geo.preferred_width, geo.preferred_height); */
    return new_layout_type;
}

void generic_minwindow(void) {
    int xcards, xgaps, ycards, ygaps;
    obtain_current_geometry();	/* update geo structure */
    if (rules.special_minwindow) {
	(*rules.special_minwindow)(geo.cw, geo.ch, geo.dx, geo.dy,
				   &geo.min_width, &geo.min_height);
    } else {
	indep_generic_minwindow(&xcards, &xgaps, &ycards, &ygaps);
	geo.min_width  = geo.dx * xgaps + geo.cw * xcards;
	geo.min_height = geo.dy * ygaps + geo.ch * ycards;
    }
/*    printf("==> generic minwindow = %d,%d\n", geo.min_width, geo.min_height); */
}
