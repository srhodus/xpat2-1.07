/* -*- C++ -*-	Time-stamp: <28 Apr 99 01:05:15 Michael Bischoff> */
/* implementation of the customize / change graphics dialog */

#include "XQtCards.h"
#include <qdialog.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include "qmaskedit.h"
#include <qlabel.h>
#include <qfont.h>
#include <qtooltip.h>
#include <qfiledialog.h>

#define X_SCALE         9
#define Y_SCALE         27

void XQtCards::CustomizeDialog(bool modal) {
    if (customize_dlg) {
//	customize_dlg->setFocus();
	customize_dlg->setActiveWindow();
	return;
    }
    QFont labelfont("helvetica", 14);
    QFont pushbfont("helvetica", 14); // , QFont::Bold);
    QFont effont("fixed", 12);


    customize_dlg = new QDialog(0, "XQtCards customizer", modal);
    customize_dlg->setFixedSize(67 * X_SCALE, 7 * Y_SCALE);
    customize_dlg->setCaption("XPat2: Change / Customize Graphics");

#if 0
    for (int i = 0; i < 7; ++i) {
	QLabel *tmp = new QLabel("I", customize_dlg);
	tmp->move(0, i * Y_SCALE);
	tmp->resize(8, 23);
	tmp->setFont(labelfont);
    }
#endif

    QLabel *text1 = new QLabel ("Card graphics directory:", customize_dlg);
    text1->move(X_SCALE, 0);
    text1->resize(X_SCALE * 64, 23);
    text1->setFont(labelfont);

    QLineEdit *edit1 = new QLineEdit(customize_dlg);
    edit1->setText(this->directory);
    edit1->move(X_SCALE, Y_SCALE);
    edit1->resize(X_SCALE * 64 + 8, 24);
    edit1->setFont(effont);
    customize_dlg_dir = edit1;

    QLabel *text2 = new QLabel ("Cardback number:", customize_dlg);
    text2->move(X_SCALE, 2 * Y_SCALE);
    text2->resize(X_SCALE * 32, 23);
    text2->setFont(labelfont);

    QMaskEdit *edit2 = new QMaskEdit(get_numcardbacks(), 0, customize_dlg);
    edit2->setText("0");
    edit2->move((65 - edit2->getFieldSize()) * X_SCALE, 2 * Y_SCALE);
    edit2->resize(X_SCALE * edit2->getFieldSize() + 8, 24);
    edit2->setFont(effont);
    edit2->setValue(currentcardback);
    customize_dlg_cbn = edit2;

    QPushButton *pb_apply  = new QPushButton("&Apply",   customize_dlg);
    QPushButton *pb_ok     = new QPushButton("&Ok",      customize_dlg);
    QPushButton *pb_cancel = new QPushButton("&Cancel",  customize_dlg);
    QPushButton *pb_reset  = new QPushButton("&Reset",   customize_dlg);
    QPushButton *pb_browse = new QPushButton("&Browse",  customize_dlg);

    pb_reset->move (  9, 5 * Y_SCALE);
    pb_ok->move    (305, 5 * Y_SCALE);
    pb_apply->move (404, 5 * Y_SCALE);
    pb_cancel->move(503, 5 * Y_SCALE);
    pb_browse->move(503, 0 * Y_SCALE);

    pb_ok    ->resize(10 * X_SCALE, 27);
    pb_cancel->resize(10 * X_SCALE, 27);
    pb_apply ->resize(10 * X_SCALE, 27);
    pb_reset ->resize(10 * X_SCALE, 27);
    pb_browse->resize(10 * X_SCALE, 27);

    pb_ok    ->setFont(pushbfont);
    pb_cancel->setFont(pushbfont);
    pb_apply ->setFont(pushbfont);
    pb_reset ->setFont(pushbfont);
    pb_browse->setFont(pushbfont);

    QToolTip::add(pb_ok,     "Apply any changes and close this window");
    QToolTip::add(pb_reset,  "Restore currently active values");
    QToolTip::add(pb_cancel, "Ignore any changes made and close this window");
    QToolTip::add(pb_apply,  "Apply any Changes and continue customizing");
    QToolTip::add(pb_browse, "Open directory selection dialog");

    connect(pb_ok,     SIGNAL(clicked()), this, SLOT(cards_ok()));
    connect(pb_apply,  SIGNAL(clicked()), this, SLOT(cards_apply()));
    connect(pb_cancel, SIGNAL(clicked()), this, SLOT(cards_cancel()));
    connect(pb_reset,  SIGNAL(clicked()), this, SLOT(cards_reset()));
    connect(pb_browse, SIGNAL(clicked()), this, SLOT(cards_browse()));

    customize_dlg->show();
    if (modal) {
	customize_dlg->exec();
	delete customize_dlg;
	customize_dlg = 0;
    }
}

void XQtCards::cards_reset() {
    customize_dlg_dir->setText(directory);
    customize_dlg_cbn->setValue(currentcardback);
}

void XQtCards::check_for_changes_and_apply() {
    bool changed = 0;
    if (strcmp(customize_dlg_dir->text(), directory)) {
	reloadGraphics(customize_dlg_dir->text());
	changed = TRUE;
    }
    
    int cardbackno = customize_dlg_cbn->value();
    if (cardbackno != 0 && cardbackno != currentcardback) {
	set_cardback(cardbackno);
	changed = TRUE;
    }
    if (changed)
	emit cards_changed();
}

void XQtCards::cards_apply() {
    check_for_changes_and_apply();
}

void XQtCards::cards_ok() {
    check_for_changes_and_apply();
    delete customize_dlg; //->accept();
    customize_dlg = 0;
}

void XQtCards::cards_cancel() {
    delete customize_dlg; // ->reject();
    customize_dlg = 0;
}

void XQtCards::cards_browse() {
    QFileDialog *fd = new QFileDialog(customize_dlg_dir->text(), 0, customize_dlg,
				      "xpm dir selection", TRUE);
#if 0	/* does the same */
    fd->setCaption("Select XPM directory");
    fd->setMode(QFileDialog::Directory);
    fd->exec();
    customize_dlg_dir->setText(fd->selectedFile());
    delete fd;
#else
    customize_dlg_dir->setText(QFileDialog::getExistingDirectory(
		customize_dlg_dir->text(), customize_dlg, "xpm dir selection"));
#endif
}
