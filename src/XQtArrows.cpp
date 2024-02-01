/* -*- C++ -*-	Time-stamp: <05 Nov 00 21:22:13 Michael Bischoff> */
/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module XQtArrows.cpp			     */
/*									     */
/*	Displays hint arrows for the Qt widget set			     */
/*	written by Michael Bischoff					     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#include <qpixmap.h>
#include <qbitmap.h>
#include <qcolor.h>
#include <qbrush.h>
#include <qpainter.h>
#include <qpointarray.h>
#include <qwidget.h>
#include "XQtCardPile.h"
#include "XQtTableau.h"
extern "C" {
#include "xpatgeo.h"
}

extern XQtTableau *tableau;

static QBrush *arrow_brush = 0;
static QPainter arrow_painter;

#if 0
static struct arrow_storage {
    int w, h;
    QPixmap *arrow_storage;
} as[4] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };

extern "C" void bitblt_arrow(int type, int save, int x, int y, int w, int h) {
    struct arrow_storage *ap = as + type;
    if (save) {
	/* for for minimum size */
	if (!ap->arrow_storage || ap->w < w || ap->h < h) {
	    /* not allocated or insufficient size */
	    if (ap->arrow_storage)
		delete ap->arrow_storage;
	    if (ap->w < w)
		ap->w = w;
	    if (ap->h < h)
		ap->h = h;
	    ap->arrow_storage = new QPixmap(ap->w, ap->h);
	}
	bitBlt(ap->arrow_storage, 0, 0, tableau, x, y, w, h, CopyROP, FALSE);
    } else {
	if (ap->arrow_storage) {
	    bitBlt(tableau, x, y, ap->arrow_storage, 0, 0, w, h, CopyROP, FALSE);
	}
    }
}

extern "C" void draw_arrow_polygon(int npoints, const struct Coord *poly) {
    int i;
    QPointArray Poly(ARROW_MAX_COORDINATES);

    printf("drawing polygon on %x\n", tableau);
    for (i = 0; i < npoints; ++i)
	Poly.setPoint(i, poly[i].x, poly[i].y);

    if (!arrow_brush)
	arrow_brush = new QBrush("yellow");

    arrow_painter.begin(tableau);
    arrow_painter.setBrush(*arrow_brush);
    arrow_painter.drawPolygon(Poly, FALSE, 0, npoints);
    arrow_painter.end();
}

#else

static QWidget *aw = 0;
static QPixmap *apix =0;
static QBitmap *aclip = 0;

extern "C" void bitblt_arrow(int type, int save, int x, int y, int w, int h) {
    if (!save && aw) {
	delete aw;
	delete apix;
	delete aclip;
	aw = 0;
	apix = 0;
	aclip = 0;
    }
}

extern "C" void draw_arrow_polygon(int npoints, const struct Coord *poly) {
    int i, maxx, maxy, minx, miny, w, h;
    QPointArray Poly(ARROW_MAX_COORDINATES);

//    printf("drawing polygon on %x\n", tableau);
    minx = maxx = poly[0].x;
    miny = maxy = poly[0].y;
    for (i = 1; i < npoints; ++i) {
	if (poly[i].x < minx)
	    minx = poly[i].x;
	if (poly[i].x > maxx)
	    maxx = poly[i].x;
	if (poly[i].y < miny)
	    miny = poly[i].y;
	if (poly[i].y > maxy)
	    maxy = poly[i].y;
    }
    if (aw) {
	delete aw;
	delete apix;
	delete aclip;
    }
    w = maxx-minx+1;
    h = maxy-miny+1;
    aclip = new QBitmap(w, h, TRUE);
    apix = new QPixmap(w, h);
    aw = new QWidget(tableau);
    aw->move(minx, miny);
    aw->resize(w, h);

    for (i = 0; i < npoints; ++i)
	Poly.setPoint(i, poly[i].x-minx, poly[i].y-miny);

    if (!arrow_brush)
	arrow_brush = new QBrush("yellow");

    arrow_painter.begin(apix);
    arrow_painter.setBrush(*arrow_brush);
    arrow_painter.drawPolygon(Poly, FALSE, 0, npoints);
    arrow_painter.end();
    arrow_painter.begin(aclip);
    arrow_painter.setPen(Qt::color1);
//    arrow_painter.setBrush(Dense3Pattern);
//    arrow_painter.setBrush(SolidPattern);
    arrow_painter.setBrush(Qt::color1);
    arrow_painter.drawPolygon(Poly, FALSE, 0, npoints);
    arrow_painter.end();

    aw->setMask(*aclip);
    aw->setBackgroundPixmap(*apix);
    aw->show();
    aw->move(minx, miny);
    aw->raise();
}

#endif
