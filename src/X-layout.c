/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module X-layout.c			     */
/*									     */
/*	Layout function for the X interface				     */
/*	written by Heiko Eissfeldt and Michael Bischoff			     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#include "X-pat.h"

#ifdef useXlib

int calc_yoff(int);

int arrange_buttons(struct singlebutton *b, int *startx, int *starty,
    XSize_t maxx, long *magic) {
    int x, y, num;
    long mask;
    /* printf("arrange width %d\n", maxx); */
    x = *startx;
    y = *starty;
    num = 0;
    *magic = 0;
    mask = 1L;
    while (b->text) {		/* weiterer button vorhanden */
	++num;
	b->x = x;
	b->y = y;
	b->w = 2 * button.bx + XTextWidth(button.font, b->text, strlen(b->text));
	b->h = 2 * button.by + button.fontheight;

	while (x > graphic.xgap && x + b->w + graphic.xgap >= maxx) {
	    /* line is full, next line */
	    *magic |= mask;
	    x = *startx;
	    y += 2 * button.by + button.fontheight + graphic.ygap;
	    b->x = x;
	    b->y = y;
	}
	mask <<= 1;
	x += b->w + graphic.xgap;
	++b;
    }
    *startx = x;
    *starty = y + 2 * button.by + button.fontheight + graphic.ygap;
    return num;
}

int calc_yoff(int w) {
    long dummy;
    int x, y;
    x = graphic.xgap;
    y = graphic.ygap;
    button.num = arrange_buttons(button.b, &x, &y, w, &dummy);
    graphic.buttons_height = y;
    graphic.message_x = 10;
    graphic.message_y = y + TABLE_BW + graphic.message_font->ascent;
    graphic.message_height = 2 * TABLE_BW +
	graphic.message_font->ascent + graphic.message_font->descent;
    return graphic.buttons_height + graphic.message_height;
}
#endif


void new_rules_coming(void) {
    /* no cleanup action necessary */
}

void new_rules_notify(void) {
    XSize_t w, h;
#ifdef useXview
    xv_set(mainwindow,
	   FRAME_LABEL, (rules.longname? rules.longname: rules.shortname),
	   0);
#else
    XStoreName(dpy, mainwindow, rules.longname ? rules.longname : rules.shortname);
#endif
    refresh_screen();		/* sometimes needed (at least if area is smaller) */
    
    /* compute minimum size */
    generic_minwindow();
#ifdef useXlib
    geo.min_height += calc_yoff(geo.min_width);
#endif
    w = geo.min_width;
    h = geo.min_height;
#ifdef LABER
    printf("min size set to %d, %d\n", w, h);
#endif
#ifdef useXlib
    {   XSizeHints xsh;
	xsh.flags = PMinSize;
	xsh.min_width = w;
	xsh.min_height = h;
	XSetWMNormalHints(dpy, table, &xsh);
    }
    w = max(graphic.width, w);
    h = max(graphic.height, h);
#else
    w = max(w, geo.w_width);
    h = max(h, geo.w_height);
#endif
    /* w and h are the maximum of the current visible size and the minimum size */
    if (w != graphic.width || h != graphic.height)
	soft_Resize(w, h);		/* request a resize if greater */
    init_layout();			/* new setup */
}

void cmd_Layout(void) {
    int i;
    init_layout();
    for (i = FIRST_SLOT; i <= LAST_SLOT; ++i)
	if (pile_resize(i))
	    draw_pileupdate(i, 0);
}



void obtain_current_geometry(void) {
#ifdef useXaw
    geo.w = geo.w_width;
    geo.h = geo.w_height;
#else
    geo.w = graphic.width;
    geo.h = graphic.height;
#endif
    geo.dx = graphic.xgap;
    geo.dy = graphic.ygap;
    geo.cw = CARD_WIDTH;
    geo.ch = CARD_HEIGHT;
    geo.rx = card.rx;
    geo.ry = card.ry;
}

/* there are 4 types of piles: VDECK, tmps, slots, stacks */
/* the IDECK is of no interest for this function */

/* find a layout for geo.w/geo.h, which is at least
   geo.min_width, geo.min_height
   and store the minimal size of this layout type in
   geo_preferred_width, geo.preferred_height */
void init_layout(void) {
    static int layout_type = -1, yoff = -1;
    static long magic = -1;	/* only for Xlib */
    long new_magic = 0;
    int w, h, new_layout_type;
    int xnum, ynum;	/* number of cards in either direction */

    /* get the size of the actual window */
#ifdef useXaw
    w = geo.w_width;
    h = geo.w_height;
#else
    w = graphic.width;
    h = graphic.height;
#endif
#ifdef LABER
    printf("init_layout requested for size (%d,%d)\n", w, h);
#endif

#ifdef useXlib
    {   int x, y;
	x = geo.dx;
	y = geo.dy;
	/* y is used space in vertical direction */
	/* get new_magic! */
	button.num = arrange_buttons(button.b, &x, &y, w, &new_magic);
	/* sorry, work is done twice */
	graphic.yoff = calc_yoff(w);
	geo.h -= graphic.yoff;		/* assume smaller height */
    }
    obtain_current_geometry();
    new_layout_type = generate_layout();
    {   int i;
	for (i = 0; i < game.numpiles; ++i)
	    if (!NOT_DISPLAYED(geo.pg+i))
		geo.pg[i].y += graphic.yoff;
	geo.h += graphic.yoff;
	geo.preferred_height += graphic.yoff;
    }
#else
    obtain_current_geometry();
    new_layout_type = generate_layout();
#endif

    xnum = (geo.w - geo.dx) / (geo.cw+geo.dx);
    ynum = (geo.h - geo.dy) / (geo.ch+geo.dy);

#if 0	/* debug */
    printf("deck %d position: (%d,%d), first slot at (%d,%d)\n",
	   p - geo.pg, p->x, p->y,
	   geo.pg[rules.numstacks].x, geo.pg[rules.numstacks].y);
    printf("cols = %d, off = %d\n", cols, off);
    printf("xxdeck at pos %d,%d\n", geo.pg[DECK].x, geo.pg[DECK].y);
#endif

    if (new_layout_type != layout_type || geo.dy != yoff) {
/*	new_layout_type < 10) {	 everything changed  (or may be resized) */
	layout_type = new_layout_type;
	yoff = geo.dy;
	magic = new_magic;
	refresh_screen();
    } else if (magic != new_magic) {		/* at least one button did move */
	magic = new_magic;
	XClearArea(dpy, table, 0, 0, 0, geo.dy-2, True);	/* just redraw the buttons */
    }
}
