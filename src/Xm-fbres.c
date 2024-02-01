/************************************************************************/
/* MODULE   : Xm-fbres.c                                                */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/*          : Fallback resources                                        */
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
/* 1.00  |19990213| Initial creation for xpat2-1.04              | ac   */
/*-------+--------+----------------------------------------------+------*/
/* 1.01  |19991018| Default resources for KDE and Gnome style    | ac   */
/*-------+--------+----------------------------------------------+------*/
/* 1.02  |19991106| adapted to xpat2-1.06                        | ac   */
/************************************************************************/


#include "X-pat.h"
#include "Xm-fbres.h"
#include "Xm-platform.h"
#include "version.h"


/************************************************************************/
/*      Fallback resources                                              */
/************************************************************************/
String	fallback_resources[] =
{ 
  /* default widget dimensions */
  "XPat.title:					X-Patience",
  "XPat.baseWidth:				585",
  "XPat.baseHeight:				505",
  "XPat.minWidth:				320",
  "XPat.minHeight:				240",

#ifdef ONLINE_HELP
  "XPat*shellDialogHelp.baseWidth:		400",
  "XPat*shellDialogHelp.baseHeight:		400",
  "XPat*shellDialogHelp.minWidth:		200",
  "XPat*shellDialogHelp.minHeight:		200",
#endif

#ifdef FLAT_BUTTONS
  "XPat*rowcolToolbar.marginHeight:		0",
  "XPat*rowcolToolbar.marginWidth:		0",
  "XPat*rowcolToolbar.spacing:			0",
  "XPat*butTbCards.marginHeight:		0",
  "XPat*butTbCards.marginWidth:			0",
  "XPat*butTbUndo.marginHeight:			0",
  "XPat*butTbUndo.marginWidth:			0",
  "XPat*butTbRedo.marginHeight:			0",
  "XPat*butTbRedo.marginWidth:			0",
  "XPat*butTbReplay.marginHeight:		0",
  "XPat*butTbReplay.marginWidth:		0",
  "XPat*butTbRestart.marginHeight:		0",
  "XPat*butTbRestart.marginWidth:		0",
  "XPat*butTbMovetostack.marginHeight:		0",
  "XPat*butTbMovetostack.marginWidth:		0",
  "XPat*butTbHint.marginHeight:			0",
  "XPat*butTbHint.marginWidth:			0",
#endif

#ifdef KDESTYLE
  "XPat*menubar.marginHeight:			3",
#endif

#ifdef GNOMESTYLE
  "XPat*menubar.marginHeight:			0",
  "XPat*sepTb1.separatorType:			SHADOW_ETCHED_IN",
  "XPat*sepTb1.width:				15",
  "XPat*sepTb1.margin:				14",
  "XPat*sepTb2.separatorType:			SHADOW_ETCHED_IN",
  "XPat*sepTb2.width:				15",
  "XPat*sepTb2.margin:				14",
  "XPat*sepTb3.separatorType:			SHADOW_ETCHED_IN",
  "XPat*sepTb3.width:				15",
  "XPat*sepTb3.margin:				14",
#else
  "XPat*sepTb1.separatorType:			NO_LINE",
  "XPat*sepTb1.width:				10",
  "XPat*sepTb2.separatorType:			NO_LINE",
  "XPat*sepTb2.width:				10",
  "XPat*sepTb3.separatorType:			NO_LINE",
  "XPat*sepTb3.width:				10",
#endif

  /* default font resources */
  "XPat.AboutText:	\
	-*-lucida sans-medium-r-normal-sans-14-*-*-*-*-*-*-*=Regular,\
	-*-new century schoolbook-bold-i-normal--18-*-*-*-*-*-*-*=BoldItalic",

  /* default string resources */
  "XPat*cascadeGame.labelString:		Game",
  "XPat*butGameNew.labelString:			New Game",
  "XPat*butGameLoad.labelString:		Load Game ...",
  "XPat*butGameSave.labelString:		Save Game ...",
  "XPat*butGameExit.labelString:		Exit",
  "XPat*cascadeRules.labelString:		Rules",
  "XPat*cascadeActions.labelString:		Actions",
  "XPat*butActionsUndo.labelString:		Undo",
  "XPat*butActionsRedo.labelString:		Redo",
  "XPat*butActionsReplay.labelString:		Replay",
  "XPat*butActionsRestart.labelString:		Restart",
  "XPat*butActionsCards.labelString:		Cards",
  "XPat*butActionsMovetostack.labelString:	Move to Stack",
  "XPat*cascadeOptions.labelString:		Options",
#ifdef SOUND
  "XPat*toggleOptionsSound.labelString:		Sound On",
#endif
  "XPat*toggleOptionsToolbar.labelString:	Show Toolbar",
  "XPat*butOptionsDropbookmark.labelString:	Drop Bookmark",
  "XPat*butOptionsGotobookmark.labelString:	Go to Bookmark",
  "XPat*cascadeHelp.labelString:		Help",
#ifdef ONLINE_HELP
  "XPat*cascadeHelpRules.labelString:		Help on Rules",
  "XPat*butHelpKeys.labelString:		Help on Keys ...",
#endif
  "XPat*butHelpHint.labelString:		Hint",
  "XPat*butHelpScore.labelString:		Score ...",
  "XPat*butHelpLicense.labelString:		License ...",
  "XPat*butHelpAbout.labelString:		About ...",
  "XPat*shellDialogFile.title:			Load Game",
  "XPat*fileselDialogFile.noMatchString:	No saved games.",
  "XPat*fileselDialogFile.Items.labelString:	Files",
  "XPat*fileselDialogFile.FilterLabel.labelString:	Filter",
  "XPat*fileselDialogFile.Dir.labelString:	Directories",
  "XPat*optmenuFileSetfilter.labelString:	Show Saved Games:",
  "XPat*butFileSetfilterAll.labelString:	All Games",
#ifdef ONLINE_HELP
  "XPat*shellDialogHelpText.title:		Help",
  "XPat*butHelpTextClose.labelString:		Close",
#endif
  "XPat*shellDialogHelpAbout.title:		About X-Patience",
  "XPat*labelHelpAboutVersion.labelString: 	X-Patience 2\\n"
						"Version " VERSION "\\n"
						"(Motif User Interface)\\n"
						"for " PLATFORM,
  "XPat*labelHelpAboutAuthors.labelString:	Game written by Heiko Eissfeldt and\\n"
						"Michael Bischoff (c) 1993-1999.\\n"
						"Motif GUI designed and created by\\n"
						"Christian Anzenberger (c) 1999.\\n"
						"See COPYRIGHT files for details.",
  "XPat*butHelpAboutVersion.labelString:	Version",
  "XPat*butHelpAboutAuthors.labelString:	Authors",
  "XPat*butHelpAboutClose.labelString:		Close",
  "XPat*shellDialogConfirm.title:		 ",
  "XPat*msgboxConfirm.MessageLabel.labelString:	Exit X-Patience?",
  "XPat*shellDialogError.title:			 ",
  "XPat*msgboxError.Cancel.labelString:		Dismiss",
  "XPat*msgboxError.MessageLabel.labelString:	Please select a saved game",


  /* default pixmap resources */
  "XPat.iconPixmap:				" FB_RES "Xpat2_icon_pm",
  "XPat*labelHelpAboutSymbol.labelPixmap:	" FB_RES "Xpat2_l_pm",
  "XPat*labelHelpAboutSymbolB.labelPixmap:	" FB_RES "Xpat2B_l_pm",

  "XPat*butTbCards.labelPixmap:			" FB_RES "DealCard_m_pm",
  "XPat*butTbUndo.labelPixmap:			" FB_RES "Undo_m_pm",
  "XPat*butTbUndo.labelInsensitivePixmap:	" FB_RES "UndoU_m_pm",
  "XPat*butTbRedo.labelPixmap:			" FB_RES "Redo_m_pm",
  "XPat*butTbRedo.labelInsensitivePixmap:	" FB_RES "RedoU_m_pm",
  "XPat*butTbReplay.labelPixmap:		" FB_RES "Replay_m_pm",
  "XPat*butTbReplay.labelInsensitivePixmap:	" FB_RES "ReplayU_m_pm",
  "XPat*butTbRestart.labelPixmap:		" FB_RES "Restart_m_pm",
  "XPat*butTbRestart.labelInsensitivePixmap:	" FB_RES "RestartU_m_pm",
  "XPat*butTbMovetostack.labelPixmap:		" FB_RES "ToStack_m_pm",
  "XPat*butTbHint.labelPixmap:			" FB_RES "Hint_m_pm",

  /* default Tableau resources */
  "XPat*Tableau.backingStore:			WhenMapped",
  "XPat*Tableau.keyboardFile:			keys",
  "XPat*Tableau.messageFile:			messages",
  "XPat*Tableau.background:			DarkOliveGreen4",
  "XPat*Tableau.arrowColor:			Gold",
  "XPat*Tableau.markColor:			Black",
  "XPat*Tableau.rules:				Klondike",
  "XPat*Tableau.rng:				1",
  NULL
};
