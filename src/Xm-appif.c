/************************************************************************/
/* MODULE   : Xm-appif.c                                                */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/* AUTHOR   : Christian Anzenberger                                     */
/*          : Several methods exported by the GUI                       */
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
#include <stdio.h>
#include <stdarg.h>

#include "Xm-main.h"
#include "Xm-appwin.h"
#include "Xm-dialog.h"

#include "X-pat.h"


/************************************************************************/
/* FUNCTION : show_active_rules                                         */
/* LONGNAME : set rule-dependant widgets to active rules                */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-03-05                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
void	show_active_rules ( void )
{
  Arg		al[1];			/* Argument List */
  XmString	xmstring;		/* temporary storage for XmStrings */
  char		*label;
  struct rules	**rp;

  /* show active rules in mainwindow titlebar */
  XtSetArg (al[0], XmNtitle,
		(char *)(rules.longname ? rules.longname : rules.shortname));
  XtSetValues (shellMain, al, 1);

  /* activate toggle button matching active rules */
  for (rp = rulepool; *rp; rp++)
  {
    int	index = rp-rulepool;

    if (MAXRULES <= index)
      break;	/* max. number of rules reached */

    /* get button label */
    XtSetArg (al[0], XmNlabelString, &xmstring);
    XtGetValues (toggleRules[index], al, 1);
    XmStringGetLtoR (xmstring, (XmStringCharSet)XmFONTLIST_DEFAULT_TAG, &label);
    XmStringFree (xmstring);

    /* activate matching button, inactiate others */
    XtSetArg (al[0], XmNset, !(strcmp(rules.shortname, label)));
    XtSetValues (toggleRules[index], al, 1);
    XtFree (label);
  }
}


/************************************************************************/
/* FUNCTION : show_message                                              */
/* LONGNAME : show message string in footer line                        */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-02-13                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
void	show_message (
	const char	*string, 
	... )
{
  Arg		al[1];			/* argument list */
  va_list	strargs;		/* string arguments */
  static char	message[256];
  XmString	xmstring;		/* temporary storage for XmStrings */

  va_start(strargs, string);
  if (!string)
  {
    memset(message, ' ', sizeof(message)-1);
    message[sizeof(message)-1] = '\0';
  }
  else
    vsprintf(message, string, strargs);
  va_end(strargs);

  xmstring	= XmStringCreateLtoR (message,
			(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
  XtSetArg (al[0], XmNlabelString, xmstring);
  XtSetValues (labelFooter, al, 1);
  XmStringFree (xmstring);
}


#ifdef SOUND
/************************************************************************/
/* FUNCTION : checksound                                                */
/* LONGNAME : check current state of sound toggle                       */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-02-13                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
int	checksound ( void )
{
  return XmToggleButtonGetState (toggleOptionsSound);
}
#endif


/************************************************************************/
/* FUNCTION : Force_Resize                                              */
/* LONGNAME : force resize of the main window                           */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-02-13                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
void	Force_Resize (
	XSize_t		width, 
	XSize_t		height )
{
  Arg		al[2];			/* argument list */
  register int	ac = 0;			/* argument count */

  XtSetArg (al[ac], XmNheight, height);				ac++;
  XtSetArg (al[ac], XmNwidth, width);				ac++;
  XtSetValues (Tableau, al, ac);
  
  printf("Resized to %d x &d\n", width, height);
}


/************************************************************************/
/* FUNCTION : request_confirm                                           */
/* LONGNAME : request confirmation and execute function if requested    */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-02-13                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : trimmed for compatiblility with the Athena interface      */
/************************************************************************/
void	request_confirm (
	void		(*dofunc)(void),
	const char	prompt[] )
{
  Widget	children[6];		/* Children to manage */
  Arg		al[6];			/* Argument List */
  register int	ac = 0;			/* Argument Count */
  XmString	xmstring;		/* temporary storage for XmStrings */

  xmstring		= XmStringCreateLtoR ((char *)prompt, (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
  XtSetArg (al[ac], XmNlabelString, xmstring);			ac++;
  XtSetValues (labelConfirmText, al, ac);
  ac	= 0;
  XmStringFree (xmstring);

  response		= RESPONSE_NONE;
  XtManageChild (msgboxConfirm);
  XtPopup (XtParent(msgboxConfirm), XtGrabNone);
  
  while (RESPONSE_NONE == response)
    XtAppProcessEvent (app_context, XtIMAll);
  XtPopdown (XtParent(msgboxConfirm));
  XSync (dpy, 0);
  XmUpdateDisplay (shellMain);
  
  if (RESPONSE_YES == response)
    (*dofunc)();	/* execute the desired function */
}

void	cmd_LeavePat ( void )
{
  play_sound("goodbye");
  XtDestroyApplicationContext(app_context);
  exit(0);
}

void	cmd_Cancel ( void )
{
  /* dummy function */
}

void	cmd_Confirm ( void )
{
  /* dummy function */
}
