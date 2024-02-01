/* -*- C++ -*-	Time-stamp: <15 May 99 20:56:44 Michael Bischoff> */
/*
   Description:
   class XQtCards is a QPixmap factory for card images, to be used by
   XPat2 and other card games.
   This class does mainly exist to separate the ugly image constructor
   from the rest of the game.

   Sources:
   XQtCards.h		header file
   XQtCards.cpp		implements the constructor and destructor
   XQtCardsDlg.cpp	implements the customisation dialog

   Dependencies:
   requires the widget qmaskedit and the Qt library (tested with version 1.42)

   Author:
   Michael Bischoff	(Michael.Bischoff@gmx.net)
*/

#ifndef XQTCARDS_H
#define XQTCARDS_H

#include <qobject.h>

class QPixmap;
class QBitmap;
class QDialog;
class QLineEdit;
class QMaskEdit;

class XQtCards : public QObject {	// requires QObject for signals and slots
    Q_OBJECT
private:
    /* data describing the geometry (CardConfig subclass?) */
    int w, h;			// width and height of a card
    int rx, ry;			// pixel size of rounded card corners
    int pile_dx, pile_dy;	// distance between piles
    int slot_dx, slot_dy;	// offset of cards within slots

    /* Pixmaps */
    char *directory;		// card graphics directory
    int numcardbacks;		// number of cardback pixmaps
    int currentcardback;	// currently used cardback (1..max)
    QBitmap *clipmap;		// storage for card clip (filled rounded rectangle)
    QBitmap *clipempty;		// rounded rectangle
    QPixmap *pm_cardback;	// QPixmap of the back side of the cards
    QPixmap *pm_empty;		// place holder (clipped by emptyclip)
    QPixmap *pm_cards[59];	// QPixmaps for 52 cards + 4 empty slots + 3 jokers
    QPixmap *XQtCards::load_cardback(int num);	// helper function
    QDialog *customize_dlg;	// current open dialog (only one dlg per instance */
    QLineEdit *customize_dlg_dir;	// current input field
    QMaskEdit *customize_dlg_cbn;	// cardback number
    void reloadGraphics(const char *);	// update pixmaps after directory has changed
    void local_constructor(const char *);
    void local_destructor();
    void check_for_changes_and_apply();
public:
    XQtCards(const char *xpmdir = 0);	// constructor uses a compiled-in default directory
   ~XQtCards();
    void CustomizeDialog(bool modal = FALSE);
    int cardwidth()		 	const { return w; }
    int cardheight()			const { return h; }
    int get_rx()			const { return rx; }
    int get_ry()			const { return ry; }
    int get_pile_dx()			const { return pile_dx; }
    int get_pile_dy()			const { return pile_dy; }
    int get_slot_dx()			const { return slot_dx; }
    int get_slot_dy()			const { return slot_dy; }
    int get_numcardbacks()		const { return numcardbacks; }
    int get_currentcardback()		const { return currentcardback; }
    void set_cardback(int num = 0);	// 0 = select a random one

    QPixmap *get_pm_card(int index)	const { return pm_cards[index]; }
    QPixmap *get_pm_cardback()		const { return pm_cardback; }
    QPixmap *get_pm_empty()		const { return pm_empty; }
    QBitmap *get_clipmap()		const { return clipmap; }

signals:
    void cards_changed();		// emitted by customize_dlg();
private slots:
    void cards_reset();
    void cards_apply();
    void cards_ok();
    void cards_cancel();
    void cards_browse();
};

#endif
