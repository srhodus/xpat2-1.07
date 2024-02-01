/* -*- C++ -*-	Time-stamp: <05 Nov 00 21:21:07 Michael Bischoff> */
/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module XQtMarkCard.c			     */
/*									     */
/*	Routines for marking selected cards				     */
/*	written by Michael Bischoff					     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#include <qpixmap.h>
#include <qcolor.h>
#include <qbrush.h>
#include <qpainter.h>
#include "XQtCardPile.h"
#include "XQtTableau.h"
extern "C" {
#include "xpatgeo.h"
}

extern XQtTableau *tableau;
static XQtCardPile *merk_pile;

/* game.for set-mark / clear-mark */

static QPixmap *mark_storage = 0;
static int mark_height = 0, mark_width = 0;
static QBrush *mark_brush = 0;
static int rem_x, rem_y;
static int rem_w, rem_h;	   /* h = 0: only horizontal bars saved */

static void create_mark_storage(void) {
    mark_storage = new QPixmap(mark_width, mark_height);
}

static void free_mark(void) {
    if (mark_storage)
	delete mark_storage;
    mark_storage = 0;
}

static void set_mark(int x, int y, int W, int h) {
    if (h > mark_height) {	/* make sure there's enough space */
	free_mark();
	mark_height = h;
    }
    if (W > mark_width) {
	free_mark();
	mark_width = W;
    }
    if (!mark_storage)
	create_mark_storage();

    rem_h = h;
    rem_w = W;
    rem_x = x;
    rem_y = y;
	bitBlt(mark_storage, 0, 0, merk_pile, x, y, W, h, Qt::CopyROP, FALSE);
	QPainter p(merk_pile);
	if (!mark_brush)
		mark_brush = new QBrush(Qt::black, Qt::DiagCrossPattern);

	p.setBrush(*mark_brush);
	p.setPen("red");
	p.drawRoundRect(x, y, W, h,
	198 * geo.rx / geo.cw,
	198 * geo.ry / geo.ch);
}

static void clear_mark(void) {
    bitBlt(merk_pile, rem_x, rem_y,
	   mark_storage, 0, 0,
           rem_w, rem_h, Qt::CopyROP, FALSE);
}

/* pile is completely drawn and unmarked. */
/* check, if pile has to be marked.       */
/* if so, do it                           */

extern "C" void show_mark(boolean on) {
    if (on) {
	struct pilegeometry *p;
	int f, l;
	int pile, m_x, m_y, m_w, m_h;

 	if (game.srcind < 0)
	    return;
	if (!mark_storage) {
	    mark_height = geo.lsh;
	    mark_width = geo.lsw;
	    create_mark_storage();
	}
	
	p = geo.pg + (pile = getpile(game.srcind));
	f = game.srcind - INDEX_OF_FIRST_CARD(pile);
	l = CARDS_ON_PILE(pile)-1;
	if (p->cdx >= 0) {
	    m_x = p->ox + f * p->cdx;
	    m_w = (l-f)*p->cdx + geo.cw;
	} else {
	    m_x = p->ox + l * p->cdx;
	    m_w = (f-l)*p->cdx + geo.cw;
	}
	if (p->cdy >= 0) {
	    m_y = p->oy + f * p->cdy;
	    m_h = (l-f)*p->cdy + geo.ch;
	} else {
	    m_y = p->oy + l * p->cdy;
	    m_h = (f-l)*p->cdy + geo.ch;
	}
	merk_pile = tableau->piles[pile];
	set_mark(m_x, m_y, m_w, m_h);
    } else {
	if (merk_pile)
		clear_mark();
	merk_pile = 0;
    }
}
