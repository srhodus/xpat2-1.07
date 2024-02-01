/************************************************************************/
/* MODULE   : Xm-about.h                                                */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/*          : Popup dialog "Help->About ..."                            */
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

#ifndef XM_ABOUT_H
#define XM_ABOUT_H

extern Widget	shellDialogHelpAbout;
extern Widget	msgboxHelpAbout;
extern Widget	sepHelpAbout;
extern Widget	formHelpAbout;
extern Widget	labelHelpAboutSymbol;
extern Widget	labelHelpAboutSymbolB;
extern Widget	labelHelpAboutText;
extern Widget	labelHelpAboutVersion;
extern Widget	labelHelpAboutAuthors;
extern Widget	butHelpAboutVersion;
extern Widget	butHelpAboutAuthors;
extern Widget	butHelpAboutClose;


void	create_shellDialogHelpAbout (
	Widget	parent );

#endif /* XM_ABOUT_H */
