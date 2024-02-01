/****************************************************************************
** $Id: application.h,v 1.5 1998/06/23 09:47:41 warwick Exp $
**
** Copyright (C) 1992-1998 Troll Tech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#ifndef XQTWINDOW_H
#define XQTWINDOW_H

#include <qmainwindow.h>
class QScrollView;
class QToolBar;
class QPopupMenu;
class QToolButton;

class XQtTableau;

class XQtXPat2Window: public QMainWindow {
    Q_OBJECT
public:
    XQtXPat2Window(const char *rules = 0, long seed = -1L);
    ~XQtXPat2Window();
    bool getSound() const	{ return sound_on; }
    void enter_rules();
    QScrollView *scrollView;

private slots:
    void QtCmd_NewGame();
    void QtCmd_SaveGame();
    void QtCmd_LoadGame();
    void QtCmd_UndoMove();
    void QtCmd_RedoMove();
    void QtCmd_RestartGame();
    void QtCmd_DropBM();
    void QtCmd_GotoBM();
    void QtCmd_DealCards();
    void QtCmd_ReplayGame();
    void QtCmd_ShowScore();
    void QtCmd_Info();
    void QtCmd_ShowVersion();
    void QtCmd_AllToStack();
    void QtCmd_AllMoves();
    void QtCmd_NextHint();
    void QtCmd_PrevHint();
    void QtCmd_DoHint();
    void QtCmd_MinWindow();
    void QtCmd_PrefWindow();
    void QtCmd_AdaptWindow();
    void QtCmd_RotateUp();
    void QtCmd_RotateDown();

    void QtCmd_rSpider();
    void QtCmd_rGypsy();
    void QtCmd_rKlondike();
    void QtCmd_rSHT();
    void QtCmd_rFreeCell();
    void QtCmd_rIdiots();
    void QtCmd_rMC();
    void QtCmd_rMO();
    void QtCmd_rCalc();
    void QtCmd_rmodCan();
    void QtCmd_rMichaels();
    void QtCmd_rCanfield();
    void QtCmd_rRC();
    void QtCmd_rBakers();
    void QtCmd_rOonsoo();
    void QtCmd_rBluemoon();

    void about();
    void toggleMenuBar();
    void toggleStatusBar();
    void toggleToolBar();
    void toggleSound();
    void toggleDragNDrop();
    void toggleAnimation();
    void QtCmd_hlpKeys();
    void QtCmd_hlpRules();

private:
    QToolBar *fileTools;
    QPopupMenu *m_file;
    QPopupMenu *m_moves;
    QPopupMenu *m_rules;
    QPopupMenu *m_controls;
    QPopupMenu *m_misc;
    QPopupMenu *m_windows;
    QPopupMenu *m_help;
    XQtTableau *tableau;
    /* menu item identifiers: */
    int i_mb, i_tb, i_sb, i_udo, i_rdo;
    int i_snd, i_dnd, i_ani;
    int icmd_ru, icmd_rd, icmd_dc;
    bool sound_on, dragNdrop_on, animation_on;
    QToolButton *tb_dc;
};


#endif
