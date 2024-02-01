/************************************************************************/
/* MODULE   : Xm-cbstd.h                                                */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/*          : Standard callbacks                                        */
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

#ifndef XM_CBSTD_H
#define XM_CBSTD_H

void	CB_Manage (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data );

void	CB_Unmanage (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data );

void	CB_Popup (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data );

void	CB_Popdown (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data );

void	CB_Map (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data );

void	CB_Unmap (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data );

void	CB_Enable (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data );

void	CB_Disable (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data );

#endif /* XM_CBSTD_H */
