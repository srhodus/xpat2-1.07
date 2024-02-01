/************************************************************************/
/* MODULE   : Xm-cbstd.c                                                */
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


#include <X11/Intrinsic.h>


/************************************************************************/
/*      Standard callbacks                                              */
/************************************************************************/
void	CB_Manage (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data )
{
  if (client_data && * (Widget *)client_data)
    XtManageChild (* (Widget *)client_data);
}

void	CB_Unmanage (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data )
{
  if (client_data && * (Widget *)client_data)
    XtUnmanageChild (* (Widget *)client_data);
}

void	CB_Popup (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data )
{
  if (client_data && * (Widget *)client_data)
    XtPopup (* (Widget *)client_data, XtGrabNone);
}

void	CB_Popdown (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data )
{
  if (client_data && * (Widget *)client_data)
    XtPopdown (* (Widget *)client_data);
}

void	CB_Map (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data )
{
  if (client_data && * (Widget *)client_data)
    XtMapWidget (* (Widget *)client_data);
}

void	CB_Unmap (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data )
{
  if (client_data && * (Widget *)client_data)
    XtUnmapWidget (* (Widget *)client_data);
}

void	CB_Enable (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data )
{
  if (client_data && * (Widget *)client_data)
    XtSetSensitive (* (Widget *)client_data, TRUE);
}

void	CB_Disable (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	call_data )
{
  if (client_data && * (Widget *)client_data)
    XtSetSensitive (* (Widget *)client_data, FALSE);
}
