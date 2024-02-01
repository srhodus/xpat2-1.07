/************************************************************************/
/* MODULE   : Xm-about.c                                                */
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

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/Form.h>
#include <Xm/Label.h>
#include <Xm/MessageB.h>
#include <Xm/PushB.h>

#include <xpm.h>

#include "Xm-pixmap.h"
#include "Xm-cbstd.h"
#include "Xm-appwin.h"


/************************************************************************/
/*      Widget hierarchy                                                */
/************************************************************************/

/* Dialogbox "Help About" */
/*           */
/*---------- */	Widget shellDialogHelpAbout		= (Widget) NULL;
/*  |        */
/*  |------- */	Widget msgboxHelpAbout			= (Widget) NULL;
/*    |      */
/*    |----- */	Widget sepHelpAbout			= (Widget) NULL;
/*    |----- */	Widget formHelpAbout			= (Widget) NULL;
/*    | |--- */	Widget labelHelpAboutSymbol		= (Widget) NULL;
/*    | |--- */	Widget labelHelpAboutSymbolB		= (Widget) NULL;
/*    | |--- */	Widget labelHelpAboutText		= (Widget) NULL;
/*    | |--- */	Widget labelHelpAboutVersion		= (Widget) NULL;
/*    | |--- */	Widget labelHelpAboutAuthors		= (Widget) NULL;
/*    |      */
/*    |----- */	Widget butHelpAboutVersion		= (Widget) NULL;
/*    |----- */	Widget butHelpAboutAuthors		= (Widget) NULL;
/*    |----- */	Widget butHelpAboutClose		= (Widget) NULL;


/************************************************************************/
/*      Font resources                                                  */
/************************************************************************/

static XmString	concat_xmstring (
	XmString	s1,
	XmString	s2 )
{
  XmString	s3 = XmStringConcat (s1, s2);

  XmStringFree (s1);
  XmStringFree (s2);
  return (s3);
}


typedef struct	FontResources_s
{ 
  XmFontList AboutText;
} FontResources_t, *FontResources_p;

static FontResources_t font_resources;


typedef struct	XmStringResources_s
{ 
  XmString stringAboutText;
} XmStringResources_t, *XmStringResources_p;

static XmStringResources_t	xmstring_resources;


/************************************************************************/
/* FUNCTION : create_compound_string                                    */
/* LONGNAME : create compound string for "Help About" dialog            */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-02-13                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
void	create_compound_string (
	Widget	toplevel )
{
  XrmValue	from_value, to_value;	/* For resource conversions */
  XmString	xmstring;		/* For building XmString objects */

  /* create compound string for "Help About" dialog */
  from_value.addr	=
	"-adobe-new century schoolbook-bold-i-normal--18-180-75-75-p-111-iso8859-1=BoldItalic, "
	"-b&h-lucida sans-medium-r-normal-sans-14-140-72-72-p-82-iso8859-1=Regular";
  from_value.size	= strlen (from_value.addr)+1;
  to_value.addr	= NULL;
  XtConvertAndStore (toplevel, XmRString, &from_value, XmRFontList, &to_value);
  if (to_value.addr)
    font_resources.AboutText	= * (XmFontList*)to_value.addr;

  xmstring	= XmStringCreate ("X-Patience", "BoldItalic");
  xmstring	= concat_xmstring (xmstring, XmStringSeparatorCreate ());
  xmstring	= concat_xmstring (xmstring, XmStringCreate ("Solitaire Card Game", "Regular"));
  xmstring	= concat_xmstring (xmstring, XmStringSeparatorCreate ());
  xmstring	= concat_xmstring (xmstring, XmStringCreate ("Suite for Unix/X11", "Regular"));
  xmstring_resources.stringAboutText	= xmstring;
}


/************************************************************************/
/* FUNCTION : create_shellDialogHelpAbout                               */
/* LONGNAME : create Help-About Dialog                                  */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-02-13                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
void	create_shellDialogHelpAbout (
	Widget	parent )
{
  Widget	children[5];		/* Children to manage */
  Arg		al[64];			/* Argument List */
  register int	ac = 0;			/* Argument Count */
  XrmValue	from_value, to_value;	/* For resource conversion */
  Pixel		bg;			/* colour values for pixmaps */ 
  XmString	xmstring;		/* temporary storage for XmStrings */

  XtSetArg (al[ac], XmNallowShellResize, TRUE);			ac++;
  XtSetArg (al[ac], XmNtitle, "About X-Patience");		ac++;
  shellDialogHelpAbout	= XmCreateDialogShell (parent, "shellDialogHelpAbout", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNautoUnmanage, FALSE);			ac++;
  XtSetArg (al[ac], XmNdialogType, XmDIALOG_TEMPLATE);		ac++;
  msgboxHelpAbout	= XmCreateMessageBox (shellDialogHelpAbout, "msgboxHelpAbout", al, ac);
  ac	= 0;

  sepHelpAbout	= XmMessageBoxGetChild (msgboxHelpAbout, XmDIALOG_SEPARATOR);

  formHelpAbout	= XmCreateForm (msgboxHelpAbout, "formHelpAbout", al, ac);

  XtSetArg (al[ac], XmNbackground, &bg);			ac++;
  XtGetValues (formHelpAbout, al, ac);
  ac	= 0;

  /* initialize button pixmaps */
  init_helpabout_pixmaps (shellMain, bg);


  XtSetArg (al[ac], XmNlabelType, XmPIXMAP);			ac++;
  labelHelpAboutSymbol	= XmCreateLabel (formHelpAbout, "labelHelpAboutSymbol", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelPixmap, pixmap_resources.pixmapAboutA);	ac++;
  XtSetValues (labelHelpAboutSymbol, al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNmappedWhenManaged, FALSE);		ac++;
  XtSetArg (al[ac], XmNlabelType, XmPIXMAP);			ac++;
  labelHelpAboutSymbolB	= XmCreateLabel (formHelpAbout, "labelHelpAboutSymbolB", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelPixmap, pixmap_resources.pixmapAboutB);	ac++;
  XtSetValues (labelHelpAboutSymbolB, al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNlabelString, xmstring_resources.stringAboutText);	ac++;
  XtSetArg (al[ac], XmNfontList, font_resources.AboutText);	ac++;
  labelHelpAboutText	= XmCreateLabel (formHelpAbout, "labelHelpAboutText", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNmappedWhenManaged, FALSE);		ac++;
  labelHelpAboutVersion	= XmCreateLabel (formHelpAbout, "labelHelpAboutVersion", al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNmappedWhenManaged, FALSE);		ac++;
  labelHelpAboutAuthors	= XmCreateLabel (formHelpAbout, "labelHelpAboutAuthors", al, ac);
  ac	= 0;

  butHelpAboutVersion	= XmCreatePushButton (msgboxHelpAbout, "butHelpAboutVersion", al, ac);
  ac	= 0;

  butHelpAboutAuthors	= XmCreatePushButton (msgboxHelpAbout, "butHelpAboutAuthors", al, ac);
  ac	= 0;

  butHelpAboutClose	= XmCreatePushButton (msgboxHelpAbout, "butHelpAboutClose", al, ac);
  ac	= 0;


  XtSetArg (al[ac], XmNtopAttachment, XmATTACH_FORM);		ac++;
  XtSetArg (al[ac], XmNtopOffset, 25);				ac++;
  XtSetArg (al[ac], XmNbottomAttachment, XmATTACH_FORM);	ac++;
  XtSetArg (al[ac], XmNbottomOffset, 25);			ac++;
  XtSetArg (al[ac], XmNleftAttachment, XmATTACH_FORM);		ac++;
  XtSetArg (al[ac], XmNleftOffset, 25);				ac++;
  XtSetArg (al[ac], XmNrightAttachment, XmATTACH_NONE);		ac++;
  XtSetValues (labelHelpAboutSymbol, al, ac);
  ac	= 0;


  XtSetArg (al[ac], XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET);	ac++;
  XtSetArg (al[ac], XmNtopOffset, 0);				ac++;
  XtSetArg (al[ac], XmNtopWidget, labelHelpAboutSymbol);	ac++;
  XtSetArg (al[ac], XmNbottomAttachment, XmATTACH_NONE);	ac++;
  XtSetArg (al[ac], XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET);	ac++;
  XtSetArg (al[ac], XmNleftOffset, 0);				ac++;
  XtSetArg (al[ac], XmNleftWidget, labelHelpAboutSymbol);	ac++;
  XtSetArg (al[ac], XmNrightAttachment, XmATTACH_NONE);		ac++;
  XtSetValues (labelHelpAboutSymbolB, al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET);	ac++;
  XtSetArg (al[ac], XmNtopOffset, 0);				ac++;
  XtSetArg (al[ac], XmNtopWidget, labelHelpAboutSymbol);	ac++;
  XtSetArg (al[ac], XmNbottomAttachment, XmATTACH_NONE);	ac++;
  XtSetArg (al[ac], XmNleftAttachment, XmATTACH_WIDGET);	ac++;
  XtSetArg (al[ac], XmNleftOffset, 25);				ac++;
  XtSetArg (al[ac], XmNleftWidget, labelHelpAboutSymbol);	ac++;
  XtSetArg (al[ac], XmNrightAttachment, XmATTACH_FORM);		ac++;
  XtSetArg (al[ac], XmNrightOffset, 25);			ac++;
  XtSetValues (labelHelpAboutText, al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET);	ac++;
  XtSetArg (al[ac], XmNtopOffset, -5);				ac++;
  XtSetArg (al[ac], XmNtopWidget, labelHelpAboutSymbol);	ac++;
  XtSetArg (al[ac], XmNbottomAttachment, XmATTACH_NONE);	ac++;
  XtSetArg (al[ac], XmNleftAttachment, XmATTACH_WIDGET);	ac++;
  XtSetArg (al[ac], XmNleftOffset, 25);				ac++;
  XtSetArg (al[ac], XmNleftWidget, labelHelpAboutSymbol);	ac++;
  XtSetArg (al[ac], XmNrightAttachment, XmATTACH_NONE);		ac++;
  XtSetValues (labelHelpAboutVersion, al, ac);
  ac	= 0;

  XtSetArg (al[ac], XmNtopAttachment, XmATTACH_FORM);		ac++;
  XtSetArg (al[ac], XmNtopOffset, 10);				ac++;
  XtSetArg (al[ac], XmNbottomAttachment, XmATTACH_NONE);	ac++;
  XtSetArg (al[ac], XmNleftAttachment, XmATTACH_FORM);		ac++;
  XtSetArg (al[ac], XmNleftOffset, 15);				ac++;
  XtSetArg (al[ac], XmNrightAttachment, XmATTACH_NONE);		ac++;
  XtSetValues (labelHelpAboutAuthors, al, ac);
  ac	= 0;

  children[ac++]	= labelHelpAboutSymbol;
  children[ac++]	= labelHelpAboutSymbolB;
  children[ac++]	= labelHelpAboutText;
  children[ac++]	= labelHelpAboutVersion;
  children[ac++]	= labelHelpAboutAuthors;
  XtManageChildren (children, ac);
  ac	= 0;

  /* callbacks for button "Version" */
  XtAddCallback (butHelpAboutVersion, XmNactivateCallback, CB_Unmap, (XtPointer)&labelHelpAboutSymbol);
  XtAddCallback (butHelpAboutVersion, XmNactivateCallback, CB_Unmap, (XtPointer)&labelHelpAboutText);
  XtAddCallback (butHelpAboutVersion, XmNactivateCallback, CB_Unmap, (XtPointer)&labelHelpAboutAuthors);
  XtAddCallback (butHelpAboutVersion, XmNactivateCallback, CB_Map, (XtPointer)&labelHelpAboutSymbolB);
  XtAddCallback (butHelpAboutVersion, XmNactivateCallback, CB_Map, (XtPointer)&labelHelpAboutVersion);

  /* callbacks for button "Authors" */
  XtAddCallback (butHelpAboutAuthors, XmNactivateCallback, CB_Unmap, (XtPointer)&labelHelpAboutSymbol);
  XtAddCallback (butHelpAboutAuthors, XmNactivateCallback, CB_Unmap, (XtPointer)&labelHelpAboutSymbolB);
  XtAddCallback (butHelpAboutAuthors, XmNactivateCallback, CB_Unmap, (XtPointer)&labelHelpAboutText);
  XtAddCallback (butHelpAboutAuthors, XmNactivateCallback, CB_Unmap, (XtPointer)&labelHelpAboutVersion);
  XtAddCallback (butHelpAboutAuthors, XmNactivateCallback, CB_Map, (XtPointer)&labelHelpAboutAuthors);

  /* callbacks for button "Close" */
  /* Restore initial state before closing the dialog */
  XtAddCallback (butHelpAboutClose, XmNactivateCallback, CB_Unmap, (XtPointer)&labelHelpAboutSymbolB);
  XtAddCallback (butHelpAboutClose, XmNactivateCallback, CB_Unmap, (XtPointer)&labelHelpAboutVersion);
  XtAddCallback (butHelpAboutClose, XmNactivateCallback, CB_Unmap, (XtPointer)&labelHelpAboutAuthors);
  XtAddCallback (butHelpAboutClose, XmNactivateCallback, CB_Map, (XtPointer)&labelHelpAboutSymbol);
  XtAddCallback (butHelpAboutClose, XmNactivateCallback, CB_Map, (XtPointer)&labelHelpAboutText);
  XtAddCallback (butHelpAboutClose, XmNactivateCallback, CB_Unmanage, (XtPointer)&msgboxHelpAbout);

  children[ac++]	= formHelpAbout;
  children[ac++]	= butHelpAboutVersion;
  children[ac++]	= butHelpAboutAuthors;
  children[ac++]	= butHelpAboutClose;
  XtManageChildren (children, ac);
  ac	= 0;
}
