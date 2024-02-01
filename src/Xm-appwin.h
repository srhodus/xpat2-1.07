/************************************************************************/
/* MODULE   : Xm-appwin.h                                               */
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
/************************************************************************/

#ifndef XM_APPWIN_H
#define XM_APPWIN_H

extern Widget	shellMain;
extern Widget	formMain;
extern Widget	menubar;
extern Widget	cascadeGame;
extern Widget	menuGame;
extern Widget	butGameNew;
extern Widget	butGameLoad;
extern Widget	butGameSave;
extern Widget	sepGame;
extern Widget	butGameExit;
extern Widget	cascadeRules;
extern Widget	menuRules;
extern Widget	toggleRules[];
extern Widget	cascadeActions;
extern Widget	menuActions;
extern Widget	butActionsUndo;
extern Widget	butActionsRedo;
extern Widget	sepActions1;
extern Widget	butActionsReplay;
extern Widget	butActionsRestart;
extern Widget	sepActions2;
extern Widget	butActionsCards;
extern Widget	butActionsMovetostack;
extern Widget	cascadeOptions;
extern Widget	menuOptions;
#ifdef SOUND
extern Widget	toggleOptionsSound;
#endif
extern Widget	toggleOptionsToolbar;
extern Widget	sepOptions1;
extern Widget	butOptionsDropbookmark;
extern Widget	butOptionsGotobookmark;
extern Widget	cascadeHelp;
extern Widget	menuHelp;
#ifdef ONLINE_HELP
extern Widget	cascadeHelpRules;
extern Widget	menuHelpRules;
extern Widget	butHelpRules[];
extern Widget	butHelpKeys;
#endif
extern Widget	butHelpHint;
extern Widget	butHelpScore;
extern Widget	sepHelpText1;
extern Widget	butHelpLicense;
extern Widget	sepHelpText2;
extern Widget	butHelpAbout;
#ifdef FLAT_BUTTONS
extern Widget	frameToolbar;
#endif
extern Widget	rowcolToolbar;
extern Widget	butTbCards;
extern Widget	sepTb1;
extern Widget	butTbUndo;
extern Widget	butTbRedo;
extern Widget	sepTb2;
extern Widget	butTbReplay;
extern Widget	butTbRestart;
extern Widget	butTbMovetostack;
extern Widget	sepTb3;
extern Widget	butTbHint;
extern Widget	Tableau;
extern Widget	formFooter;
extern Widget	labelFooter;


void	create_shellMain (
	Display	*dpy, 
	char	*app_name, 
	int	app_argc, 
	char	**app_argv );

#endif /* XM_APPWIN_H */
