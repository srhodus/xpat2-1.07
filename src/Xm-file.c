/************************************************************************/
/* MODULE   : Xm-file.c                                                 */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/*          : File selection dialog                                     */
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
#include <Xm/FileSB.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/SelectioB.h>

#include "Xm-main.h"
#include "Xm-cbstd.h"
#include "Xm-cbapp.h"

#include "X-pat.h"


/************************************************************************/
/*      Widget hierarchy                                                */
/************************************************************************/

/*------------------ */	Widget shellDialogFile		= (Widget) NULL;
/*  |                */
/*  |--------------- */	Widget fileselDialogFile	= (Widget) NULL;
/*    |              */
/*    |------------- */	Widget butFileApply		= (Widget) NULL;
/*    |------------- */	Widget butFileCancel		= (Widget) NULL;
/*    |------------- */	Widget butFileHelp		= (Widget) NULL;
/*    |------------- */	Widget scrlistFileFiles		= (Widget) NULL;
/*    | |----------- */	Widget sbhorFileFiles		= (Widget) NULL;
/*    | |----------- */	Widget sbverFileFiles		= (Widget) NULL;
/*    | |----------- */	Widget listFileFiles		= (Widget) NULL;
/*    |              */
/*    |------------- */	Widget labelFileFiles		= (Widget) NULL;
/*    |------------- */	Widget butFileOk		= (Widget) NULL;
/*    |------------- */	Widget labelFileSelection	= (Widget) NULL;
/*    |------------- */	Widget sepFile			= (Widget) NULL;
/*    |------------- */	Widget textFileSelection	= (Widget) NULL;
/*    |------------- */	Widget labelFileFilter		= (Widget) NULL;
/*    |------------- */	Widget textFileFilter		= (Widget) NULL;
/*    |------------- */	Widget labelFileDirs		= (Widget) NULL;
/*    |------------- */	Widget scrlistFileDirs		= (Widget) NULL;
/*    | |----------- */	Widget sbhorFileDirs		= (Widget) NULL;
/*    | |----------- */	Widget sbverFileDirs		= (Widget) NULL;
/*    | |----------- */	Widget listFileDirs		= (Widget) NULL;
/*    |              */
/*    |------------- */	Widget optmenuFileSetfilter	= (Widget) NULL;
/*      |----------- */	Widget labelFileSetfilter	= (Widget) NULL;
/*      |----------- */	Widget cascadeFileSetfilter	= (Widget) NULL;
/*        |--------- */ Widget menuFileSetfilter	= (Widget) NULL;
/*          |------- */ Widget butFileSetfilterAll	= (Widget) NULL;
/*          |-------    Widget butFileSetfilter[1] */
/*          |-------    Widget butFileSetfilter[2] */
/*          |-------    Widget        .....        */
/*          |-------    Widget butFileSetfilter[n] */
/*                   */ Widget butFileSetfilter[MAXRULES];


/************************************************************************/
/*      Local functions                                                 */
/************************************************************************/

void	list_games (
	Widget		fileselbox,
	XtPointer	*search_data );


/************************************************************************/
/* FUNCTION : create_shellDialogFile                                    */
/* LONGNAME : create File Selection Dialog                              */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-02-28                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
void	create_shellDialogFile (
	Widget	parent )
{
  Widget	children[14];		/* Children to manage */
  Arg		al[64];			/* Argument List */
  register int	ac = 0;			/* Argument Count */
  XmString	xmstring;		/* temporary storage for XmStrings */

  XtSetArg(al[ac], XmNallowShellResize, TRUE);			ac++;
  shellDialogFile	= XmCreateDialogShell (parent, "shellDialogFile", al, ac);
  ac	= 0;

  XtSetArg(al[ac], XmNdialogStyle, XmDIALOG_PRIMARY_APPLICATION_MODAL);	ac++;
  XtSetArg(al[ac], XmNmustMatch, TRUE);				ac++;
#if 0
  XtSetArg(al[ac], XmNfileSearchProc, list_games);		ac++;
#endif
  fileselDialogFile	= XmCreateFileSelectionBox (shellDialogFile, "fileselDialogFile", al, ac);
  ac	= 0;

  butFileApply		= XmSelectionBoxGetChild (fileselDialogFile, XmDIALOG_APPLY_BUTTON);
  butFileCancel		= XmSelectionBoxGetChild (fileselDialogFile, XmDIALOG_CANCEL_BUTTON);
  butFileHelp		= XmSelectionBoxGetChild (fileselDialogFile, XmDIALOG_HELP_BUTTON);
  listFileFiles		= XmSelectionBoxGetChild (fileselDialogFile, XmDIALOG_LIST);
  labelFileFiles	= XmSelectionBoxGetChild (fileselDialogFile, XmDIALOG_LIST_LABEL);
  butFileOk		= XmSelectionBoxGetChild (fileselDialogFile, XmDIALOG_OK_BUTTON);
  labelFileSelection	= XmSelectionBoxGetChild (fileselDialogFile, XmDIALOG_SELECTION_LABEL);
  sepFile		= XmSelectionBoxGetChild (fileselDialogFile, XmDIALOG_SEPARATOR);
  textFileSelection	= XmSelectionBoxGetChild (fileselDialogFile, XmDIALOG_TEXT);
  labelFileFilter	= XmFileSelectionBoxGetChild (fileselDialogFile, XmDIALOG_FILTER_LABEL);
  textFileFilter	= XmFileSelectionBoxGetChild (fileselDialogFile, XmDIALOG_FILTER_TEXT);
  labelFileDirs		= XmFileSelectionBoxGetChild (fileselDialogFile, XmDIALOG_DIR_LIST_LABEL);
  listFileDirs		= XmFileSelectionBoxGetChild (fileselDialogFile, XmDIALOG_DIR_LIST);
  scrlistFileFiles	= XtParent (listFileFiles);

  XtSetArg(al[ac], XmNhorizontalScrollBar, &sbhorFileFiles);	ac++;
  XtSetArg(al[ac], XmNverticalScrollBar, &sbverFileFiles);	ac++;
  XtGetValues(scrlistFileFiles, al, ac);
  ac	= 0;

  scrlistFileDirs	= XtParent (listFileDirs);

  XtSetArg(al[ac], XmNhorizontalScrollBar, &sbhorFileDirs);	ac++;
  XtSetArg(al[ac], XmNverticalScrollBar, &sbverFileDirs);	ac++;
  XtGetValues(scrlistFileDirs, al, ac);
  ac	= 0;

  XtSetArg(al[ac], XmNorientation, XmHORIZONTAL);		ac++;
  optmenuFileSetfilter	= XmCreateOptionMenu (fileselDialogFile, "optmenuFileSetfilter", al, ac);
  ac	= 0;

  labelFileSetfilter	= XmOptionLabelGadget (optmenuFileSetfilter);
  cascadeFileSetfilter	= XmOptionButtonGadget (optmenuFileSetfilter);
  menuFileSetfilter	= XmCreatePulldownMenu (optmenuFileSetfilter, "menuFileSetfilter", al, ac);


  /**********************************************************************/
  /*    create rule-dependant widgets                                   */
  /**********************************************************************/
  {
    struct rules	**rp;
    char	widgetname[32];

    /* create default button "All Games" */
    butFileSetfilterAll	= XmCreatePushButton (menuFileSetfilter, "butFileSetfilterAll", al, ac);
    ac	= 0;

    XtAddCallback (butFileSetfilterAll, XmNactivateCallback, CB_FileSetfilter, (XtPointer)FALSE);
    XtManageChild (butFileSetfilterAll);

    /* create rule-dependant buttons */
    for (rp = rulepool; *rp; rp++)
    {
      int	index = rp-rulepool;

      if (MAXRULES <= index)
        break;	/* max. number of rules reached */

      xmstring	= XmStringCreateLtoR ((char *)((*rp)->shortname),
			(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
      XtSetArg (al[ac], XmNlabelString, xmstring);		ac++;
      sprintf(widgetname, "butFileSetfilter%d", index+1);
      butFileSetfilter[index]	= XmCreatePushButton (menuFileSetfilter, widgetname, al, ac);
      ac	= 0;
      XmStringFree (xmstring);

      XtAddCallback (butFileSetfilter[index], XmNactivateCallback,
			CB_FileSetfilter, (XtPointer)((*rp)->shortname));
      XtManageChild (butFileSetfilter[index]);
    }
  }
 
  XtAddCallback (fileselDialogFile, XmNokCallback, CB_GameLoad, (XtPointer)0);
  XtAddCallback (fileselDialogFile, XmNnoMatchCallback, CB_FileNomatch, (XtPointer)0);
  XtAddCallback (butFileCancel, XmNactivateCallback, CB_Unmanage, (XtPointer) &fileselDialogFile);

  XtSetArg(al[ac], XmNsubMenuId, menuFileSetfilter);		ac++;
  XtSetValues (cascadeFileSetfilter, al, ac);
  ac	= 0;

  children[ac++]	= optmenuFileSetfilter;
  XtManageChildren(children, ac);
  ac	= 0;
  XtUnmanageChild (butFileHelp);
}


/************************************************************************/
/* FUNCTION : list_games                                                */
/* LONGNAME : list saved games as selected by toggle button             */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-05-13                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
void	list_games (
	Widget		fileselbox,
	XtPointer	*search_data )
{
  char		*value;
  char		*mask;
  char		*dir;
  char		*pattern;

  XmFileSelectionBoxCallbackStruct *call_data	=
		(XmFileSelectionBoxCallbackStruct *)search_data;

  XmStringGetLtoR(call_data->value, XmFONTLIST_DEFAULT_TAG, &value);
  XmStringGetLtoR(call_data->mask, XmFONTLIST_DEFAULT_TAG, &mask);
  XmStringGetLtoR(call_data->dir, XmFONTLIST_DEFAULT_TAG, &dir);
  XmStringGetLtoR(call_data->pattern, XmFONTLIST_DEFAULT_TAG, &pattern);

  
}
