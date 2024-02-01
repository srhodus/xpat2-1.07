/************************************************************************/
/* MODULE   : Xm-help.c                                                 */
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
/* 0.1   |19990213| Initial creation for xpat2-1.04              | ac   */
/************************************************************************/

#ifdef ONLINE_HELP
/* No real need for this ifdef. Module is in-/excluded in Makefile,     */
/* because Sun WorkShop C does not like empty translation units.        */

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MessageB.h>
#include <Xm/PushB.h>
#include <Xm/Text.h>

#include "Xm-cbstd.h"


/************************************************************************/
/*      Widget hierarchy                                                */
/************************************************************************/

/* Dialogbox "Help" */
/*           */
/*---------- */	Widget shellDialogHelpText		= (Widget) NULL;
/*  |        */
/*  |------- */	Widget msgboxHelpText			= (Widget) NULL;
/*    |      */
/*    |----- */	Widget sepHelpText			= (Widget) NULL;
/*    |----- */	Widget scrtextHelpText			= (Widget) NULL;
/*    | |--- */	Widget sbhorHelpText			= (Widget) NULL;
/*    | |--- */	Widget sbverHelpText			= (Widget) NULL;
/*    | |--- */	Widget textHelpText			= (Widget) NULL;
/*    |      */
/*    |----- */	Widget butHelpTextClose			= (Widget) NULL;


/************************************************************************/
/* FUNCTION : create_shellDialogHelpText                                */
/* LONGNAME : create Help Dialog                                        */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-02-27                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
void	create_shellDialogHelpText (
	Widget	parent )
{
  Widget	children[3];		/* Children to manage */
  Arg		al[64];			/* Argument List */
  register int	ac = 0;			/* Argument Count */
  XmString	xmstring;		/* temporary storage for XmStrings */

  XtSetArg(al[ac], XmNallowShellResize, TRUE);			ac++;
  XtSetArg(al[ac], XmNbaseWidth, 440);				ac++;
  XtSetArg(al[ac], XmNbaseHeight, 440);				ac++;
  shellDialogHelpText	= XmCreateDialogShell (parent, "shellDialogHelpText", al, ac);
  ac	= 0;

  XtSetArg(al[ac], XmNautoUnmanage, FALSE);			ac++;
  XtSetArg(al[ac], XmNdialogType, XmDIALOG_TEMPLATE);		ac++;
  msgboxHelpText	= XmCreateMessageBox (shellDialogHelpText, "msgboxHelpText", al, ac);
  ac	= 0;

  sepHelpText	= XmMessageBoxGetChild (msgboxHelpText, XmDIALOG_SEPARATOR);

  XtSetArg(al[ac], XmNeditable, FALSE);				ac++;
  XtSetArg(al[ac], XmNcursorPositionVisible, FALSE);		ac++;
  XtSetArg(al[ac], XmNeditMode, XmMULTI_LINE_EDIT);		ac++;
  textHelpText	= XmCreateScrolledText (msgboxHelpText, "textHelpText", al, ac);
  ac	= 0;

  scrtextHelpText	= XtParent (textHelpText);

  XtSetArg(al[ac], XmNhorizontalScrollBar, &sbhorHelpText);		ac++;
  XtSetArg(al[ac], XmNverticalScrollBar, &sbverHelpText);		ac++;
  XtGetValues(scrtextHelpText, al, ac);
  ac	= 0;

  butHelpTextClose	= XmCreatePushButton (msgboxHelpText, "butHelpTextClose", al, ac);
  ac	= 0;

  XtSetArg(al[ac], XmNdefaultButton, butHelpTextClose);		ac++;
  XtSetValues (msgboxHelpText,al, ac);
  ac	= 0;

  XtManageChild(textHelpText);

  /* callbacks for button "Close" */
  XtAddCallback (butHelpTextClose, XmNactivateCallback, CB_Unmanage, (XtPointer)&msgboxHelpText);
  children[ac++]	= butHelpTextClose;
  XtManageChildren(children, ac);
  ac	= 0;
}

#endif	/* ONLINE_HELP */
