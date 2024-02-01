/************************************************************************/
/* MODULE   : Xm-dialog.h                                               */
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

#ifndef XM_DIALOG_H
#define XM_DIALOG_H


/* User response to Modal Confirmation Dialog */
#define	RESPONSE_NONE	0
#define	RESPONSE_YES	1
#define	RESPONSE_NO	2


extern Widget	shellDialogConfirm;
extern Widget	msgboxConfirm;
extern Widget	butConfirmCancel;
extern Widget	butConfirmHelp;
extern Widget	labelConfirmText;
extern Widget	butConfirmOk;
extern Widget	sepConfirm;
extern Widget	labelConfirmSymbol;

extern Widget	shellDialogError;
extern Widget	msgboxError;
extern Widget	butErrorCancel;
extern Widget	butErrorHelp;
extern Widget	labelErrorText;
extern Widget	butErrorOk;
extern Widget	sepError;
extern Widget	labelErrorSymbol;

extern int	response;


/*
void	CB_DialogConfirm (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data );
*/

void	create_shellDialogConfirm (
	Widget	parent );

void	create_shellDialogError (
	Widget	parent );

#endif /* XM_DIALOG_H */
