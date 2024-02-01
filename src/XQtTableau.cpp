/* -*- C++ -*-	Time-stamp: <08 May 99 15:05:13 Michael Bischoff>
   XQtTableau.cpp
 */

#include "XQtTableau.h"
#include "XQtCards.h"
#include "XQtCardPile.h"
#include <qevent.h>
#include <qtimer.h>
#include <qrect.h>

#include <time.h>
#include "xpatgeo.h"

QSize XQtTableau::sizeHint() const {
    if (geo.preferred_width > 0 && geo.preferred_height > 0)
	return QSize(geo.preferred_width, geo.preferred_height);
    else 
	if (geo.min_width > 0 && geo.min_height > 0)
	    return QSize(geo.min_width, geo.min_height);
	else
	    return QSize();
}

// static data needed for the C routines
XQtTableau *tableau = 0;

extern "C" void Force_Resize(int w, int h);

/* bool drag = TRUE if middle button pressed (move card)
   bool drag = FALSE if right button pressed (just show card) */

void XQtTableau::startDrag(XQtCardPile *pile, int ox, int oy, bool drag, int x, int y, int pilen) {
    dp_tpile = -2;
    stopDrag();	// stop dragging any previously dragged card
    dragtype = drag;
    hs_x = ox;	// mouse position within dragged widget
    hs_y = oy;
    src_x = x;
    src_y = y;
    src_pile = pilen;
    dragpile = pile;
    dragpile->show();
    dragpile->raise();
}

void XQtTableau::stopDrag() {
//    printf("StopDrag() called with tpile = %d, srcind = %d\n", dp_tpile, game.srcind);
    if (dp_tpile >= 0)
	piles[dp_tpile]->num_to_paint = -1;
    if (!dragndrop_on)
	return;
    if (dragpile)
	delete dragpile;
    dragpile = 0;
    // do the move if valid
    if (dp_tpile >= 0) {
	if (game.srcind >= 0) {
	    store_move(do_move(game.srcind, dp_tpile));
	    game.srcind = -1;
	    piles[dp_tpile]->repaint();	// restore full sight
	    if (dp_tpile != src_pile)
		piles[src_pile]->repaint();
	}
    }
    dp_tpile = -3;
}

void XQtTableau::startAnimate(int x, int y) {
    if (!dragtype) {
	/* just expose card */
	if (dragpile)
	    delete dragpile;
	dragpile = 0;
	return;
    }
    if (!dragndrop_on)
	return;
    dp_tpile = -2;
    if (!dragpile || !frames_per_second) {
	stopDrag();
	return;
    }
//    printf("StartAnimate() called with srcind = %d\n", game.srcind);
    // find destination pile by mouse coordinates
    if (game.srcind >= 0) {
	Pileindex i;
	struct pilegeometry *p;
	for (i = 0; i < game.numpiles; ++i) {
	    p = geo.pg + i;
	    if (x >= p->x && x < p->x + p->w &&
		y >= p->y && y < p->y + p->h) {
		dp_tpile = i;
		break;
	    }
	}
	if (dp_tpile >= 0 && move_valid(game.srcind, dp_tpile)) {
//	    store_move(do_move(h, pile));
	    show_message("");
	    dp_tx = p->x + p->ox + p->cdx * CARDS_ON_PILE(dp_tpile);
	    dp_ty = p->y + p->oy + p->cdy * CARDS_ON_PILE(dp_tpile);
//	    printf("Move accepted to pile %d at %d,%d\n", dp_tpile, dp_tx, dp_ty);
	} else {
	    game.srcind = -1;
	    show_message(TXT_INVALIDMOVE);
	    dp_tpile = src_pile;
	    dp_tx = src_x;
	    dp_ty = src_y;
	}
    } else {
	stopDrag();
	return;
    }
    if (!animation_on) {
	stopDrag();
	return;
    }
//    printf("StartAnimate: tpile = %d\n", dp_tpile);

    dp_sx = dragpile->QWidget::x();
    dp_sy = dragpile->QWidget::y();
    dp_r2 = (dp_sx - dp_tx) * (dp_sx - dp_tx)
	+ (dp_sy - dp_ty) * (dp_sy - dp_ty);
    if (dp_r2 < 16) {
	stopDrag();
	return;
    }
    dp_done = 0;
    if (!timer) {
	// create timer object on demand
	timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(move_dragpile()));
    }
    timer->start(1000 / frames_per_second);
}

void XQtTableau::move_dragpile() {
    if (!pixels_per_second || pixels_per_second > 50)
	pixels_per_second = 2;
    dp_done += pixels_per_second;
    if (!dragpile || (dp_done * dp_done > dp_r2)) {
	timer->stop();
	stopDrag();
	return;
    }
    /* move dragpile to certain amount of path */
#if 0
    double arc = 3.14159 * 0.5 * dp_done / sqrt(dp_r2);
    dragpile->move(dp_sx + (int)((dp_tx - dp_sx) * sin(arc)),
		   dp_ty + (int)((dp_sy - dp_ty) * cos(arc)));
#else
    // accelerated move
    int nx, ny;
    nx = dp_sx + (dp_tx - dp_sx) * (dp_done * dp_done) / dp_r2;
    ny = dp_sy + (dp_ty - dp_sy) * (dp_done * dp_done) / dp_r2;
    dragpile->move(nx, ny);
//    printf("   moved to %4d,%4d\n", nx, ny);
#endif
}


void XQtTableau::Drag(int mx, int my) {
    if (dragpile && dragtype)
	dragpile->move(mx - hs_x, my - hs_y);
}



void XQtTableau::CustomizeModal() {
    cards->CustomizeDialog(TRUE);
}
void XQtTableau::CustomizeModeless() {
    cards->CustomizeDialog(FALSE);
}

void XQtTableau::mouseReleaseEvent(QMouseEvent* e) {
    stopDrag();
}

extern "C" void draw_pileupdate(int pile, int delta) {
    if (pile < game.numpiles && tableau->piles[pile]) {
	tableau->piles[pile]->compressCards();
	tableau->piles[pile]->repaint();
    }
}
extern "C" void move_card_data(Cardindex dst, Cardindex src) {
    game.cards[dst] = game.cards[src];
    game.visible[dst] = game.visible[src];
//    tableau->cardy[dst] = tableau->cardy[src];
}

extern "C" void cmd_LeavePat(void) {
}
extern "C" void refresh_screen(void) {
    tableau->repaint();
}
extern "C" void request_confirm(void (*a)(void), const char *b) {
}
extern "C" void win_game(void) {}


void XQtTableau::leave_rules() {
    delete_all_piles();
}
void XQtTableau::enter_rules() {
    int i;
    generic_minwindow();
    resize(geo.min_width, geo.min_height);
    init_layout();
    create_all_piles();
    for (i = 0; i < game.numpiles; ++i)
	if (piles[i])
	    piles[i]->show();
    repaint();
}

void XQtTableau::obtain_geometry() {
    geo.w = width();
    geo.h = height();
    geo.dx = cards->get_pile_dx();
    geo.dy = cards->get_pile_dy();
    geo.cw = cards->cardwidth();
    geo.ch = cards->cardheight();
    geo.rx = cards->get_rx();
    geo.ry = cards->get_ry();
}

void obtain_current_geometry(void) {
    tableau->obtain_geometry();
}

void cmd_Layout(void) {
    int i;
    tableau->init_layout();
    for (i = FIRST_SLOT; i <= LAST_SLOT; ++i)
        if (pile_resize(i))
            draw_pileupdate(i, 0);
}

void XQtTableau::init_layout() {
    obtain_geometry();	// new!
    generate_layout(); /* width(),
		    height(),
		    cards->cardwidth(),
		    cards->cardheight(),
		    cards->get_pile_dx(),
		    cards->get_pile_dy()); */
}

extern "C" void cmd_MinWindow(void) {
    geo.w = geo.min_width;
    geo.h = geo.min_height;
    Force_Resize(geo.w, geo.h);
    cmd_Layout();
    tableau->repaint();
}
extern "C" void cmd_PreferredWindow(void) {
    geo.w = geo.preferred_width;
    geo.h = geo.preferred_height;
    Force_Resize(geo.w, geo.h);
    cmd_Layout();
    tableau->repaint();
}
extern "C" void cmd_Cancel(void) {}
extern "C" void cmd_Confirm(void) {}

// create the visible piles if the rules are set and init_layout was called
void XQtTableau::create_all_piles() {
    piles = new XQtCardPile *[game.numpiles];
    for (int i = 0; i < game.numpiles; ++i)
	piles[i] = (geo.pg[i].x < 0 ? 0 : new XQtCardPile(i, this));
}

XQtTableau::XQtTableau(const char *rules, long seed,
		       QWidget *parent, const char *name,
		       const char *xpmdir) : QWidget(parent, name) {

			   int w, h;
   cards = new XQtCards(xpmdir);
   setBackgroundColor(darkGreen);
   // in this version, the parent is a QSrollView

   // rules = Gypsy_rules per default
   if (!rules)
       rules = "Gypsy";
   new_rules(rules, -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1);
   
   tableau = this;
   generic_minwindow();
//   resize(geo.min_width, geo.min_height);
			   w = max(geo.min_width, 800);
			   h = max(geo.min_height, 600);
   resize(w, h);
   init_layout();	// requires a set-up size!
   geo.aw = geo.ah = geo.cw / 16;	/* set defaults */

    create_all_piles();

    newgame(seed);

//    fprintf(stderr, "Tableau constructor done\n");
    connect(cards, SIGNAL(cards_changed()), this, SLOT(repaintAll()));
    timer = 0;
    frames_per_second = 50;
    pixels_per_second = 15;
//   resize(800, 600);

}

void XQtTableau::delete_all_piles() {
    for (int i = 0; i < game.numpiles; ++i) {
	if (piles[i])
	    delete piles[i];
    }
    delete piles;
}

XQtTableau::~XQtTableau() {
    tableau = 0;
    if (timer)
	delete timer;
    if (dragpile)
	delete dragpile;
    delete_all_piles();
    delete cards;
}


#if 0
QSize XQtTableau::sizeHint() const {
    fprintf(stderr, "size hint called\n");
    return QSize(12 * cards->cardwidth(), 2 * cards->cardheight());
}
#endif

/* this slot should be called when the graphics have changed */
/* TODO: before calling this, resize tableau widget if necessary */
void XQtTableau::repaintAll() {	/* SLOT */
    int i;

    init_layout();
    for (i = 0; i < game.numpiles; ++i)
	if (piles[i])
	    piles[i]->setCorrectSize();
    for (i = FIRST_SLOT; i <= LAST_SLOT; ++i)
        pile_resize(i);
    erase();	// erase complete widget
    for (i = 0; i < game.numpiles; ++i)
	if (piles[i])
	    piles[i]->repaint(TRUE);	// piles are different widgets
}

void XQtTableau::paintEvent(QPaintEvent *event) {
    int i;
    if (!event)
	repaintAll();
    else {
	QRect r = rect();

//	erase(r);	// besser is das..
	for (i = 0; i < game.numpiles; ++i)
	    if (piles[i])
		piles[i]->setCorrectSize();
	for (i = FIRST_SLOT; i <= LAST_SLOT; ++i)
	    pile_resize(i);
	for (i = 0; i < game.numpiles; ++i)
	    if (piles[i])
		if (piles[i]->rect().intersects(r))
		    piles[i]->repaint(TRUE);
    }
}
