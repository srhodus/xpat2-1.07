/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module X-arrows.c			     */
/*									     */
/*	Displays hint arrows for the X interface			     */
/*	written by Heiko Eissfeldt and Michael Bischoff			     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#include "X-pat.h"

GC hintgc;
static struct arrow_storage {
    int w, h;
    Pixmap arrow_storage;
} as[4] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };

#ifdef useXlib
void init_arrow(const char *arrowcolor, int arrwidth, int arrheight) {
    /* make GCs for dashed lines or colored lines (to mark cards) */
    XGCValues gcv;
    long gcflags;
    XColor color;
    Colormap cmap;
    
    geo.aw = geo.ah = CARD_WIDTH / 16;	/* defaults */
    if (arrwidth >= 0 && arrwidth <= 30)
	geo.aw = arrwidth;
    if (arrheight >= 0 && arrheight <= 30)
	geo.ah = arrheight;

    if (geo.aw <= 0 || geo.ah <= 0) {
	geo.aw = geo.ah = -1;
	return;			/* no arrows wanted */
    }

    /* make own gcs for dashed lines */
    gcv.background = BlackPixel(dpy, screen);
    gcv.graphics_exposures = True;
    gcflags = GCForeground | GCBackground | GCGraphicsExposures;
    if (graphic.is_color && arrowcolor) {
	cmap = DefaultColormap(dpy, screen);
	color.flags = DoRed | DoGreen | DoBlue;
	XAllocNamedColor(dpy, cmap, arrowcolor, &color, &color);
	gcv.foreground = color.pixel;
	hintgc = XCreateGC(dpy, RootWindow(dpy, screen), gcflags, &gcv);
    } else {
	gcv.foreground = WhitePixel(dpy, screen);
	hintgc = XCreateGC(dpy, RootWindow(dpy, screen), gcflags, &gcv);
    }
}
#endif

#ifdef useXview
void init_arrow(unsigned long arrowcolor, int arrwidth, int arrheight) {
    XGCValues gcv;
    long gcflags;
    
    if (arrwidth >= 0 && arrwidth <= 30)
	geo.aw = arrwidth;
    if (arrheight >= 0 && arrheight <= 30)
	geo.ah = arrheight;

    if (geo.aw <= 0 || geo.ah <= 0) {
	geo.aw = geo.ah = -1;
	return;			/* no arrows wanted */
    }

    gcv.background = BlackPixel(dpy, screen);
    gcv.graphics_exposures = True;
    gcflags = GCForeground | GCBackground | GCGraphicsExposures;
    gcv.foreground = arrowcolor;
    hintgc = XCreateGC(dpy, RootWindow(dpy, screen), gcflags, &gcv);
}
#endif

void bitblt_arrow(int type, int save, int x, int y, int w, int h) {
    struct arrow_storage *ap = as+type;
    /* printf("bitblt %d,%d, %d,%d, %d,%d called\n",
       type, save, x, y, w, h); */

    if (save) {
	/* for for minimum size */
	if (!ap->arrow_storage || ap->w < w || ap->h < h) {
	    /* not allocated or insufficient size */
	    if (ap->arrow_storage)
		XFreePixmap(dpy, ap->arrow_storage);
	    if (ap->w < w)
		ap->w = w;
	    if (ap->h < h)
		ap->h = h;
	    ap->arrow_storage = XCreatePixmap(dpy, table, ap->w, ap->h,
					      DefaultDepth(dpy, screen));
	}
	XCopyArea(dpy, table, ap->arrow_storage, whitegc,
		  x, y, w, h, 0, 0);
    } else {
	if (ap->arrow_storage) {
	    XCopyArea(dpy, ap->arrow_storage, table, whitegc,
		      0, 0, w, h, x, y);
	}
    }
}

void draw_arrow_polygon(int npoints, const struct Coord *poly) {
    int i;
    XPoint Poly[ARROW_MAX_COORDINATES];

    /* printf("Poly(%d) called\n", npoints); */
    for (i = 0; i < npoints; ++i) {
	Poly[i].x = poly[i].x;
	Poly[i].y = poly[i].y;
    }
    XFillPolygon(dpy, table, hintgc, Poly, npoints, Complex, CoordModeOrigin);
    Poly[npoints] = Poly[0];
    XDrawLines(dpy, table, blackgc, Poly, npoints+1, CoordModeOrigin);

#ifdef useXview
    xv_set(xv_default_server, SERVER_SYNC, FALSE, 0);
#else
    XFlush(dpy);
#endif
}
