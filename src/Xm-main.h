/************************************************************************/
/* MODULE   : Xm-main.h                                                 */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
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

#ifndef XM_MAIN_H
#define XM_MAIN_H

#define	MAXRULES	32	/* max. number of rules */


extern Display		*dpy;
extern struct rules	*rulepool[];

extern XtAppContext	app_context;
extern Window		mainwindow;
extern Window		table;
extern char		*loadfilename;

#endif /* XM_MAIN_H */
