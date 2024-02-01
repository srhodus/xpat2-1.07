/* -*- C++ -*-	Time-stamp: <05 Nov 00 21:17:36 Michael Bischoff> */
/****************************************************************************
**
** application widget for XPat2
*****************************************************************************/

#include "XQtWindow.h"
#include "XQtTableau.h"

#include <qpixmap.h>
#include <qscrollview.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qkeycode.h>
// #include <qmultilinedit.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qapplication.h>
#include <qaccel.h>
#include <qtextstream.h>
#include <qpainter.h>
// #include <qpaintdevicemetrics.h>
#include <qwhatsthis.h>
#include "qhelpwin.h"
#include "version.h"

#include <stdio.h>
#include <stdarg.h>
extern "C" {
#include "xpatgame.h"
}

#include "filesave.xpm"
#include "fileopen.xpm"
// #include "undomove.xpm"
// #include "redomove.xpm"
#include "bbb.xpm"
#include "b.xpm"
#include "f.xpm"
#include "fff.xpm"
#include "dealcards.xpm"
#include "gethint.xpm"
#include "dohint.xpm"

#include "xpatgeo.h"

const char * fileSaveText = "Click this button to save the game you are "
"playing.  The file name will be generated automatically.\n\n"
"You can also select the Save command from the File menu.\n\n";
const char * fileOpenText = "Click this button to load a previously "
"saved game. You will be prompted for a file name.\n\n"
"You can also select the Open command from the File menu.\n\n";
const char * undoMoveText = "Click this button to undo your previous "
"move. Moves are kept from the beginning of the game.\n\n"
"Please note that this may increase your cheat count.\n\n";
const char * redoMoveText = "Click this button to undo your previous "
"undo.\n\n";
const char * restartGameText =
"Click this button to restart the same game from the beginning.\n\n"
"In most cases, this is considered as cheating, since you now "
"know which cards will be dealt where and when.\n";
const char * replayGameText =
"Click this button to replay the game until the end.\n\n"
"This is considered as a gimmick.";

static XQtXPat2Window *mainwin = 0;
static XQtTableau *tabl2 = 0;

extern "C" void Force_Resize(int w, int h) {
    int dw, dh;
    dw = mainwin->width() - mainwin->scrollView->width();
    dh = mainwin->height() - mainwin->scrollView->height();
    tabl2->resize(w, h);
    mainwin->resize(w + dw, h + dh);
}

int checksound(void) {
    return mainwin->getSound();
}

extern "C" void new_rules_coming(void) {
    tabl2->leave_rules();
}

extern "C" void new_rules_notify(void) {
    tabl2->enter_rules();
    mainwin->enter_rules();
    Force_Resize(geo.preferred_width, geo.preferred_height);
}

void XQtXPat2Window::enter_rules() {
    setCaption(rules.longname ? rules.longname: rules.shortname);
    
    // set buttons or menu items to enabled or disabled state
    tb_dc->setEnabled(rules.variant & NODEAL ? FALSE : TRUE);
    m_moves->setItemEnabled(icmd_dc, rules.variant & NODEAL ? FALSE : TRUE);
    m_moves->setItemEnabled(icmd_ru, FALSE);
    m_moves->setItemEnabled(icmd_rd, FALSE);
    int i;
    for (i = 0; i < 4; ++i)
	if (rules.paramstring[i] == TXTI_ROTATE) {
	    m_moves->setItemEnabled(icmd_ru, TRUE);
	    m_moves->setItemEnabled(icmd_rd, TRUE);
	}
}


XQtXPat2Window::XQtXPat2Window(const char *ruleset, long seed)
    : QMainWindow( 0, "XPat2 Qt version" ) {
    QPixmap saveIcon, openIcon, undoIcon, redoIcon, restartIcon, replayIcon;
    QPixmap dealcardsIcon, nexthintIcon, dohintIcon;
    mainwin = this;

    scrollView = new QScrollView(this, "scrollview");
    setCentralWidget( scrollView );
    tableau = new XQtTableau(ruleset, seed, scrollView, "tableau");
    scrollView->addChild(tableau);
    tabl2 = tableau;

    sound_on = TRUE;
    dragNdrop_on = FALSE;
    animation_on = TRUE;

    fileTools = new QToolBar( this, "file operations" );
    saveIcon      = QPixmap( filesave );
    openIcon      = QPixmap( fileopen );
    restartIcon   = QPixmap( bbb );
    undoIcon      = QPixmap( b );
    redoIcon      = QPixmap( f );
    replayIcon    = QPixmap( fff );
    dealcardsIcon = QPixmap( pic_dealcards );
    nexthintIcon  = QPixmap( pic_gethint );
    dohintIcon    = QPixmap( pic_dohint );
    //    undoIcon = QPixmap( undomove );
    //    redoIcon = QPixmap( redomove );

    QToolButton * fileSave = new QToolButton( saveIcon, "Save File", 0,
					      this, SLOT(QtCmd_SaveGame()),
					      fileTools, "save file" );
    QToolButton * fileOpen = new QToolButton( openIcon, "Open File", 0,
					      this, SLOT(QtCmd_LoadGame()),
					      fileTools, "open file" );
    fileTools->addSeparator();
    QToolButton * restartGame = new QToolButton( restartIcon, "Restart Game", 0,
					      this, SLOT(QtCmd_RestartGame()),
					      fileTools, "restart game" );
    QToolButton * undoMove    = new QToolButton( undoIcon, "Undo Move", 0,
					      this, SLOT(QtCmd_UndoMove()),
					      fileTools, "undo move" );
    QToolButton * redoMove    = new QToolButton( redoIcon, "Redo Move", 0,
					      this, SLOT(QtCmd_RedoMove()),
					      fileTools, "redo move" );
    QToolButton * replayGame  = new QToolButton( replayIcon, "Replay Game", 0,
					      this, SLOT(QtCmd_ReplayGame()),
					      fileTools, "replay game" );
    fileTools->addSeparator();
    QToolButton * dealcards   = new QToolButton( dealcardsIcon, "Deal Cards", 0,
					      this, SLOT(QtCmd_DealCards()),
					      fileTools, "deal cards" );
    tb_dc = dealcards;
    QToolButton * nexthint    = new QToolButton( nexthintIcon, "Suggest move", 0,
					      this, SLOT(QtCmd_NextHint()),
					      fileTools, "Next Hint" );
    QToolButton * dohint      = new QToolButton( dohintIcon, "Perform suggested move", 0,
					      this, SLOT(QtCmd_DoHint()),
					      fileTools, "Do Hint" );
    fileTools->addSeparator();


    (void)QWhatsThis::whatsThisButton( fileTools );
#if 0
    QWhatsThis::add( fileSave, fileSaveText, FALSE );
    QWhatsThis::add( fileOpen, fileOpenText, FALSE );
    QWhatsThis::add( undoMove, undoMoveText, FALSE );
    QWhatsThis::add( restartGame, restartGameText, FALSE );
    QWhatsThis::add( redoMove,    redoMoveText,    FALSE );
    QWhatsThis::add( undoMove,    undoMoveText,    FALSE );
    QWhatsThis::add( replayGame,  replayGameText,  FALSE );
#else
    QWhatsThis::add( fileSave,    fileSaveText);
    QWhatsThis::add( fileOpen,    fileOpenText);
    QWhatsThis::add( undoMove,    undoMoveText);
    QWhatsThis::add( restartGame, restartGameText);
    QWhatsThis::add( redoMove,    redoMoveText);
    QWhatsThis::add( undoMove,    undoMoveText);
    QWhatsThis::add( replayGame,  replayGameText);
#endif

    m_file = new QPopupMenu();
    menuBar()->insertItem( "&File", m_file );
    m_file->insertItem( saveIcon, "Save Game", this, SLOT(QtCmd_SaveGame()), CTRL+Key_S);
    m_file->insertItem( openIcon, "Load Game", this, SLOT(QtCmd_LoadGame()));
    m_file->insertItem( "Replay Game", this, SLOT(QtCmd_ReplayGame()));
    m_file->insertItem( "Restart Game", this, SLOT(QtCmd_RestartGame()), CTRL+Key_A);
    m_file->insertSeparator();
    m_file->insertItem( "New Game", this, SLOT(QtCmd_NewGame()), SHIFT+Key_N );
    m_file->insertItem( "Quit", qApp, SLOT(quit()), SHIFT+Key_Q );


    m_moves = new QPopupMenu();
    menuBar()->insertItem( "&Moves", m_moves );
    i_udo = m_moves->insertItem( "&Undo", this, SLOT(QtCmd_UndoMove()), CTRL+Key_U );
    i_rdo = m_moves->insertItem( "&Redo", this, SLOT(QtCmd_RedoMove()), CTRL+Key_R );
    m_moves->insertItem( "&Goto Bookmark", this, SLOT(QtCmd_GotoBM()), CTRL+Key_G );
    m_moves->insertItem( "&Drop Bookmark", this, SLOT(QtCmd_DropBM()), CTRL+Key_D );
    m_moves->insertItem( "Restart", this, SLOT(QtCmd_RestartGame()), CTRL+Key_A);
    m_moves->insertSeparator();
    icmd_dc = m_moves->insertItem( "Deal Cards", this, SLOT(QtCmd_DealCards()), Key_D);
    icmd_ru = m_moves->insertItem( "Rotate Up", this, SLOT(QtCmd_RotateUp()));
    icmd_rd = m_moves->insertItem( "Rotate Down", this, SLOT(QtCmd_RotateDown()));
    m_moves->insertItem( "All Moves",  this, SLOT(QtCmd_AllMoves()), Key_M);
    m_moves->insertItem( "Moves to Stacks", this, SLOT(QtCmd_AllToStack()), Key_S);

    m_rules = new QPopupMenu();
    menuBar()->insertItem( "&Rules", m_rules );
    m_rules->insertItem( "Spider",          this, SLOT(QtCmd_rSpider()),   ALT+Key_S);
    m_rules->insertItem( "Gypsy",           this, SLOT(QtCmd_rGypsy()),    ALT+Key_G);
    m_rules->insertItem( "Klondike",        this, SLOT(QtCmd_rKlondike()), ALT+Key_K);
    m_rules->insertItem( "Seahaven Towers", this, SLOT(QtCmd_rSHT()),      ALT+Key_H);
    m_rules->insertItem( "Free Cell",       this, SLOT(QtCmd_rFreeCell()), ALT+Key_F);
    m_rules->insertItem( "Idiot's Delight", this, SLOT(QtCmd_rIdiots()),   ALT+Key_I);
    m_rules->insertItem( "Monte Carlo",     this, SLOT(QtCmd_rMC()),       ALT+Key_M);
    m_rules->insertItem( "Midnight Oil",    this, SLOT(QtCmd_rMO()),       ALT+Key_O);
    m_rules->insertItem( "Calculation",     this, SLOT(QtCmd_rCalc()),     ALT+Key_Z);
    m_rules->insertItem( "mod. Canfield",   this, SLOT(QtCmd_rmodCan()),   ALT+Key_X);
    m_rules->insertItem( "Michael's Fantasy",this,SLOT(QtCmd_rMichaels()), ALT+Key_Y);
    m_rules->insertItem( "Canfield",        this, SLOT(QtCmd_rCanfield()), ALT+Key_T);
    m_rules->insertItem( "Royal Cotillion", this, SLOT(QtCmd_rRC()),       ALT+Key_R);
    m_rules->insertItem( "Baker's Dozen",   this, SLOT(QtCmd_rBakers()),   ALT+Key_B);
    m_rules->insertItem( "Oonsoo",          this, SLOT(QtCmd_rOonsoo()),   ALT+Key_O);
    m_rules->insertItem( "Blue Moon",       this, SLOT(QtCmd_rBluemoon()), ALT+Key_M);
//    m_rules->setCheckable( TRUE );

    m_controls = new QPopupMenu();
    i_mb = m_controls->insertItem( "Menu bar", this, SLOT(toggleMenuBar()), CTRL+Key_M);
    // Now an accelerator for when the menubar is invisible!
    QAccel* a = new QAccel(this);
    a->connectItem( a->insertItem( CTRL+Key_M ), this, SLOT(toggleMenuBar()) );
    i_tb = m_controls->insertItem( "Tool bar", this, SLOT(toggleToolBar()), CTRL+Key_T);
    i_sb = m_controls->insertItem( "Status bar", this, SLOT(toggleStatusBar()), CTRL+Key_B);

    m_misc = new QPopupMenu();
    menuBar()->insertItem( "&Options", m_misc );
    m_misc->insertItem( "&Controls", m_controls);
    i_snd = 
	m_misc->insertItem( "&Sound", this, SLOT(toggleSound()));
    m_misc->setCheckable( TRUE );
    m_misc->setItemChecked(i_snd, sound_on);
    i_dnd = 
	m_misc->insertItem( "Drag'n drop", this, SLOT(toggleDragNDrop()));
    m_misc->setCheckable( TRUE );
    m_misc->setItemChecked(i_dnd, dragNdrop_on);
    i_ani = 
	m_misc->insertItem( "Animation", this, SLOT(toggleAnimation()));
    m_misc->setCheckable( TRUE );
    m_misc->setItemChecked(i_ani, animation_on);

    m_misc->insertItem( "Customize Rules...");
//    m_misc->insertItem( "Change Graphics (modal)...", tableau, SLOT(CustomizeModal()));
    m_misc->insertItem( "Change Graphics (modeless)...", tableau, SLOT(CustomizeModeless()));

    m_controls->setCheckable( TRUE );
    m_controls->setItemChecked( i_mb, TRUE );
    m_controls->setItemChecked( i_tb, TRUE );
    m_controls->setItemChecked( i_sb, TRUE );

    m_windows = new QPopupMenu();
    menuBar()->insertItem( "&Window", m_windows );
    m_windows->insertItem( "Minimal Size",        this, SLOT(QtCmd_MinWindow()), SHIFT+Key_M);
    m_windows->insertItem( "Preferred Size",      this, SLOT(QtCmd_PrefWindow()), SHIFT+Key_P);
    m_windows->insertItem( "Adapt to outer Size", this, SLOT(QtCmd_AdaptWindow()), SHIFT+Key_A);
    m_windows->insertItem( "Redraw",              tableau, SLOT(repaintAll()),     CTRL+Key_L);

    menuBar()->insertSeparator();
    m_help = new QPopupMenu();
    menuBar()->insertItem( "&Help", m_help );
    m_help->insertItem( "About",               this, SLOT(about()));
    m_help->insertItem( "Help on Keys...",     this, SLOT(QtCmd_hlpKeys()));
    m_help->insertItem( "Help on Rules...",    this, SLOT(QtCmd_hlpRules()));
    m_help->insertSeparator();
    m_help->insertItem( "Info",                this, SLOT(QtCmd_Info()), Key_I);
    m_help->insertItem( "Show Score",          this, SLOT(QtCmd_ShowScore()), Key_S);
    m_help->insertItem( "Show Version",        this, SLOT(QtCmd_ShowVersion()), Key_V);
    m_help->insertItem( "Suggest Move",        this, SLOT(QtCmd_NextHint()), Key_Plus);
    m_help->insertItem( "Previous suggestion", this, SLOT(QtCmd_PrevHint()), Key_Minus);
    m_help->insertItem( "Do suggested Move",   this, SLOT(QtCmd_DoHint()), Key_Space);

    statusBar()->message( "Welcome to XPat2!", 2000 );
    tableau->dragndrop_on = dragNdrop_on;
    tableau->sound_on = sound_on;
    tableau->animation_on = animation_on;

    enter_rules();	// set enable/disable menu items and caption
    resize(800,600);
    scrollView->resizeContents(800,600);
}

extern "C" void show_message(const char *str, ...) {
    static char last_message[256];
    va_list args;
    va_start(args, str);

    if (!str) {
	memset(last_message, ' ', sizeof(last_message)-1);
	last_message[sizeof(last_message)-1] = '\0';
    } else
	vsprintf(last_message, str, args);

    mainwin->statusBar()->message(last_message);
}


XQtXPat2Window::~XQtXPat2Window() {
    delete tableau;	// others to do
}



void XQtXPat2Window::QtCmd_NewGame() {
    newgame(-1L);
    tableau->repaint();
}

void XQtXPat2Window::QtCmd_LoadGame() {
    QString fn = QFileDialog::getOpenFileName(0,0,this);
    if ( !fn.isEmpty() )
        load_game(fn);
    else
	statusBar()->message( "Loading aborted", 2000 );
}

void XQtXPat2Window::QtCmd_SaveGame() {
    cmd_SaveGame();
}


void XQtXPat2Window::toggleMenuBar() {
    if ( menuBar()->isVisible() ) {
	menuBar()->hide();
	m_controls->setItemChecked( i_mb, FALSE );
    } else {
	menuBar()->show();
	m_controls->setItemChecked( i_mb, TRUE );
    }
}

void XQtXPat2Window::toggleToolBar() {
    if ( fileTools->isVisible() ) {
	fileTools->hide();
	m_controls->setItemChecked( i_tb, FALSE );
    } else {
	fileTools->show();
	m_controls->setItemChecked( i_tb, TRUE );
    }
}
void XQtXPat2Window::toggleSound() {
    if ( sound_on ) {
	sound_on = FALSE;
    } else {
	sound_on = TRUE;
    }
    m_misc->setItemChecked( i_snd, sound_on);
    tableau->sound_on = sound_on;
}
void XQtXPat2Window::toggleDragNDrop() {
    if ( dragNdrop_on ) {
	dragNdrop_on = FALSE;
    } else {
	dragNdrop_on = TRUE;
    }
    m_misc->setItemChecked( i_dnd, dragNdrop_on);
    tableau->dragndrop_on = dragNdrop_on;
}
void XQtXPat2Window::toggleAnimation() {
    if ( animation_on ) {
	animation_on = FALSE;
    } else {
	animation_on = TRUE;
    }
    m_misc->setItemChecked( i_ani, animation_on);
    tableau->animation_on = animation_on;
}

void XQtXPat2Window::toggleStatusBar() {
    if ( statusBar()->isVisible() ) {
	statusBar()->hide();
	m_controls->setItemChecked( i_sb, FALSE );
    } else {
	statusBar()->show();
	m_controls->setItemChecked( i_sb, TRUE );
    }
}

void XQtXPat2Window::QtCmd_UndoMove() {
    cmd_UndoMove();
}
void XQtXPat2Window::QtCmd_RedoMove() {
    cmd_RedoMove();
}
void XQtXPat2Window::QtCmd_RestartGame() {
    cmd_RestartGame();
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_ReplayGame() {
    cmd_ReplayGame();
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_DropBM() {
    cmd_DropBookmark();
}
void XQtXPat2Window::QtCmd_GotoBM() {
    cmd_GotoBookmark();
}
void XQtXPat2Window::QtCmd_DealCards() {
    cmd_DealCards();
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_ShowScore() {
    cmd_ShowScore();
}
void XQtXPat2Window::QtCmd_ShowVersion() {
    cmd_ShowVersion();
}
void XQtXPat2Window::QtCmd_Info() {
    cmd_Info();
}
void XQtXPat2Window::QtCmd_AllToStack() {
    cmd_AllToStack();
}
void XQtXPat2Window::QtCmd_AllMoves() {
    cmd_AllMoves();
}
void XQtXPat2Window::QtCmd_NextHint() {
    cmd_NextHint();
}
void XQtXPat2Window::QtCmd_PrevHint() {
    cmd_PreviousHint();
}
void XQtXPat2Window::QtCmd_DoHint() {
    cmd_DoHint();
}
void XQtXPat2Window::QtCmd_RotateUp() {
    cmd_RotateUp();
}
void XQtXPat2Window::QtCmd_RotateDown() {
    cmd_RotateDown();
}
void XQtXPat2Window::QtCmd_MinWindow() {
    cmd_MinWindow();
}
void XQtXPat2Window::QtCmd_PrefWindow() {
    cmd_PreferredWindow();
}

void XQtXPat2Window::QtCmd_AdaptWindow() {
    int w, h;
    w = scrollView->width();
    h = scrollView->height();
    if (w < geo.min_width)
	w = geo.min_width;
    if (h < geo.min_height)
	h = geo.min_height;
// #ifdef useScrollView
    scrollView->resizeContents(w, h);
// #endif
    geo.w = w;
    geo.h = h;
    // init_layout();
    tableau->resize(w, h);
    cmd_Layout();
    tableau->repaint();
}


void XQtXPat2Window::QtCmd_rSpider() {
    change_rules("Spider");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rGypsy() {
    change_rules("Gypsy");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rKlondike() {
    change_rules("Klondike");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rSHT() {
    change_rules("Seahaven");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rFreeCell() {
    change_rules("Free Cell");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rIdiots() {
    change_rules("Idiot's Delight");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rMC() {
    change_rules("Monte Carlo");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rMO() {
    change_rules("Midnight Oil");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rCalc() {
    change_rules("Calculation");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rmodCan() {
    change_rules("modCanfield");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rMichaels() {
    change_rules("Michael's Fantasy");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rCanfield() {
    change_rules("Canfield");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rRC() {
    change_rules("Royal Cotillion");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rBakers() {
    change_rules("Baker's Dozen");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rOonsoo() {
    change_rules("Oonsoo");
    newgame(-1L);
    tableau->repaint();
}
void XQtXPat2Window::QtCmd_rBluemoon() {
    change_rules("Blue Moon");
    newgame(-1L);
    tableau->repaint();
}

void XQtXPat2Window::about() {
    QMessageBox::about( this, "XPat2 - Qt version",
                        "This is version " VERSION " of XPat2.\n"
                        "Qt user interface 1999 by M. Bischoff\n\n"
                        "Have fun!" );
}


extern "C" struct rules *rulepool[];

void XQtXPat2Window::QtCmd_hlpRules() {
    QHelpWindow *hw;
    char pathname[256];
    char caption[128];
    const char *langdir = get_lang();
    const char *helpfilename;
    int i = 0;

    /* find current rules */
    while (rulepool[i]) {
	if (!strcmp(rules.shortname, rulepool[i]->shortname))
	    break;
	++i;
    }
    if (!rulepool[i])
	return;	/* rules not found !? */
//    printf("selected rules %s, %s\n", rulepool[i]->shortname, xpat_messages[76+i]);
#if 0
    printf("[0] = %s\n", xpat_messages[0]);
    printf("[1] = %s\n", xpat_messages[1]);
    printf("[72] = %s, i = %d\n", xpat_messages[72], i);
#endif
    helpfilename = xpat_messages[76+i];
    
    if (strlen(langdir) + strlen(LIBDIR) + 3 + strlen(helpfilename)
	       <= sizeof(pathname) && *langdir) {
	/* langdir is set and buffer has sufficient size */
	sprintf(pathname, "%s/%s/%s", LIBDIR, langdir, helpfilename);
    } else {
        sprintf(pathname, "%s/%s", LIBDIR, helpfilename);
    }
    sprintf(caption, "XPat2: Help on the rules of %s", rulepool[i]->shortname);
    hw = new QHelpWindow(pathname, caption);
}

void XQtXPat2Window::QtCmd_hlpKeys() {
    QHelpWindow *hw;
    char pathname[256];
    const char *langdir = get_lang();

    if (strlen(langdir) + strlen(LIBDIR) + 12 <= sizeof(pathname)
	&& *langdir) {
	/* langdir is set and buffer has sufficient size */
	sprintf(pathname, "%s/%s/%s", LIBDIR, langdir, "help.keys");
    } else {
        sprintf(pathname, "%s/%s", LIBDIR, "help.keys");
    }
    hw = new QHelpWindow(pathname, "XPat2: Key bindings");
}
