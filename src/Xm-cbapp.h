/************************************************************************/
/* MODULE   : Xm-cbapp.h                                                */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/*          : Application specific callbacks                            */
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

#ifndef XM_CBAPP_H
#define XM_CBAPP_H

void	CB_GameNew (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_GameLoad (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_GameSave (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_GameExit (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_ToggleRules (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_ActionsUndo (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_ActionsRedo (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_ActionsReplay (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_ActionsRestart (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_ActionsDeal (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_ActionsMovetostack (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_OptionsToolbar (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_OptionsDropbookmark (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_OptionsGotobookmark (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_HelpText (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_HelpHint (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_HelpScore (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_FileNomatch (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);
	
void	CB_FileSetfilter (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data);

#endif /* XM_CBAPP_H */
