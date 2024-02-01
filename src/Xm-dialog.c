/************************************************************************/
/* MODULE   : Xm-dialog.c                                               */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/* AUTHOR   : Christian Anzenberger                                     */
/*          : Popup dialogs                                             */
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

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MessageB.h>

#include "Xm-cbstd.h"
#include "Xm-dialog.h"


int	response;


/************************************************************************/
/*      Widget hierarchy                                                */
/************************************************************************/

/* Modal Confirmation Dialog */
/*           */
/*---------- */	Widget shellDialogConfirm		= (Widget) NULL;
/*  |        */
/*  |------- */	Widget msgboxConfirm			= (Widget) NULL;
/*    |      */
/*    |----- */	Widget butConfirmCancel			= (Widget) NULL;
/*    |----- */	Widget butConfirmHelp			= (Widget) NULL;
/*    |----- */	Widget labelConfirmText			= (Widget) NULL;
/*    |----- */	Widget butConfirmOk			= (Widget) NULL;
/*    |----- */	Widget sepConfirm			= (Widget) NULL;
/*    |----- */	Widget labelConfirmSymbol		= (Widget) NULL;

/* Modal Error Dialog */
/*           */
/*---------- */	Widget shellDialogError			= (Widget) NULL;
/*  |        */
/*  |------- */	Widget msgboxError			= (Widget) NULL;
/*    |      */
/*    |----- */	Widget butErrorCancel			= (Widget) NULL;
/*    |----- */	Widget butErrorHelp			= (Widget) NULL;
/*    |----- */	Widget labelErrorText			= (Widget) NULL;
/*    |----- */	Widget butErrorOk			= (Widget) NULL;
/*    |----- */	Widget sepError				= (Widget) NULL;
/*    |----- */	Widget labelErrorSymbol			= (Widget) NULL;


/************************************************************************/
/* FUNCTION : CB_DialogConfirm                                          */
/* LONGNAME : Callback for Modal Confirmation Dialog                    */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-02-13                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
void	CB_DialogConfirm (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data )
{
  int			*response_ptr;
  XmAnyCallbackStruct	*cbstruct_ptr;

  response_ptr		= (int *)client_data;
  cbstruct_ptr		= (XmAnyCallbackStruct *)call_data;
  
  if (XmCR_OK == cbstruct_ptr->reason)
    *response_ptr	= RESPONSE_YES;
  else
    if (XmCR_CANCEL == cbstruct_ptr->reason)
      *response_ptr	= RESPONSE_NO;
}


/************************************************************************/
/* FUNCTION : create_shellDialogConfirm                                 */
/* LONGNAME : create Modal Confirmation Dialog                          */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-02-13                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : The default labels for Ok- and Cancel-button are used.    */
/*          : The Help-button is removed.                               */
/************************************************************************/
void	create_shellDialogConfirm (
	Widget	parent )
{
  Widget	children[6];		/* Children to manage */
  Arg		al[64];			/* Argument List */
  register int	ac = 0;			/* Argument Count */
  XmString	xmstring;		/* temporary storage for XmStrings */

  XtSetArg (al[ac], XmNallowShellResize, TRUE);			ac++;
  XtSetArg (al[ac], XmNtitle, " ");				ac++;
  shellDialogConfirm	= XmCreateDialogShell (parent, "shellDialogConfirm", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL);	ac++;
  XtSetArg (al[ac], XmNnoResize, TRUE);				ac++;
  XtSetArg (al[ac], XmNresizePolicy, XmRESIZE_NONE);		ac++;
  XtSetArg (al[ac], XmNallowOverlap, FALSE);			ac++;
  XtSetArg (al[ac], XmNautoUnmanage, FALSE);			ac++;
  XtSetArg (al[ac], XmNdialogType, XmDIALOG_QUESTION);		ac++;
  msgboxConfirm		= XmCreateMessageBox (shellDialogConfirm, "msgboxConfirm", al, ac);
  ac	= 0;

  butConfirmCancel	= XmMessageBoxGetChild (msgboxConfirm, XmDIALOG_CANCEL_BUTTON);
  butConfirmHelp	= XmMessageBoxGetChild (msgboxConfirm, XmDIALOG_HELP_BUTTON);
  labelConfirmText	= XmMessageBoxGetChild (msgboxConfirm, XmDIALOG_MESSAGE_LABEL);
  butConfirmOk		= XmMessageBoxGetChild (msgboxConfirm, XmDIALOG_OK_BUTTON);
  sepConfirm		= XmMessageBoxGetChild (msgboxConfirm, XmDIALOG_SEPARATOR);
  labelConfirmSymbol	= XmMessageBoxGetChild (msgboxConfirm, XmDIALOG_SYMBOL_LABEL);
  XtSetValues (labelConfirmText, al, ac);
  ac	= 0;

  XtAddCallback (msgboxConfirm, XmNokCallback, CB_DialogConfirm, (XtPointer)&response);
  XtAddCallback (msgboxConfirm, XmNcancelCallback, CB_DialogConfirm, (XtPointer)&response);
  XtUnmanageChild (butConfirmHelp);
}


/************************************************************************/
/* FUNCTION : create_shellDialogError                                   */
/* LONGNAME : create Modal Error Dialog                                 */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-02-13                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : The Cancel-button is used to close the dialog.            */
/*          : The Ok- and Help-button are removed.                      */
/************************************************************************/
void	create_shellDialogError (
	Widget	parent )
{
  Widget	children[6];		/* Children to manage */
  Arg		al[64];			/* Argument List */
  register int	ac = 0;			/* Argument Count */
  XmString	xmstring;		/* temporary storage for XmStrings */

  XtSetArg (al[ac], XmNallowShellResize, TRUE);			ac++;
  XtSetArg (al[ac], XmNtitle, " ");				ac++;
  shellDialogError	= XmCreateDialogShell (parent, "shellDialogError", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL);	ac++;
  XtSetArg (al[ac], XmNnoResize, TRUE);				ac++;
  XtSetArg (al[ac], XmNresizePolicy, XmRESIZE_NONE);		ac++;
  XtSetArg (al[ac], XmNallowOverlap, FALSE);			ac++;
  XtSetArg (al[ac], XmNautoUnmanage, FALSE);			ac++;
  XtSetArg (al[ac], XmNdialogType, XmDIALOG_ERROR);		ac++;
  msgboxError		= XmCreateMessageBox (shellDialogError, "msgboxError", al, ac);
  ac	= 0;

  butErrorCancel	= XmMessageBoxGetChild (msgboxError, XmDIALOG_CANCEL_BUTTON);
  butErrorHelp		= XmMessageBoxGetChild (msgboxError, XmDIALOG_HELP_BUTTON);
  labelErrorText	= XmMessageBoxGetChild (msgboxError, XmDIALOG_MESSAGE_LABEL);
  butErrorOk		= XmMessageBoxGetChild (msgboxError, XmDIALOG_OK_BUTTON);
  sepError		= XmMessageBoxGetChild (msgboxError, XmDIALOG_SEPARATOR);
  labelErrorSymbol	= XmMessageBoxGetChild (msgboxError, XmDIALOG_SYMBOL_LABEL);

  XtAddCallback (msgboxError, XmNcancelCallback, CB_Unmanage, (XtPointer)&msgboxError);
  XtUnmanageChild (butErrorOk);
  XtUnmanageChild (butErrorHelp);
}
