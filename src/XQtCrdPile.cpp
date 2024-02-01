/* -*- C++ -*-	Time-stamp: <08 May 99 15:05:38 Michael Bischoff>
   XQtCardPile.cpp
   This widget displays a pile of cards (slot, stack, etc...)
   on the tableau widget
 */

#include "XQtCardPile.h"
#include "XQtCards.h"
#include "XQtTableau.h"
#include <qpainter.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qevent.h>
#include "xpatgeo.h"

QSize XQtCardPile::sizeHint() const {
    if (special_image != -1 && pileno >= 0 && pileno < game.numpiles) {
	struct pilegeometry *p = geo.pg + pileno;
	return QSize(p->w, p->h);
    } else {
	if (geo.cw > 0 && geo.ch > 0)
	    return QSize(geo.cw, geo.ch);
	else
	    return QSize();
    }
}

void XQtCardPile::mousePressEvent(QMouseEvent* e) {
    Cardindex c;
    int mx = e->x(), my = e->y();
    int cw = graphics->cardwidth(), ch = graphics->cardheight();
    int button = 0;
//    printf("mouse is pressed in CardPile %d at %d,%d\n", pileno, mx, my);

    c = FindCardOfMousePos(pileno, mx, my);

    switch (e->button()) {
    case LeftButton:
	if (c < 0)
	    return;
	button = 1;
	button_pressed(pileno, c, 1);	// quick move
	return;
    case MidButton:
	button = 2;
	if (c == -2)
	    return;
	button_pressed(pileno, c, 2);	// select / deselect
	if (!tabl->dragndrop_on) {
	    return;			// done
	}
	c = game.srcind;		// reached card according to rules
	break;
    case RightButton:
	if (c < 0)
	    return;
	button = 3;
	break;
    default:
	return;
    }

    if (c < 0)
	return;
//	printf("  pressed on card with value %d\n", game.cards[c]);
    XQtCardPile *floating = new XQtCardPile(0, tabl);
    int i, cx, cy, top;
    struct pilegeometry *p = geo.pg + pileno;
    i = c - INDEX_OF_FIRST_CARD(pileno);
    if (e->button() == MidButton)
	// visible card = topmost card
	top = INDEX_OF_LAST_CARD(pileno);
    else
	top = c;
    cx = p->ox + i * p->cdx;
    cy = p->oy + i * p->cdy;
    floating->move(x() + cx, y() + cy);
    floating->setMask(*(graphics->get_clipmap()));
    if (game.visible[top])
	floating->special_image = game.cards[top];
    else
	floating->special_image = 99;

    num_to_paint = -1;
    if (e->button() == MidButton) {
	/* drag it */
	num_to_paint = c - INDEX_OF_FIRST_CARD(pileno);	// cards remaining to paint
	show_mark(0);
	repaint();
	tabl->startDrag(floating, mx - cx, my - cy, TRUE, cx + x(), cy + y(), pileno);
    } else {
	/* only expose it */
	tabl->startDrag(floating, mx - cx, my - cy, FALSE, 0, 0, -1);
    }
}

/* the release event is sent to the widget which got the pressed event, not
   to the widget where the mouse currently is over! */
void XQtCardPile::mouseReleaseEvent(QMouseEvent* e) {
//    printf("Calling startAnimate(%d,%d)\n", special_image, pileno);
//    if (special_image >= 0) {
	// this is the dragged card
	// start movement with mouse coordinates
	tabl->startAnimate(x() + e->x(), y() + e->y());
//    }
}

void XQtCardPile::mouseMoveEvent(QMouseEvent* e) {
    tabl->Drag(x() + e->x(), y() + e->y());
}

void XQtCardPile::setCorrectSize() {
    struct pilegeometry *p;
    p = geo.pg + pileno;
    setGeometry(p->x, p->y, p->w, p->h);	// take values from geo.pg[]
}

XQtCardPile::XQtCardPile(int pilenr, XQtTableau *parent, const char *name=0)
  : QWidget(parent, name) {
    pileno = pilenr;
    tabl = parent;
    graphics = tabl->getCards();
    num_to_paint = -1;
    special_image = -1;
    if (!NOT_DISPLAYED(geo.pg+pileno)) {
	setCorrectSize();
	setBackgroundColor(darkGreen);
    }
//    fprintf(stderr, "created pile %d (type %d) at %d,%d, size %d,%d\n",
//	    pileno, game.piletype[pileno], x(), y(), width(), height());
    
}

void XQtCardPile::compressCards() {
    num_to_paint = -1;
    if (pile_resize(pileno))
	repaint();
}

void XQtCardPile::paintEvent(QPaintEvent *event) {
    QPixmap *Pixmap_to_draw = 0;
    int xdelta, ydelta, num;
    struct pilegeometry *p = geo.pg + pileno;
    xdelta = p->cdx;
    ydelta = p->cdy;

    if (special_image != -1) {
	/* floating card */
	if (special_image == 99)
	    Pixmap_to_draw = graphics->get_pm_cardback();
	else
	    Pixmap_to_draw = graphics->get_pm_card(special_image);
	if (event)
	    bitBlt(this, event->rect().topLeft(), Pixmap_to_draw, event->rect());
	else
	    bitBlt(this, 0, 0, Pixmap_to_draw, graphics->cardwidth(), graphics->cardheight(), CopyROP, FALSE);
	return;
    }
    if (pileno < 0 || pileno >= game.numpiles) {
	printf("repaint request for pile %d (pos = %d,%d, size = %d,%d)\n",
	       pileno,
	       x(), y(), width(), height());
	return;
    }
    if (game.disable[pileno])     /* don't draw THIS pile */
        return;
    if (NOT_DISPLAYED(p))
        return;                 /* draw nothing */

    num = num_to_paint < 0 ? CARDS_ON_PILE(pileno) : num_to_paint;

    if (!num) {          /* draw empty pile */
        switch (game.piletype[pileno]) {
        case Stack:
	    Pixmap_to_draw = graphics->get_pm_card(SUITSYMBOL + SUIT(pileno));
            break;
        default:
            Pixmap_to_draw = graphics->get_pm_empty();
            break;
        }
	if (event)
	    bitBlt(this, event->rect().topLeft(), Pixmap_to_draw, event->rect());
	else
	    bitBlt(this, 0, 0, Pixmap_to_draw, graphics->cardwidth(), graphics->cardheight(), CopyROP, FALSE);
    } else if (!ydelta && !xdelta) {      /* only topmost card is visible */
        Cardindex c;
        c = INDEX_OF_FIRST_CARD(pileno) + num - 1;
	Pixmap_to_draw = game.visible[c] ? graphics->get_pm_card(game.cards[c])
	 : graphics->get_pm_cardback();

	if (event)
	    bitBlt(this, event->rect().topLeft(), Pixmap_to_draw, event->rect());
	else
	    bitBlt(this, 0, 0, Pixmap_to_draw, graphics->cardwidth(), graphics->cardheight(), CopyROP, FALSE);

    } else {
	// at least one card, painting a slot
	int cdelta = num;
	Cardindex c = INDEX_OF_FIRST_CARD(pileno) + num - cdelta; // the lowest one to repaint
	int i = c - INDEX_OF_FIRST_CARD(pileno); 

//	fprintf(stderr, "painting pile %d (%d cards, d=%d,%d)\n",
//		pileno, cdelta, xdelta, ydelta);
	while (--cdelta >= 0) {
	    int pw, ph;	// paint-width and height
//	    fprintf(stderr, "  visible=%d at %d,%d, size %d,%d\n", game.visible[c],
//		    xdelta*i, ydelta*i, graphics->cardwidth(), graphics->cardheight());
	    Pixmap_to_draw = game.visible[c] ? graphics->get_pm_card(game.cards[c])
		: graphics->get_pm_cardback();
	    pw = geo.cw;
	    ph = geo.ch;
	    if (cdelta) {
		/* Not the last card. May use card clipping optimisation */
		if (p->cdx == 0 && p->cdy > 0)
		    ph = p->cdy + geo.ry;
		if (p->cdy == 0 && p->cdx > 0)
		    pw = p->cdx + geo.rx;
	    }
	    bitBlt(this,
		   p->ox + p->cdx*i, p->oy + p->cdy*i,
		   Pixmap_to_draw, 0, 0,
		   pw, ph, CopyROP, FALSE);
	    ++c;
	    ++i;
	}
    }
}
