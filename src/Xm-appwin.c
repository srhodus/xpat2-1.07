/************************************************************************/
/* MODULE   : Xm-appwin.c                                               */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/*          : Application main window                                   */
/* AUTHOR   : Christian Anzenberger                                     */
/* CONTACT  : christian.anzenberger@siemens.at                          */
/* CREATED  : 1999-02-13                                                */
/* NOTES    : see README.motif for details on release                   */
/*          : see COPYRIGHT.motif for details on copyright              */
/************************************************************************/
/* History of Change:                                                   */
/*-------+--------+----------------------------------------------+------*/
/*Version|  Date  | Changes                                      |Author*/
/*-------+--------+----------------------------------------------+------*/
/* 0.1   |19990213| Initial creation for xpat2-1.04              | ac   */
/*-------+--------+----------------------------------------------+------*/
/* 0.9   |19990701| First public snapshot                        | ac   */
/************************************************************************/


#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <Xm/Form.h>
#ifdef FLAT_BUTTONS
#include <Xm/Frame.h>
#endif
#include <Xm/CascadeB.h>
#include <Xm/Label.h>
#include <Xm/Protocols.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/Separator.h>
#include <Xm/ToggleB.h>

#include "Xm-main.h"
#include "Xm-pixmap.h"
#include "Xm-cbstd.h"
#include "Xm-cbapp.h"
#include "Xm-tbflatb.h"
#include "Xm-file.h"
#include "Xm-help.h"
#include "Xm-about.h"

#include "X-pat.h"
#include "Tableau.h"


/************************************************************************/
/*      Widget hierarchy                                                */
/************************************************************************/

/* Main Window */
/*             */
/*------------------ */	Widget shellMain		= (Widget) NULL;
/*  |                */
/*  |--------------- */	Widget formMain			= (Widget) NULL;
/*    |------------- */	Widget menubar			= (Widget) NULL;
/*    | |            */
/*    | |----------- */	Widget cascadeGame		= (Widget) NULL;
/*    | | |--------- */	Widget menuGame			= (Widget) NULL;
/*    | |   |------- */	Widget butGameNew		= (Widget) NULL;
/*    | |   |------- */	Widget butGameLoad		= (Widget) NULL;
/*    | |   |------- */	Widget butGameSave		= (Widget) NULL;
/*    | |   |------- */	Widget sepGame			= (Widget) NULL;
/*    | |   |------- */	Widget butGameExit		= (Widget) NULL;
/*    | |            */
/*    | |----------- */	Widget cascadeRules		= (Widget) NULL;
/*    | | |--------- */	Widget menuRules		= (Widget) NULL;
/*    | |   |-------    Widget toggleRules[1] */
/*    | |   |-------    Widget toggleRules[2] */
/*    | |   |-------    Widget      ....      */
/*    | |   |-------    Widget toggleRules[n] */
/*    | |            */ Widget toggleRules[MAXRULES];
/*    | |            */
/*    | |----------- */	Widget cascadeActions		= (Widget) NULL;
/*    | | |--------- */	Widget menuActions		= (Widget) NULL;
/*    | |   |------- */	Widget butActionsUndo		= (Widget) NULL;
/*    | |   |------- */	Widget butActionsRedo		= (Widget) NULL;
/*    | |   |------- */	Widget sepActions1		= (Widget) NULL;
/*    | |   |------- */	Widget butActionsReplay		= (Widget) NULL;
/*    | |   |------- */	Widget butActionsRestart	= (Widget) NULL;
/*    | |   |------- */	Widget sepActions2		= (Widget) NULL;
/*    | |   |------- */	Widget butActionsCards		= (Widget) NULL;
/*    | |   |------- */	Widget butActionsMovetostack	= (Widget) NULL;
/*    | |            */
/*    | |----------- */	Widget cascadeOptions		= (Widget) NULL;
/*    | | |--------- */	Widget menuOptions		= (Widget) NULL;
#ifdef SOUND
/*    | |   |------- */	Widget toggleOptionsSound	= (Widget) NULL;
#endif
/*    | |   |------- */	Widget toggleOptionsToolbar	= (Widget) NULL;
/*    | |   |------- */	Widget sepOptions1		= (Widget) NULL;
/*    | |   |------- */	Widget butOptionsDropbookmark	= (Widget) NULL;
/*    | |   |------- */	Widget butOptionsGotobookmark	= (Widget) NULL;
/*    | |            */
/*    | |----------- */	Widget cascadeHelp		= (Widget) NULL;
/*    |   |--------- */	Widget menuHelp			= (Widget) NULL;
#ifdef ONLINE_HELP
/*    |     |------- */	Widget cascadeHelpRules		= (Widget) NULL;
/*    |     | |----- */	Widget menuHelpRules		= (Widget) NULL;
/*    |     |   |---   	Widget butHelpRules[1] */
/*    |     |   |---   	Widget butHelpRules[2] */
/*    |     |   |---   	Widget      .....      */
/*    |     |   |---   	Widget butHelpRules[n] */
/*    |     |        */	Widget butHelpRules[MAXRULES];
/*    |     |        */
/*    |     |------- */	Widget butHelpKeys		= (Widget) NULL;
#endif
/*    |     |------- */	Widget butHelpHint		= (Widget) NULL;
/*    |     |------- */	Widget butHelpScore		= (Widget) NULL;
/*    |     |------- */	Widget sepHelpText1		= (Widget) NULL;
/*    |     |------- */	Widget butHelpLicense		= (Widget) NULL;
/*    |     |------- */	Widget sepHelpText2		= (Widget) NULL;
/*    |     |------- */	Widget butHelpAbout		= (Widget) NULL;
/*    |              */
#ifdef FLAT_BUTTONS
/*    |------------- */	Widget frameToolbar		= (Widget) NULL;
#endif
/*    | |----------- */	Widget rowcolToolbar		= (Widget) NULL;
/*    |   |--------- */	Widget butTbCards		= (Widget) NULL;
/*    |   |--------- */	Widget sepTb1			= (Widget) NULL;
/*    |   |--------- */	Widget butTbUndo		= (Widget) NULL;
/*    |   |--------- */	Widget butTbRedo		= (Widget) NULL;
/*    |   |--------- */	Widget sepTb2			= (Widget) NULL;
/*    |   |--------- */	Widget butTbReplay		= (Widget) NULL;
/*    |   |--------- */	Widget butTbRestart		= (Widget) NULL;
/*    |   |--------- */	Widget butTbMovetostack		= (Widget) NULL;
/*    |   |--------- */	Widget sepTb3			= (Widget) NULL;
/*    |   |--------- */	Widget butTbHint		= (Widget) NULL;
/*    |              */
/*    |------------- */	Widget Tableau			= (Widget) NULL;
/*    |              */
/*    |------------- */	Widget formFooter		= (Widget) NULL;
/*      |----------- */	Widget labelFooter		= (Widget) NULL;


/************************************************************************/
/* FUNCTION : create_shellMain                                          */
/* LONGNAME : create main application window                            */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-02-13                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
void	create_shellMain (
	Display	*dpy, 
	char	*app_name, 
	int	app_argc, 
	char	**app_argv )
{
  Widget	children[14];		/* Children to manage */
  Arg		al[64];			/* Argument List */
  register int	ac = 0;			/* Argument Count */
  XrmValue	from_value, to_value;	/* For resource conversion */
  Pixel		bg;			/* colour values for pixmaps */ 
  XmString	xmstring;		/* temporary storage for XmStrings */

  /**********************************************************************/
  /*    create widget hierarchy                                         */
  /**********************************************************************/

  /* create application main shell */

  XtSetArg (al[ac], XmNallowShellResize, TRUE);			ac++;
  XtSetArg (al[ac], XmNargc, app_argc);				ac++;
  XtSetArg (al[ac], XmNargv, app_argv);				ac++;
  XtSetArg (al[ac], XmNallowShellResize, TRUE);			ac++;
  shellMain	= XtAppCreateShell (app_name, "XPat", 
			applicationShellWidgetClass, dpy, al, ac);
  ac	= 0;

  /* confirm exit */
  XmAddWMProtocolCallback (shellMain,
				XmInternAtom(dpy, "WM_DELETE_WINDOW", False),
				CB_GameExit, (XtPointer)0);

  /* process extra command arguments */
  if (!(process_extra_args (app_argc, app_argv)))
    exit(0);

  /* initialize icon pixmap */
  init_icon_pixmap (shellMain, WhitePixel(dpy,0));

 
  /* set icon title and pixmap */
  XtSetArg (al[ac], XmNiconPixmap, pixmap_resources.pixmapIcon);	ac++;
  XtSetArg (al[ac], XmNiconName, "Xpat2");			ac++;
  XtSetValues (shellMain, al, ac);
  ac	= 0;


  /* create application main form  */

  XtSetArg (al[ac], XmNautoUnmanage, FALSE);			ac++;
  formMain	= XmCreateForm (shellMain, "formMain", al, ac);
  ac	= 0;


  /* create menubar */

#ifdef FLAT_BUTTONS
  XtSetArg (al[ac], XmNshadowThickness, 1);			ac++;
#endif
  menubar	= XmCreateMenuBar (formMain, "menubar", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  cascadeGame	= XmCreateCascadeButton (menubar, "cascadeGame", al, ac);
  ac	= 0;


  /* create pulldown menu "Game" */

  XtSetArg (al[ac], XmNtearOffModel, XmTEAR_OFF_DISABLED);	ac++;
  menuGame	= XmCreatePulldownMenu (menubar, "menuGame", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butGameNew	= XmCreatePushButton (menuGame, "butGameNew", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butGameLoad	= XmCreatePushButton (menuGame, "butGameLoad", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butGameSave	= XmCreatePushButton (menuGame, "butGameSave", al, ac);
  ac	= 0;

  sepGame	= XmCreateSeparator (menuGame, "sepGame", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butGameExit	= XmCreatePushButton (menuGame, "butGameExit", al, ac);
  ac	= 0;


  /* create pulldown menu "Rules" */

  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  cascadeRules	= XmCreateCascadeButton (menubar, "cascadeRules", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNtearOffModel, XmTEAR_OFF_DISABLED);	ac++;
  XtSetArg (al[ac], XmNradioBehavior, TRUE);			ac++;
  menuRules	= XmCreatePulldownMenu (menubar, "menuRules", al, ac);
  ac	= 0;

  /* Note: menu buttons are rule-dependant wigets and will be created later */


  /* create pulldown menu "Actions" */

  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  cascadeActions	= XmCreateCascadeButton (menubar, "cascadeActions", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNtearOffModel, XmTEAR_OFF_ENABLED);	ac++;
  menuActions	= XmCreatePulldownMenu (menubar, "menuActions", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNsensitive, FALSE);			ac++;
  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butActionsUndo	= XmCreatePushButton (menuActions, "butActionsUndo", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNsensitive, FALSE);			ac++;
  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butActionsRedo	= XmCreatePushButton (menuActions, "butActionsRedo", al, ac);
  ac	= 0;

  sepActions1	= XmCreateSeparator (menuActions, "sepActions1", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNsensitive, FALSE);			ac++;
  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butActionsReplay	= XmCreatePushButton (menuActions, "butActionsReplay", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNsensitive, FALSE);			ac++;
  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butActionsRestart	= XmCreatePushButton (menuActions, "butActionsRestart", al, ac);
  ac	= 0;

  sepActions2	= XmCreateSeparator (menuActions, "sepActions2", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butActionsCards	= XmCreatePushButton (menuActions, "butActionsCards", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butActionsMovetostack	= XmCreatePushButton (menuActions, "butActionsMovetostack", al, ac);
  ac	= 0;


  /* create pulldown menu "Options" */

  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  cascadeOptions	= XmCreateCascadeButton (menubar, "cascadeOptions", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNtearOffModel, XmTEAR_OFF_DISABLED);	ac++;
  menuOptions	= XmCreatePulldownMenu (menubar, "menuOptions", al, ac);
  ac	= 0;

#ifdef SOUND
  XtSetArg (al[ac], XmNset, TRUE);				ac++;
  toggleOptionsSound	= XmCreateToggleButton (menuOptions, "toggleOptionsSound", al, ac);
  ac	= 0;
#endif

  XtSetArg (al[ac], XmNset, TRUE);				ac++;
  toggleOptionsToolbar	= XmCreateToggleButton (menuOptions, "toggleOptionsToolbar", al, ac);
  ac	= 0;

  sepOptions1	= XmCreateSeparator (menuOptions, "sepOptions1", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butOptionsDropbookmark	= XmCreatePushButton (menuOptions, "butOptionsDropbookmark", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNsensitive, FALSE);			ac++;
  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butOptionsGotobookmark	= XmCreatePushButton (menuOptions, "butOptionsGotobookmark", al, ac);
  ac	= 0;


  /* create pulldown menu "Help" */

  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  cascadeHelp	= XmCreateCascadeButton (menubar, "cascadeHelp", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNtearOffModel, XmTEAR_OFF_DISABLED);	ac++;
  menuHelp	= XmCreatePulldownMenu (menubar, "menuHelp", al, ac);
  ac	= 0;


#ifdef ONLINE_HELP
  /* create pulldown submenu "Help on Rules" */

  cascadeHelpRules	= XmCreateCascadeButton (menuHelp, "cascadeHelpRules", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNtearOffModel, XmTEAR_OFF_DISABLED);	ac++;
  menuHelpRules	= XmCreatePulldownMenu (menuHelp, "menuHelpRules", al, ac);
  ac	= 0;

  /* Note: menu buttons are rule-dependant wigets and will be created later */


  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butHelpKeys	= XmCreatePushButton (menuHelp, "butHelpKeys", al, ac);
  ac	= 0;
#endif

  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butHelpHint	= XmCreatePushButton (menuHelp, "butHelpHint", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butHelpScore	= XmCreatePushButton (menuHelp, "butHelpScore", al, ac);
  ac	= 0;

  sepHelpText1	= XmCreateSeparator (menuHelp, "sepHelpText1", al, ac);
  ac	= 0;

  butHelpLicense	= XmCreatePushButton (menuHelp, "butHelpLicense", al, ac);
  ac	= 0;

  sepHelpText2	= XmCreateSeparator (menuHelp, "sepHelpText2", al, ac);
  ac	= 0;
  
  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  butHelpAbout	= XmCreatePushButton (menuHelp, "butHelpAbout", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNmenuHelpWidget, cascadeHelp);		ac++;
  XtSetValues (menubar, al, ac);
  ac	= 0;


  /* create toolbar */

#ifdef FLAT_BUTTONS
  XtSetArg (al[ac], XmNshadowThickness, 1);			ac++;
  XtSetArg (al[ac], XmNshadowType, XmSHADOW_OUT);		ac++;
  frameToolbar	= XmCreateFrame (formMain, "frameToolbar", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNorientation, XmHORIZONTAL);		ac++;
  rowcolToolbar	= XmCreateRowColumn (frameToolbar, "rowcolToolbar", al, ac);
  ac	= 0;
#else

  XtSetArg (al[ac], XmNorientation, XmHORIZONTAL);		ac++;
  rowcolToolbar	= XmCreateRowColumn (formMain, "rowcolToolbar", al, ac);
  ac	= 0;
#endif

  XtSetArg (al[ac], XmNbackground, &bg);			ac++;
  XtGetValues (rowcolToolbar, al, ac);
  ac	= 0;

 
  /* toolbar button "Cards" */
  XtSetArg (al[ac], XmNtraversalOn, FALSE);			ac++;
  XtSetArg (al[ac], XmNlabelType, XmPIXMAP);			ac++;
  butTbCards	= XmCreatePushButton (rowcolToolbar, "butTbCards", al, ac);
  ac	= 0;

  /* toolbar separator */
  XtSetArg (al[ac], XmNorientation, XmVERTICAL);	ac++;
  sepTb1	= XmCreateSeparator (rowcolToolbar, "sepTb1", al, ac);
  ac	= 0;

  /* toolbar button "Undo" */
  XtSetArg (al[ac], XmNtraversalOn, FALSE);			ac++;
  XtSetArg (al[ac], XmNsensitive, FALSE);			ac++;
  XtSetArg (al[ac], XmNlabelType, XmPIXMAP);			ac++;
  butTbUndo	= XmCreatePushButton (rowcolToolbar, "butTbUndo", al, ac);
  ac	= 0;

  /* toolbar button "Redo" */
  XtSetArg (al[ac], XmNtraversalOn, FALSE);			ac++;
  XtSetArg (al[ac], XmNsensitive, FALSE);			ac++;
  XtSetArg (al[ac], XmNlabelType, XmPIXMAP);			ac++;
  butTbRedo	= XmCreatePushButton (rowcolToolbar, "butTbRedo", al, ac);
  ac	= 0;

  /* toolbar separator */
  XtSetArg (al[ac], XmNorientation, XmVERTICAL);	ac++;
  sepTb2	= XmCreateSeparator (rowcolToolbar, "sepTb2", al, ac);
  ac	= 0;

  /* toolbar button "Replay" */
  XtSetArg (al[ac], XmNtraversalOn, FALSE);			ac++;
  XtSetArg (al[ac], XmNsensitive, FALSE);			ac++;
  XtSetArg (al[ac], XmNlabelType, XmPIXMAP);			ac++;
  butTbReplay	= XmCreatePushButton (rowcolToolbar, "butTbReplay", al, ac);
  ac	= 0;

  /* toolbar button "Restart" */
  XtSetArg (al[ac], XmNtraversalOn, FALSE);			ac++;
  XtSetArg (al[ac], XmNsensitive, FALSE);			ac++;
  XtSetArg (al[ac], XmNlabelType, XmPIXMAP);			ac++;
  butTbRestart	= XmCreatePushButton (rowcolToolbar, "butTbRestart", al, ac);
  ac	= 0;

  /* toolbar button "Move to Stack" */
  XtSetArg (al[ac], XmNtraversalOn, FALSE);			ac++;
  XtSetArg (al[ac], XmNlabelType, XmPIXMAP);			ac++;
  butTbMovetostack	= XmCreatePushButton (rowcolToolbar, "butTbMovetostack", al, ac);
  ac	= 0;

  /* toolbar separator */
  XtSetArg (al[ac], XmNorientation, XmVERTICAL);	ac++;
  sepTb3	= XmCreateSeparator (rowcolToolbar, "sepTb3", al, ac);
  ac	= 0;

  /* toolbar button "Hint" */
  XtSetArg (al[ac], XmNtraversalOn, FALSE);			ac++;
  XtSetArg (al[ac], XmNalignment, XmALIGNMENT_CENTER);		ac++;
  XtSetArg (al[ac], XmNlabelType, XmPIXMAP);			ac++;
  butTbHint	= XmCreatePushButton (rowcolToolbar, "butTbHint", al, ac);
  ac	= 0;


  /* initialize button pixmaps */
  init_toolbar_pixmaps (shellMain, bg);

  XtSetArg (al[ac], XmNlabelPixmap, pixmap_resources.pixmapDealCard);	ac++;
  XtSetValues (butTbCards, al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelPixmap, pixmap_resources.pixmapUndo);	ac++;
  XtSetArg (al[ac], XmNlabelInsensitivePixmap, pixmap_resources.pixmapUndoU);	ac++;
  XtSetValues (butTbUndo, al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelPixmap, pixmap_resources.pixmapRedo);	ac++;
  XtSetArg (al[ac], XmNlabelInsensitivePixmap, pixmap_resources.pixmapRedoU);	ac++;
  XtSetValues (butTbRedo, al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelPixmap, pixmap_resources.pixmapReplay);	ac++;
  XtSetArg (al[ac], XmNlabelInsensitivePixmap, pixmap_resources.pixmapReplayU);	ac++;
  XtSetValues (butTbReplay, al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelPixmap, pixmap_resources.pixmapRestart);	ac++;
  XtSetArg (al[ac], XmNlabelInsensitivePixmap, pixmap_resources.pixmapRestartU);	ac++;
  XtSetValues (butTbRestart, al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelPixmap, pixmap_resources.pixmapToStack);	ac++;
  XtSetValues (butTbMovetostack, al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelPixmap, pixmap_resources.pixmapHint);	ac++;
  XtSetValues (butTbHint, al, ac);
  ac	= 0;

  /* create drawing area (for cards) */

#if 0
  if (DefaultDepthOfScreen (DefaultScreenOfDisplay (dpy)) != 1)
  {
    from_value.addr	= "DarkOliveGreen4";
    from_value.size	= strlen (from_value.addr) + 1;
    to_value.addr	= NULL;
    XtConvertAndStore (formMain, XmRString, &from_value, XmRPixel, &to_value);
    if (to_value.addr)
    {
      XtSetArg (al[ac], XmNbackground, * (unsigned int *)to_value.addr);	ac++;
    }
  }
#endif
  Tableau	= XtCreateWidget("desktop", tableauWidgetClass, formMain, al, ac);
  ac	= 0;


  /* create footer (for messages) */

  XtSetArg (al[ac], XmNmarginWidth, 0);				ac++;
  XtSetArg (al[ac], XmNmarginHeight, 0);			ac++;
  XtSetArg (al[ac], XmNresizePolicy, XmRESIZE_GROW);		ac++;
  formFooter	= XmCreateForm (formMain, "formFooter", al, ac);
  ac	= 0;

  /* create message area */
  XtSetArg (al[ac], XmNalignment, XmALIGNMENT_BEGINNING);	ac++;
  XtSetArg (al[ac], XmNlabelType, XmSTRING);			ac++;
  XtSetArg (al[ac], XmNrecomputeSize, TRUE);			ac++;
  labelFooter	= XmCreateLabel (formFooter, "labelFooter", al, ac);
  ac	= 0;


  /**********************************************************************/
  /*    create rule-dependant widgets                                   */
  /**********************************************************************/
  {
    struct rules	**rp;
    char	widgetname[32];

    for (rp = rulepool; *rp; rp++)
    {
      int	index = rp-rulepool;

      if (MAXRULES <= index)
        break;	/* max. number of rules reached */

      /* create toggle-buttons (radio box behaviour) */
      xmstring	= XmStringCreateLtoR ((char *)((*rp)->shortname), (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
      XtSetArg (al[ac], XmNlabelString, xmstring);		ac++;
      XtSetArg (al[ac], XmNindicatorType, XmONE_OF_MANY);	ac++;
      sprintf(widgetname, "toggleRules%d", index+1);
      toggleRules[index]	= XmCreateToggleButton (menuRules, widgetname, al, ac);
      ac	= 0;

      XtAddCallback (toggleRules[index], XmNvalueChangedCallback, CB_ToggleRules,
				(XtPointer)((*rp)->shortname));
      XtManageChild (toggleRules[index]);

#ifdef ONLINE_HELP
      /* create menuitem buttons */
      XtSetArg (al[ac], XmNlabelString, xmstring);		ac++;
      XtSetArg (al[ac], XmNlabelType, XmSTRING);		ac++;
      sprintf(widgetname, "butHelpRules%d", index+1);
      butHelpRules[index]	= XmCreatePushButton (menuHelpRules, widgetname, al, ac);
      ac	= 0;
      XmStringFree (xmstring);

      XtAddCallback (butHelpRules[index], XmNactivateCallback, CB_HelpText,
				(XtPointer)(TXT_HELPFILES[index+5]));
      XtManageChild (butHelpRules[index]);
#endif
    }
  }

  XtSetArg (al[ac], XmNsubMenuId, menuRules);			ac++;
  XtSetValues (cascadeRules, al, ac);
  ac	= 0;

#ifdef ONLINE_HELP
  XtSetArg (al[ac], XmNsubMenuId, menuHelpRules);		ac++;
  XtSetValues (cascadeHelpRules, al, ac);
  ac	= 0;
#endif


  /**********************************************************************/
  /*    define widget geometry                                          */
  /**********************************************************************/

  /* attachments for menubar */
  XtSetArg (al[ac], XmNtopAttachment, XmATTACH_FORM);		ac++;
  XtSetArg (al[ac], XmNbottomAttachment, XmATTACH_NONE);	ac++;
  XtSetArg (al[ac], XmNleftAttachment, XmATTACH_FORM);		ac++;
  XtSetArg (al[ac], XmNrightAttachment, XmATTACH_FORM);		ac++;
  XtSetValues (menubar, al, ac);
  ac	= 0;

  /* attachments for toolbar */
  XtSetArg (al[ac], XmNtopAttachment, XmATTACH_WIDGET);		ac++;
  XtSetArg (al[ac], XmNtopWidget, menubar);			ac++;
  XtSetArg (al[ac], XmNbottomAttachment, XmATTACH_NONE);	ac++;
  XtSetArg (al[ac], XmNleftAttachment, XmATTACH_FORM);		ac++;
  XtSetArg (al[ac], XmNrightAttachment, XmATTACH_FORM);		ac++;
#ifdef FLAT_BUTTONS
  XtSetValues (frameToolbar, al, ac);
#else
  XtSetValues (rowcolToolbar, al, ac);
#endif
  ac	= 0;

  /* attachments for card drawing area */
  XtSetArg (al[ac], XmNtopAttachment, XmATTACH_WIDGET);		ac++;
#ifdef FLAT_BUTTONS
  XtSetArg (al[ac], XmNtopWidget, frameToolbar);		ac++;
#else
  XtSetArg (al[ac], XmNtopWidget, rowcolToolbar);		ac++;
#endif
  XtSetArg (al[ac], XmNbottomAttachment, XmATTACH_WIDGET);	ac++;
  XtSetArg (al[ac], XmNbottomWidget, formFooter);		ac++;
  XtSetArg (al[ac], XmNleftAttachment, XmATTACH_FORM);		ac++;
  XtSetArg (al[ac], XmNrightAttachment, XmATTACH_FORM);		ac++;
  XtSetValues (Tableau, al, ac);
  ac	= 0;

  /* attachments for message area */
  XtSetArg (al[ac], XmNtopAttachment, XmATTACH_NONE);		ac++;
  XtSetArg (al[ac], XmNbottomAttachment, XmATTACH_FORM);	ac++;
  XtSetArg (al[ac], XmNleftAttachment, XmATTACH_FORM);		ac++;
  XtSetArg (al[ac], XmNrightAttachment, XmATTACH_FORM);		ac++;
  XtSetValues (formFooter, al, ac);
  ac	= 0;


  /**********************************************************************/
  /*    define callback functions and manage widgets                    */
  /**********************************************************************/

  /* callbacks for menubar */

  XtAddCallback (butGameNew, XmNactivateCallback, CB_GameNew, (XtPointer)0);
  XtAddCallback (butGameLoad, XmNactivateCallback, CB_Manage, (XtPointer)&fileselDialogFile);
  XtAddCallback (butGameSave, XmNactivateCallback, CB_GameSave, (XtPointer)0);
  XtAddCallback (butGameExit, XmNactivateCallback, CB_GameExit, (XtPointer)0);
  children[ac++]	= butGameNew;
  children[ac++]	= butGameLoad;
  children[ac++]	= butGameSave;
  children[ac++]	= sepGame;
  children[ac++]	= butGameExit;
  XtManageChildren (children, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNsubMenuId, menuGame);			ac++;
  XtSetValues (cascadeGame, al, ac);
  ac	= 0;

  XtAddCallback (butActionsUndo, XmNactivateCallback, CB_ActionsUndo, (XtPointer)0);
  XtAddCallback (butActionsRedo, XmNactivateCallback, CB_ActionsRedo, (XtPointer)0);
  XtAddCallback (butActionsReplay, XmNactivateCallback, CB_ActionsReplay, (XtPointer)0);
  XtAddCallback (butActionsRestart, XmNactivateCallback, CB_ActionsRestart, (XtPointer)0);
  XtAddCallback (butActionsCards, XmNactivateCallback, CB_ActionsDeal, (XtPointer)0);
  XtAddCallback (butActionsMovetostack, XmNactivateCallback, CB_ActionsMovetostack, (XtPointer)0);
  children[ac++]	= butActionsUndo;
  children[ac++]	= butActionsRedo;
  children[ac++]	= sepActions1;
  children[ac++]	= butActionsReplay;
  children[ac++]	= butActionsRestart;
  children[ac++]	= sepActions2;
  children[ac++]	= butActionsCards;
  children[ac++]	= butActionsMovetostack;
  XtManageChildren (children, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNsubMenuId, menuActions);			ac++;
  XtSetValues (cascadeActions, al, ac);
  ac	= 0;

  XtAddCallback (toggleOptionsToolbar, XmNvalueChangedCallback, CB_OptionsToolbar, (XtPointer)0);
  XtAddCallback (butOptionsDropbookmark, XmNactivateCallback, CB_OptionsDropbookmark, (XtPointer)0);
  XtAddCallback (butOptionsGotobookmark, XmNactivateCallback, CB_OptionsGotobookmark, (XtPointer)0);
#ifdef SOUND
  children[ac++]	= toggleOptionsSound;
#endif
  children[ac++]	= toggleOptionsToolbar;
  children[ac++]	= sepOptions1;
  children[ac++]	= butOptionsDropbookmark;
  children[ac++]	= butOptionsGotobookmark;
  XtManageChildren (children, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNsubMenuId, menuOptions);			ac++;
  XtSetValues (cascadeOptions, al, ac);
  ac	= 0;


#ifdef ONLINE_HELP
  XtAddCallback (butHelpKeys, XmNactivateCallback, CB_HelpText,
			(XtPointer)TXT_HELPFILES[0]);
#endif
  XtAddCallback (butHelpHint, XmNactivateCallback, CB_HelpHint, (XtPointer)0);
  XtAddCallback (butHelpScore, XmNactivateCallback, CB_HelpScore, (XtPointer)0);
/*
  XtAddCallback (butHelpLicense, XmNactivateCallback, CB_HelpLicense, (XtPointer)0);
*/
  XtAddCallback (butHelpAbout, XmNactivateCallback, CB_Manage, (XtPointer)&msgboxHelpAbout);
#ifdef ONLINE_HELP
  children[ac++]	= cascadeHelpRules;
  children[ac++]	= butHelpKeys;
#endif
  children[ac++]	= butHelpHint;
  children[ac++]	= butHelpScore;
  children[ac++]	= sepHelpText1;
  children[ac++]	= butHelpLicense;
  children[ac++]	= sepHelpText2;
  children[ac++]	= butHelpAbout;
  XtManageChildren (children, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNsubMenuId, menuHelp);			ac++;
  XtSetValues (cascadeHelp, al, ac);
  ac	= 0;


  children[ac++]	= cascadeGame;
  children[ac++]	= cascadeRules;
  children[ac++]	= cascadeActions;
  children[ac++]	= cascadeOptions;
  children[ac++]	= cascadeHelp;
  XtManageChildren (children, ac);
  ac	= 0;

  /* callbacks for toolbar */
  
  XtAddCallback (butTbCards, XmNactivateCallback, CB_ActionsDeal, (XtPointer)0);
#ifdef FLAT_BUTTONS
  add_flatButtonCB(butTbCards);
#endif
  XtAddCallback (butTbUndo, XmNactivateCallback, CB_ActionsUndo, (XtPointer)0);
#ifdef FLAT_BUTTONS
  add_flatButtonCB(butTbUndo);
#endif
  XtAddCallback (butTbRedo, XmNactivateCallback, CB_ActionsRedo, (XtPointer)0);
#ifdef FLAT_BUTTONS
  add_flatButtonCB(butTbRedo);
#endif
  XtAddCallback (butTbReplay, XmNactivateCallback, CB_ActionsReplay, (XtPointer)0);
#ifdef FLAT_BUTTONS
  add_flatButtonCB(butTbReplay);
#endif
  XtAddCallback (butTbRestart, XmNactivateCallback, CB_ActionsRestart, (XtPointer)0);
#ifdef FLAT_BUTTONS
  add_flatButtonCB(butTbRestart);
#endif
  XtAddCallback (butTbMovetostack, XmNactivateCallback, CB_ActionsMovetostack, (XtPointer)0);
#ifdef FLAT_BUTTONS
  add_flatButtonCB(butTbMovetostack);
#endif
  XtAddCallback (butTbHint, XmNactivateCallback, CB_HelpHint, (XtPointer)0);
#ifdef FLAT_BUTTONS
  add_flatButtonCB(butTbHint);
#endif
  children[ac++]	= butTbCards;
  children[ac++]	= sepTb1;
  children[ac++]	= butTbUndo;
  children[ac++]	= butTbRedo;
  children[ac++]	= sepTb2;
  children[ac++]	= butTbReplay;
  children[ac++]	= butTbRestart;
  children[ac++]	= butTbMovetostack;
  children[ac++]	= sepTb3;
  children[ac++]	= butTbHint;
  XtManageChildren (children, ac);
  ac	= 0;

#ifdef FLAT_BUTTONS
  children[ac++]	= rowcolToolbar;
  XtManageChildren(children, ac);
  ac	= 0;
#endif

  XtSetArg (al[ac], XmNtopAttachment, XmATTACH_FORM);		ac++;
  XtSetArg (al[ac], XmNtopOffset, 1);				ac++;
  XtSetArg (al[ac], XmNbottomAttachment, XmATTACH_FORM);	ac++;
  XtSetArg (al[ac], XmNleftAttachment, XmATTACH_FORM);		ac++;
  XtSetArg (al[ac], XmNrightAttachment, XmATTACH_FORM);		ac++;
  XtSetValues (labelFooter, al, ac);
  ac	= 0;

  children[ac++]	= labelFooter;
  XtManageChildren (children, ac);
  ac	= 0;

  children[ac++]	= menubar;
#ifdef FLAT_BUTTONS
  children[ac++]	= frameToolbar;
#else
  children[ac++]	= rowcolToolbar;
#endif
  children[ac++]	= Tableau;
  children[ac++]	= formFooter;
  XtManageChildren (children, ac);
  ac	= 0;

  XtManageChild (formMain);
}
