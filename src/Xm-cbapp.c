/************************************************************************/
/* MODULE   : Xm-cbapp.c                                                */
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
/* 1.00  |19990213| Initial creation for xpat2-1.04              | ac   */
/*-------+--------+----------------------------------------------+------*/
/* 1.01  |19991106| adapted to xpat2-1.06                        | ac   */
/************************************************************************/

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#include <sys/stat.h>

#include "Xm-main.h"
#include "Xm-appwin.h"
#include "Xm-file.h"
#include "Xm-help.h"
#include "Xm-dialog.h"

#include "X-pat.h"
#include "Tableau.h"

/************************************************************************/
/*      Specific callbacks                                              */
/************************************************************************/
void	CB_GameNew (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;

  rq_AnotherGame ();
}

void	CB_GameLoad (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmFileSelectionBoxCallbackStruct *call_data	=
			(XmFileSelectionBoxCallbackStruct *)xt_call_data;

  XmStringGetLtoR (call_data->value, (XmStringCharSet)XmFONTLIST_DEFAULT_TAG, &loadfilename);
  load_game(loadfilename);
  init_layout();		/* re-position the piles */
  show_active_rules();
  XtFree(loadfilename);

  XtUnmanageChild (fileselDialogFile);
}

void	CB_GameSave (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;

  cmd_SaveGame ();
}

void	CB_GameExit (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;

  rq_LeavePat ();
}


void	CB_ToggleRules (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmToggleButtonCallbackStruct *call_data	=
			(XmToggleButtonCallbackStruct *)xt_call_data;

  change_rules((char *)client_data);
}


void	CB_ActionsUndo (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;

  cmd_UndoMove ();
}

void	CB_ActionsRedo (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;

  cmd_RedoMove ();
}

void	CB_ActionsReplay (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;

  cmd_ReplayGame ();
}

void	CB_ActionsRestart (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;

  cmd_RestartGame ();
}

void	CB_ActionsDeal (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;

  cmd_DealCards ();
}

void	CB_ActionsMovetostack (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;

  cmd_ToStack ();
}


void	CB_OptionsToolbar (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  Arg		al[4];			/* Argument List */
  register int	ac = 0;			/* Argument Count */
  XmToggleButtonCallbackStruct *call_data	=
			(XmToggleButtonCallbackStruct *)xt_call_data;

  if (call_data->set)
  { /* toggle is set, show toolbar */
#ifdef FLAT_BUTTONS
    XtMapWidget (frameToolbar);
#else
    XtMapWidget (rowcolToolbar);
#endif

    XtSetArg (al[ac], XmNtopAttachment, XmATTACH_WIDGET);	ac++;
#ifdef FLAT_BUTTONS
    XtSetArg (al[ac], XmNtopWidget, frameToolbar);		ac++;
#else
    XtSetArg (al[ac], XmNtopWidget, rowcolToolbar);		ac++;
#endif
    XtSetValues (Tableau, al, ac);
    ac	= 0;
  }
  else
  { /* toggle is not set, hide toolbar */
#ifdef FLAT_BUTTONS
    XtUnmapWidget (frameToolbar);
#else
    XtUnmapWidget (rowcolToolbar);
#endif

    XtSetArg (al[ac], XmNtopAttachment, XmATTACH_WIDGET);	ac++;
    XtSetArg (al[ac], XmNtopWidget, menubar);			ac++;
    XtSetValues (Tableau, al, ac);
    ac	= 0;
  }
}

void	CB_OptionsDropbookmark (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;

  cmd_DropBookmark ();
}

void	CB_OptionsGotobookmark (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;

  cmd_GotoBookmark ();
}


#ifdef ONLINE_HELP
void	CB_HelpText (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;
  const char	*langdir	= get_lang();	/* xpat2 1.06 */
  char		*helptext;

  /* set error-message as the default text */
  helptext	= (char *)TXT_LOAD_ERR_OPEN;

  do
  {
    char	filename[1024];
    struct stat	statbuf;
    FILE	*fp;
  
    if (!client_data)
      break;			/* Error: no filename */

    if (!(*((char *)client_data)))
      break;			/* Error: empty filename */

    /* create path to helpfile */
    if (((char *)client_data)[0] != '/')
      sprintf(filename, "%s/%s/%s", LIBDIR, langdir, ((char *)client_data));
    else
      strcpy(filename, ((char *)client_data));

    /* check if file is a regular textfile */
    if (-1 == stat(filename, &statbuf))
      break;			/* Error: failed to get file status */

    if (S_IFREG != statbuf.st_mode & S_IFMT)
      break;			/* Error: file is not a regular file */

    if (NULL == (fp = fopen(filename, "r")))
      break;			/* Error: failed to open file */

    
    if (NULL == (helptext = XtMalloc ((unsigned int)(statbuf.st_size + 1))))
    { /* Error: memory allocation failed */
      fclose (fp);
      break;
    }
    
    if (!(fread (helptext, sizeof (char), statbuf.st_size, fp)))
    { /* Error: failed to read file */
      fclose (fp);
      break;
    }

    helptext[statbuf.st_size] = 0;
    fclose (fp);

  } while (0);

  XmTextSetString (textHelpText, helptext);

  XtManageChild (msgboxHelpText);

  XtFree (helptext);
}
#endif

void	CB_HelpHint (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;

  cmd_NextHint ();
}

void	CB_HelpScore (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;

  cmd_ShowScore ();
}


void	CB_FileNomatch (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  XmFileSelectionBoxCallbackStruct *call_data	=
			(XmFileSelectionBoxCallbackStruct *)xt_call_data ;

  XtManageChild (msgboxError);
}


void	CB_FileSetfilter (
	Widget		widget,
	XtPointer	client_data,
	XtPointer	xt_call_data)
{
  Arg		al[4];			/* Argument List */
  register int	ac = 0;			/* Argument Count */
  XmString	xmstring;		/* temporary storage for XmStrings */

  XmPushButtonCallbackStruct *call_data	=
			(XmPushButtonCallbackStruct *)xt_call_data;

  if (client_data && (*((char *)client_data)))
  {
    xmstring	= XmStringCreateLtoR ((char *)client_data,
			(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
    XtSetArg (al[ac], XmNpattern, xmstring);		ac++;
    XtSetValues (fileselDialogFile, al, ac);
    ac	= 0;
    XmStringFree (xmstring);
  }
}
