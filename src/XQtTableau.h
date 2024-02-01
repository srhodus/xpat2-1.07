#ifndef XQTTABLEAU_H
#define XQTTABLEAU_H

#include <qwidget.h>

/* The Tableau constructor loads the card graphics (class XQtCards)
   and requests the layout from the game.
   With the size of a single card and the layout and the parameters
   (x distance, y distance, Std-delta-y) the size of the widget is then
   determined */

// class XPat2CommonRules;
class XQtCardPile;
class XQtCards;
class QMouseEvent;
class QTimer;

class XQtTableau : public QWidget {
    Q_OBJECT
private:
    XQtCards *cards;		// this points to an allocated object.
    XQtCardPile *dragpile;	// currently dragging this pile
    bool dragtype;		// TRUE = drag it, FALSE = do only expose it
    int hs_x, hs_y;		// hotspot within dragged cards
    QTimer *timer;		// for animated play
    int dp_sx, dp_tx, dp_sy, dp_ty, dp_tpile, dp_r2, dp_done;
    int frames_per_second;	// 1..99 (default: 20)
    int pixels_per_second;	// 1..50
    int src_x, src_y, src_pile;
    void create_all_piles();
    void delete_all_piles();

public:
    void enter_rules();
    void leave_rules();
    bool dragndrop_on;
    bool animation_on;
    bool sound_on;
    void obtain_geometry();
    QSize sizeHint() const;

private slots:
    void move_dragpile();

public slots:
    void startDrag(XQtCardPile *, int, int, bool, int, int, int);
    void stopDrag();
    void Drag(int, int);
    void startAnimate(int, int);	// mouse was released at argument pos.
    void CustomizeModal();
    void CustomizeModeless();
    void repaintAll();		// repaint all piles

public:
    XQtTableau(const char *rules = "Gypsy", long seed = -1L, QWidget *parent = 0, const char *name = 0, const char *xpmdir = 0);
    ~XQtTableau();
    XQtCardPile **piles;
    void init_layout();

//  QSize sizeHint() const;
//    int *cardy;
    XQtCards *getCards() const { return cards; }

 private:
//    void changeRules(XPat2CommonRules *rules);
    void mouseReleaseEvent(QMouseEvent*);

 private:
//    int distx;		// distance between cards - horizontally
 //   int disty;		// distance between cards - vertically
//    XPat2CommonRules *rules;
    // the number of piles is obtained from the rules class
 protected:
    void paintEvent(QPaintEvent *);

};

#endif
