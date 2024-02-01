/************************************************************************/
/* MODULE   : Xm-help.h                                                 */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/*          : Help window                                               */
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
/* 1.01  |19991106| adapted to xpat2-1.06                        | ac   */
/************************************************************************/

#ifndef XM_HELP_H
#define XM_HELP_H

#ifdef ONLINE_HELP

#define TXT_HELPFILES	(xpat_messages+71)	/* xpat2 1.06 */

extern Widget	shellDialogHelpText;
extern Widget	msgboxHelpText;
extern Widget	sepHelpText;
extern Widget	scrtextHelpText;
extern Widget	sbhorHelpText;
extern Widget	sbverHelpText;
extern Widget	textHelpText;
extern Widget	butHelpTextClose;


void	create_shellDialogHelpText (
	Widget	parent );
#endif

#endif /* XM_HELP_H */
