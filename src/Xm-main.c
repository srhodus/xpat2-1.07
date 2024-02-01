/************************************************************************/
/* MODULE   : Xm-main.c                                                 */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
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

#include "Xm-main.h"
#include "Xm-fbres.h"
#include "Xm-appwin.h"
#include "Xm-file.h"
#include "Xm-help.h"
#include "Xm-about.h"
#include "Xm-dialog.h"

#include "X-pat.h"
#include "version.h"


/************************************************************************/
/*      Global varables                                                 */
/************************************************************************/
XtAppContext	app_context;
Window		mainwindow;
Window		table;
char		*loadfilename;


/************************************************************************/
/* FUNCTION : main                                                      */
/* LONGNAME : X-Patience / Motif GUI / main routine                     */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-02-13                                                */
/* INPUT    : command options, see ...                                  */
/* OUTPUT   : exit code, see ...                                        */
/* NOTES    : -                                                         */
/************************************************************************/
int	main (
	int	argc, 
	char	**argv )
{
  XtSetLanguageProc ( (XtAppContext)NULL, (XtLanguageProc)NULL, (XtPointer)NULL);

  XtToolkitInitialize ();

  app_context	= XtCreateApplicationContext();

  XtAppSetFallbackResources (app_context, fallback_resources);

  dpy		= XtOpenDisplay (app_context, NULL, argv[0], "XPat", 
                           NULL, 0, &argc, argv);
  if (!dpy)
  {
    printf ("%s: can't open display, exiting...\n", argv[0]);
    exit (-1);
  }

  /* create GUI objects */
  create_shellMain (dpy, argv[0], argc, argv);
  create_shellDialogFile (shellMain);
#ifdef ONLINE_HELP
  create_shellDialogHelpText (shellMain);
#endif
  create_compound_string (shellMain);
  create_shellDialogHelpAbout (shellMain);
  create_shellDialogConfirm (shellMain);
  create_shellDialogError (shellMain);
  XtRealizeWidget (shellMain);

  /************************************************************************/
  /* The following sections are trimmed to be fully compatible with the   */
  /* alternative GUIs without modifications on the game itself.           */
  /* Several things might look different in a pure-Motif implementation.  */
  /************************************************************************/
  
  mainwindow	= XtWindow(shellMain);
  table		= XtWindow(Tableau);

  /* Several buttons are created insensitive by default. Currently  */
  /* the game deliveres no responses if it's time to unlock them.   */
  /* So they are all made sensitive now. This may be refined later. */
  {
    Arg			al[1];		/* Argument List */

    XtSetArg (al[0], XmNsensitive, TRUE);

    XtSetValues (butActionsUndo, al, 1);
    XtSetValues (butActionsRedo, al, 1);
    XtSetValues (butActionsReplay, al, 1);
    XtSetValues (butActionsRestart, al, 1);
    XtSetValues (butOptionsGotobookmark, al, 1);
    XtSetValues (butTbUndo, al, 1);
    XtSetValues (butTbRedo, al, 1);
    XtSetValues (butTbReplay, al, 1);
    XtSetValues (butTbRestart, al, 1);
  }

#if 0
  {
    XSetWindowAttributes winattr;
    long winmask;

    winattr.backing_store	= card.cardset ? WhenMapped : NotUseful;
    winattr.border_pixel	= blackpixel;
    winattr.bit_gravity	= NorthWestGravity;
    winattr.event_mask	= KeyPressMask |
				ExposureMask |
				ButtonPressMask |
				ButtonReleaseMask |
				StructureNotifyMask |
				Button3MotionMask;
    winmask		= CWBorderPixel |
				CWEventMask |
				CWBackingStore |
				CWBitGravity;
    XChangeWindowAttributes(dpy, table, winmask, &winattr);
  }
#endif

  graphics_control(Enable);

  init_layout();		/* position the piles in a nice way */
  {
    int		i;

    for (i = 0; i < game.numpiles; ++i)
      pile_resize(i);
  }

  show_message(TXT_WELCOME, VERSION);

  show_active_rules();

#if 0
/* xpat2 1.06 */
  if (!graphic.w_width)
  {
    graphic.w_width	= graphic.width;
    graphic.w_height	= graphic.height;
  }
#endif

  XtAppMainLoop (app_context);

  exit (0);
}
