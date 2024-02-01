#include "xpatgame.h"
#include "xpatgeo.h"

static int rem_sx = -1, rem_sy, rem_dx, rem_dy;

static void compute_rem(void) {
    Pileindex srcpile;
    struct pilegeometry *p;

    srcpile = getpile(game.arrow_srcind);
    p = geo.pg + srcpile;
    rem_sx = p->x + p->ox + geo.cw / 2;
    rem_sy = p->y + p->oy + geo.ch / 2;
    if (game.piletype[srcpile] == Slot && CARDS_ON_PILE(srcpile) > 1) {
	/* first, compute position in the middle of topmost card */
	rem_sx += p->cdx * (game.arrow_srcind - INDEX_OF_FIRST_CARD(srcpile));
	rem_sy += p->cdy * (game.arrow_srcind - INDEX_OF_FIRST_CARD(srcpile));
	if (game.arrow_srcind != INDEX_OF_LAST_CARD(srcpile)) {
	    /* place arrow within visible part of card */
	    if (p->cdx) {
		/* horizontal displacement */
		if (p->cdx > 0)
		    rem_sx -= (geo.cw - p->cdx) / 2;
		else
		    rem_sx += (geo.cw + p->cdx) / 2;
	    }
	    if (p->cdy) {
		if (p->cdy > 0)
		    rem_sy -= (geo.ch - p->cdy) / 2;
		else
		    rem_sy += (geo.ch + p->cdy) / 2;
	    }
	}
    }
    p = geo.pg + game.arrow_dstpile;
    rem_dx = p->x + p->ox + geo.cw / 2;
    rem_dy = p->y + p->oy + geo.ch / 2;
    if (game.piletype[game.arrow_dstpile] == Slot &&
	!EMPTY(game.arrow_dstpile)) {
	rem_dx += p->cdx * (CARDS_ON_PILE(game.arrow_dstpile) - 1);
	rem_dy += p->cdy * (CARDS_ON_PILE(game.arrow_dstpile) - 1);
    }
    /* check that coordinates are within tableau */
#define CHECK(rem_sy, h)	\
    if (rem_sy < 1)		\
	rem_sy = 1;		\
    if (rem_sy > geo.h - 2)	\
	rem_sy = geo.h - 2;
    CHECK(rem_sx, w);
    CHECK(rem_sy, h);
    CHECK(rem_dx, w);
    CHECK(rem_dy, h);
}

/* draw an arrow with y-part */
static int polygon_y(struct Coord *Poly,
		     int deltax, int deltay, int adx, int ady) {
    Poly[0].x = rem_dx-deltax;
    Poly[0].y = rem_dy-ady/2;
    Poly[1].x = rem_dx-adx;
    Poly[1].y = rem_dy-ady;
    Poly[2].x = rem_dx;
    Poly[2].y = rem_dy+ady;
    Poly[3].x = rem_dx+adx;
    Poly[3].y = rem_dy-ady;
    Poly[4].x = rem_dx+deltax;
    Poly[4].y = rem_dy-ady/2;
    if (rem_dx-rem_sx > 0) {	/* this is uncritical, since difference is */
        Poly[5].x = rem_dx+deltax;	/* either 0 or at least CARD_WIDTH */
        Poly[5].y = rem_sy+deltay;
        Poly[6].x = rem_sx-deltax;
        Poly[6].y = rem_sy+deltay;
        Poly[7].x = rem_sx-deltax;
        Poly[7].y = rem_sy-deltay;
        Poly[8].x = rem_dx-deltax;
        Poly[8].y = rem_sy-deltay;
	return 9;
    } else if (rem_dx < rem_sx) {
        Poly[5].x = rem_dx+deltax;
        Poly[5].y = rem_sy-deltay;
        Poly[6].x = rem_sx+deltax;
        Poly[6].y = rem_sy-deltay;
        Poly[7].x = rem_sx+deltax;
        Poly[7].y = rem_sy+deltay;
        Poly[8].x = rem_dx-deltax;
        Poly[8].y = rem_sy+deltay;
	return 9;
    } else {
        Poly[5].x = rem_sx+deltax;
        Poly[5].y = rem_sy+deltay;
        Poly[6].x = rem_sx-deltax;
        Poly[6].y = rem_sy+deltay;
	return 7;
    }
}

/* draw an x-only arrow */
static int polygon_x(struct Coord *Poly,
		     int deltax, int deltay, int adx, int ady) {
    /* arrow: 1      */
    /*          0    */
    /*             2 */
    /*          4    */
    /*        3      */
    Poly[0].x = rem_dx-adx/2;
    Poly[0].y = rem_sy-deltay;
    Poly[1].x = rem_dx-adx;
    Poly[1].y = rem_sy-ady;
    Poly[2].x = rem_dx+adx;
    Poly[2].y = rem_sy;
    Poly[3].x = rem_dx-adx;
    Poly[3].y = rem_sy+ady;
    Poly[4].x = rem_dx-adx/2;
    Poly[4].y = rem_sy+deltay;
    Poly[5].x = rem_sx-deltax;
    Poly[5].y = rem_sy+deltay;
    Poly[6].x = rem_sx-deltax;
    Poly[6].y = rem_sy-deltay;
    return 7;
}

static int compute_arrow(struct Coord *Poly) {
    /* build a polygon i.e. a arrow pointing from source to destination */ 

    if (rem_dy >= rem_sy + UPDOWN_MINDIST)    	/* arrow up */
        return polygon_y(Poly, geo.aw,-geo.ah,geo.ya_w, geo.ya_h);
    else if (rem_dy <= rem_sy - UPDOWN_MINDIST)	/* arrow down */
        return polygon_y(Poly, geo.aw,geo.ah,geo.ya_w,-geo.ya_h);
    else if (rem_dx >= rem_sx)			/* arrow to the right */
        return polygon_x(Poly, geo.aw,geo.ah,geo.xa_w,geo.xa_h);
    else					/* arrow to the left */
        return polygon_x(Poly, -geo.aw,geo.ah,-geo.xa_w,geo.xa_h);
}

static void clear_arrow(void) {
    int a, d;
    a = -1;
    if (rem_sx < rem_dx) {
	a = rem_sx; d = rem_dx - rem_sx;
    } else if (rem_sx > rem_dx) {
	a = rem_dx; d = rem_sx - rem_dx;
    } else
	d = a = -1;
    if (a >= 0) {
	bitblt_arrow(0, 0,
		     a - geo.aw, rem_sy - geo.ah,
		     d + 2 * geo.aw + 1, 2 * geo.ah + 1);
    }   
    if (rem_sy <= rem_dy - UPDOWN_MINDIST) {
	a = rem_sy; d = rem_dy - rem_sy;
    } else if (rem_sy >= rem_dy + UPDOWN_MINDIST) {
	a = rem_dy; d = rem_sy - rem_dy;
    } else {
	d = a = -1;	/* only horizontal part of arrow => y arrow */
	bitblt_arrow(2, 0,
		     rem_dx - geo.xa_w, rem_sy - geo.xa_h,
		     2 * geo.xa_w + 1, 2 * geo.xa_h + 1);
    }
    if (a >= 0) {
	bitblt_arrow(1, 0,
		     rem_dx - geo.aw, a - geo.ah,
		     2 * geo.aw + 1, d + 2 * geo.ah + 1);
	bitblt_arrow(2, 0,
		     rem_dx-geo.ya_w, rem_dy-geo.ya_h,
		     2 * geo.ya_w + 1, 2 * geo.ya_h + 1);
    }
    rem_sx = -1;
}

static void save_background(void) {
    /* save the background */
    int a, d;
    a = -1;
    if (rem_sx < rem_dx) {
	a = rem_sx; d = rem_dx - rem_sx;
    } else if (rem_sx > rem_dx) {
	a = rem_dx; d = rem_sx - rem_dx;
    } else
	d = a = -1;
    if (a >= 0) {
	int len;
	len = d + 2 * geo.aw + 1;
	bitblt_arrow(0, 1,
		     a - geo.aw, rem_sy - geo.ah,
		     len, 2 * geo.ah + 1);
    }
    if (rem_sy <= rem_dy - UPDOWN_MINDIST) {
	a = rem_sy; d = rem_dy - rem_sy;
    } else if (rem_sy >= rem_dy + UPDOWN_MINDIST) {
	a = rem_dy; d = rem_sy - rem_dy;
    } else {
	d = a = -1;	/* only horizontal part of arrow */
	bitblt_arrow(2, 1,
		     rem_dx-geo.xa_w, rem_sy-geo.xa_h,
		     2 * geo.xa_w + 1, 2 * geo.xa_h + 1);
    }
    if (a >= 0) {
	int height;
	height = d + 2 * geo.ah + 1;
	bitblt_arrow(1, 1,
		     rem_dx - geo.aw, a - geo.ah,
		     2 * geo.aw + 1, height);
	bitblt_arrow(2, 1,
		     rem_dx-geo.ya_w, rem_dy-geo.ya_h,
		     2 * geo.ya_w + 1, 2 * geo.ya_h + 1);
    }
}

void show_arrow(int on) {
    /* printf("show_arrow(%d): aw = %d\n", on, geo.aw); */
    if (geo.aw <= 0)	/* no arrows active */
	return;

    if (on) {		/* calculate new arrow position */
#ifdef DEBUG
	if (on == 2)
	    fprintf(stderr, "arrow(2): srcind = %d\n", game.arrow_srcind);
#endif
	if (game.arrow_srcind < 0)
	    return;

	/* adapt arrows to match cardset sizes */
	geo.ya_h = geo.xa_w = geo.aw * 2;
	geo.xa_h = geo.ya_w = geo.aw * 4;
	

	if (on == 1) {	/* 1 = recompute, 2 = redisplay last */
	    compute_rem();
	    save_background();
	}
	{   struct Coord poly[ARROW_MAX_COORDINATES];
	    int npoints;
	    npoints = compute_arrow(poly);
	    draw_arrow_polygon(npoints, poly);
	}
    } else {
	game.arrow_srcind = -1;	/* no valid arrow now */
	if (rem_sx < 0)
	    return;		/* no arrow was visible */
	clear_arrow();
    }
}
