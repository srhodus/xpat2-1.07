/* -*- C++ -*-	Time-stamp: <15 May 99 20:56:31 Michael Bischoff> */
/*
   Description:
   class XQtCardPile displays a pile of cards

   Sources:
   XQtCardPile.h	header file
   XQtCardPile.cpp	implements the constructor and destructor

   Dependencies:
   only usable as child of the XQtTableau widget

   Author:
   Michael Bischoff	(Michael.Bischoff@gmx.net)
*/

#include <qwidget.h>
#include <qsize.h>

class XQtCards;
class XQtTableau;
class QMouseEvent;

extern "C" {
#include "xpatgame.h"
}

#define SUITSYMBOL      52      /* for empty stacks */
#define CARDBACK        56
#define OUTLINE         58
#define NOTHING         59

class XQtCardPile : public QWidget {
    Q_OBJECT
public:
    XQtCardPile(int pilenr, XQtTableau *parent, const char *name=0);
    void compressCards();	// adjust internally to available space (Slots)
    void setCorrectSize();	// adjust widget (size and pos) after graphics change

    int num_to_paint;		// number of cards to paint (-1 = normal)
    QSize sizeHint() const;
private:
    XQtCards *graphics;		// points to graphics data
    XQtTableau *tabl;		// points to tableau widget
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    int pileno;			// pile number in game structure
    int special_image;		// for exposing cards: if not -1, then card (99 = Cardback)
protected:
    void paintEvent(QPaintEvent *);
};
