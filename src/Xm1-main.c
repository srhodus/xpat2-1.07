/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module Xm1-main.c			     */
/*									     */
/*	main function for the Motif Widget interface			     */
/*	written by Heiko Eissfeldt and Michael Bischoff			     */
/*	March-1994							     */
/*	Modified by Karsten Jensen					     */
/*	October-2000							     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#ifdef useXm

#include "X-pat.h"
#include "Tableau.h"
#include "Xm1-help.h"
#include "version.h"

#include <Xm/CascadeB.h>
#include <Xm/CascadeBG.h>
#include <Xm/PushBG.h>
#include <Xm/ToggleB.h>
#include <Xm/MainW.h>
#include <Xm/Form.h>
#include <Xm/RowColumn.h>
#include <Xm/Separator.h>
#include <Xm/Frame.h>
#include <Xm/MessageB.h>
#include <X11/Xmu/Editres.h>


Window table, mainwindow;

Widget toplevel;
static Widget MessageBox, Desktop;

static void
perform_command(Widget widget, XtPointer client_data, XtPointer call_data)
{
    (*(void (*)(void))client_data)();	/* any questions? */
}

void 
show_message(const char *str, ...)
{
    XmString str2;
    static char last_message[256];
    Arg Args;
    va_list args;
    va_start(args, str);

    if (!str) {
	memset(last_message, ' ', sizeof(last_message)-1);
	last_message[sizeof(last_message)-1] = '\0';
    } else
	vsprintf(last_message, str, args);

    str2 = XmStringCreateSimple(last_message);
    XtSetArg(Args, XmNlabelString, str2);
    XtSetValues(MessageBox, &Args, 1);
}



static XtAppContext app_con;
static void (*execfunc)(void) = NULL;
static Widget dialog;

void
cmd_LeavePat(void)
{
    play_sound("goodbye");
    XtDestroyApplicationContext(app_con);
    exit(0);
}

static void
popup_confirm(const char *prompt)
{
    Arg Args[2];
    XmString str2;
    str2 = XmStringCreateLocalized((char *) prompt);
    XtSetArg(Args[0], XmNmessageString, str2);
    XtSetValues(dialog, Args, 1);
    XmStringFree(str2);
    XtManageChild(dialog);
}

static void
Cancel(Widget widget, XtPointer client_data, XtPointer call_data)
{
    XtUnmanageChild(dialog);
    execfunc = NULL;
}
static void
Ok(Widget widget, XtPointer client_data, XtPointer call_data)
{
    (*execfunc)();	/* execute the desired function */
    Cancel(NULL, dialog, NULL);
}

void
cmd_Cancel(void)
{
    if (execfunc)
	Cancel(NULL, dialog, NULL);
}

void
cmd_Confirm(void)
{
    if (execfunc) {
	(*execfunc)();	/* execute the desired function */
	Cancel(NULL, dialog, NULL);
    }
}

void
request_confirm(void (*dofunc)(void), const char *prompt)
{
    if (execfunc)
	return;		/* request pending => deny another one */
    execfunc = dofunc;
    popup_confirm(prompt);
}

static String fallback_resources[] = { 
    "*Tableau.borderWidth:		0",
    "*Tableau.backingStore:		WhenMapped",
    "*Tableau.keyboardFile:		keys",
    "*Tableau.messageFile:		messages",
    "*Tableau.arrowColor:		Gold",
    "*Tableau.markColor:		Black",
    "*Tableau.rules:		        Gypsy",
    "*Tableau.rng:		        1",
    "*help.okLabelString:		Close",
    "*help_popup.title:			Xpat Help",
    "*helptext.rows:			25",
    "*helptext.columns:			60",
    "*helptext.highlightThickness:	0",
    NULL
};

static XrmOptionDescRec options[] = {
    /* tableau resources */
    { "-xpmdir",	"*Tableau.xpmdir",	XrmoptionSepArg, NULL },
    { "-xpmcls",	"*Tableau.xpmcls",	XrmoptionSepArg, NULL },
#ifdef LOADCARDS
    { "-cards",		"*Tableau.cardset",	XrmoptionSepArg, NULL },
#endif
    { "-rules",		"*Tableau.rules",	XrmoptionSepArg, NULL },
    { "-faceup",	"*Tableau.faceup",	XrmoptionSepArg, NULL },
    { "-facedown",	"*Tableau.facedown",	XrmoptionSepArg, NULL },
    { "-decks",		"*Tableau.decks",	XrmoptionSepArg, NULL },
    { "-slots", 	"*Tableau.slots",	XrmoptionSepArg, NULL },
    { "-jokers",	"*Tableau.jokers",	XrmoptionSepArg, NULL },
    { "-tmps",		"*Tableau.tmps",	XrmoptionSepArg, NULL },
    { "-p0",        	"*Tableau.param0",	XrmoptionSepArg, NULL },
    { "-p1",        	"*Tableau.param1",	XrmoptionSepArg, NULL },
    { "-p2",		"*Tableau.param2",	XrmoptionSepArg, NULL },
    { "-p3",		"*Tableau.param3",	XrmoptionSepArg, NULL },
    { "-cb",        	"*Tableau.cardbackColor",XrmoptionSepArg,NULL },
    { "-tb",        	"*Tableau.background",	XrmoptionSepArg,NULL },
    { "-red",        	"*Tableau.RedColor",    XrmoptionSepArg, NULL },
    { "-markcolor",	"*Tableau.markColor",	XrmoptionSepArg, NULL },
    { "-arrowcolor",	"*Tableau.arrowColor",	XrmoptionSepArg, NULL },

    /* non-tableau resources */
#ifdef SOUND
    { "-sound", 	"*Sound.state",      	XrmoptionNoArg, (XtPointer)"True" },
    { "-nosound", 	"*Sound.state",      	XrmoptionNoArg, (XtPointer)"False" },
#endif
};

static void
HintNotify(Widget w, XEvent *xev, String *params, Cardinal *num)
{
    /* check to be sure state is still Set so that user can cancel
       the action (e.g. by moving outside the window, in the default
       bindings. */
    /* Nope, we cannot do this, the 'set' state is private data */
    /* CommandWidget cbw = (CommandWidget)w; 
    if (cbw->command.set)
	XtCallCallbackList(w, cbw->command.callbacks, (XtPointer) NULL); */
    switch (((XButtonPressedEvent *)xev)->button) {
    case Button1:
	cmd_NextHint();
	break;
    case Button2:
	cmd_DoHint();
	break;
    case Button3:
	cmd_PreviousHint();
    }
}

/* type converter functions: */
static void
mXtAP_Cancel (Widget w, XEvent *xev, String *params, Cardinal *num)
{
    cmd_Cancel();
}

static void
mXtAP_Confirm(Widget w, XEvent *xev, String *params, Cardinal *num)
{
    cmd_Confirm();
}

static XtActionsRec moreActions[] = {
    { "HintNotify",	HintNotify },
    { "Cancel",		mXtAP_Cancel },
    { "Ok",		mXtAP_Confirm }
};

char *loadfilename;

static void
process_extra_args(int argc, char *argv[])
{
    /* check extra args */
    game.seed = -1L;
    loadfilename = NULL;
    if (argc > 2) {
    usage:
	fprintf(stderr, "xpat: invalid argument: %s\n", argv[1]);
	exit(EXIT_FAILURE);
    } else if (argc == 2) {
	/* seed or load file */
	if (*argv[1] == '-')
	    goto usage;
	else if (isdigit(*argv[1])) {
	    game.seed = atol(argv[1]);
	    if (game.seed < 0L || game.seed >= 1000000000L)
		goto usage;
	} else {
	    loadfilename = argv[1];
	    /* printf("loadfile is %s\n", loadfilename); */
	}
    }
}

/*extern void cmd_DebugOut(void); */
extern struct rules *rulepool[];
static void
selectrules(Widget w, XtPointer number, XtPointer garbage)
{
    const char *s = XtName(w);
    /* printf("widget %s has been selected\n", s); */
    change_rules(s);
}

#ifdef SOUND
static Widget sound;

int
checksound(void)
{
    return XmToggleButtonGetState(sound);
}
#endif


typedef struct _menu_item {
    const char *label;
    WidgetClass *class;
    char mnemonic;
    const char *accelerator;
    const char *accel_text;
    XtCallbackProc callback;
    XtPointer callback_data;
} MenuItem;

static MenuItem game_items[] = {
    {
	"Drop Bookmark", &xmPushButtonGadgetClass, 0, NULL, NULL,
	perform_command, cmd_DropBookmark
    },
    {
	"Goto Bookmark", &xmPushButtonGadgetClass, 0, NULL, NULL,
	perform_command, cmd_GotoBookmark
    },
    {
	"Replay", &xmPushButtonGadgetClass, 0, NULL, NULL,
	perform_command, cmd_ReplayGame
    },
    {
	"Restart", &xmPushButtonGadgetClass, 0, NULL, NULL,
	perform_command, cmd_RestartGame
    },
    {
	"New Game", &xmPushButtonGadgetClass, 0, NULL, NULL,
	perform_command, rq_AnotherGame
    },
    {
	"Quit", &xmPushButtonGadgetClass, 0, NULL, NULL,
	perform_command, rq_LeavePat
    },
    {
	NULL, NULL, 0, NULL, NULL, NULL, NULL
    }
};

static MenuItem button_panel_items[] = {
    {
	"Cards", &xmPushButtonGadgetClass, 0, NULL, NULL,
	perform_command, cmd_DealCards
    },
    {
	"Undo",&xmPushButtonGadgetClass, 0, NULL, NULL,
	perform_command, cmd_UndoMove
    },
    {
	"Redo",	&xmPushButtonGadgetClass, 0, NULL, NULL,
	perform_command, cmd_RedoMove
    },
    {
	"Score", &xmPushButtonGadgetClass, 0, NULL, NULL,
	perform_command, cmd_ShowScore
    },
    {
	"Hint",	&xmPushButtonGadgetClass, 0, NULL, NULL,
	perform_command, cmd_NextHint
    },
    {
	"Move to Stack", &xmPushButtonGadgetClass, 0, NULL, NULL,
	perform_command, cmd_ToStack
    },
    {
	NULL, NULL, 0, NULL, NULL, NULL, NULL
    }

};

static Widget
BuildPulldownMenu(Widget parent, char *menu_title, char menu_mnemonic,
		  Boolean tear_off, MenuItem *items)
{
    Widget Pulldown, cascade, widget;
    int i;
    XmString str;

    Pulldown = XmCreatePulldownMenu(parent, "_pulldown", NULL, 0);
    if (tear_off)
	XtVaSetValues(Pulldown, XmNtearOffModel, XmTEAR_OFF_ENABLED, NULL);
    str = XmStringCreateLocalized(menu_title);
    cascade = XtVaCreateManagedWidget(menu_title, xmCascadeButtonWidgetClass,
				      parent,
				      XmNsubMenuId, Pulldown,
				      XmNlabelString, str,
				      XmNmnemonic, menu_mnemonic,
				      NULL);
    XmStringFree(str);
    /*
     * Now add the menu items 
     */

    for (i = 0; items[i].label != NULL; i++) {
	widget = XtVaCreateManagedWidget(items[i].label, *items[i].class,
					 Pulldown, NULL);
	if (items[i].mnemonic)
	    XtVaSetValues(widget, XmNmnemonic, items[i].mnemonic, NULL);
	if (items[i].accelerator) {
	    str = XmStringCreateLocalized((char *) items[i].accel_text);
	    XtVaSetValues(widget,
			  XmNaccelerator, items[i].accelerator,
			  XmNacceleratorText, str,
			  NULL);
	    XmStringFree(str);
	}
	if (items[i].callback)
	    XtAddCallback(widget, XmNactivateCallback,
			  items[i].callback, items[i].callback_data);
    }
    return cascade;
}

static Widget
BuildRulesMenu(Widget parent, char *menu_title, char menu_mnemonic,
		  Boolean tear_off)
{
    MenuItem *items, *item;
    struct rules **rp;
    Widget cascade;
    
    for (rp = rulepool; *rp; ++rp);
    items = (MenuItem *) XtMalloc(((rp - rulepool) + 1) * sizeof(MenuItem));
    for (rp = rulepool, item = items; *rp; ++rp, ++item) {
	item->label = (*rp)->shortname;
	item->class = &xmPushButtonGadgetClass;
	item->mnemonic = 0;
	item->accelerator = NULL;
	item->accel_text = NULL;
	item->callback = selectrules;
	item->callback_data = NULL;
    }
    item->label = NULL;
    item->class = NULL;
    item->mnemonic = 0;
    item->accelerator = NULL;
    item->accel_text = NULL;
    item->callback = NULL;
    item->callback_data = NULL;
    cascade = BuildPulldownMenu(parent, menu_title, menu_mnemonic,
				tear_off, items);
    XtFree((char *) items);
    return cascade;
}

static void
CreatePulldownMenu(Widget parent)
{
    Widget cascade;
    XmString str;

    BuildPulldownMenu(parent, "Game", 'G', False, game_items);
    BuildRulesMenu(parent, "Rules", 'R', False);
    /*    cascade = BuildPulldownMenu(parent, "Help", 'H', False, help_items); */
    str = XmStringCreateLocalized("Help");
    cascade = XtVaCreateManagedWidget("Help", xmCascadeButtonWidgetClass,
				      parent,
				      XmNlabelString, str,
				      XmNmnemonic, 'H',
				      NULL);
    XmStringFree(str);
    XtVaSetValues(parent, XmNmenuHelpWidget, cascade, NULL);
    XtAddCallback(cascade, XmNactivateCallback, popup_help, NULL);
}

static void
CreatePanelButtons(Widget parent, MenuItem *items)
{
    Widget widget;
    int i;
    XmString str;

    /*
     * Now add the buttons items 
     */

    for (i = 0; items[i].label != NULL; i++) {
	widget = XtVaCreateManagedWidget(items[i].label, *items[i].class,
					 parent,
					 XmNtraversalOn, False,
					 NULL);
	if (items[i].mnemonic)
	    XtVaSetValues(widget, XmNmnemonic, items[i].mnemonic, NULL);
	if (items[i].accelerator) {
	    str = XmStringCreateLocalized((char *) items[i].accel_text);
	    XtVaSetValues(widget,
			  XmNaccelerator, items[i].accelerator,
			  XmNacceleratorText, str,
			  NULL);
	    XmStringFree(str);
	}
	if (items[i].callback)
	    XtAddCallback(widget, XmNactivateCallback,
			  items[i].callback, items[i].callback_data);
    }
#ifdef SOUND
	sound = XtVaCreateManagedWidget("Sound", xmToggleButtonWidgetClass,
					 parent,
					 XmNtraversalOn, False,
					 NULL);
#endif

}

static Widget
CreateMainWindow(Widget parent)
{
    Widget ButtonPanel, Form, Frame, Separator;

    Form = XtCreateWidget("form", xmFormWidgetClass, parent, NULL, 0);

    ButtonPanel = XtVaCreateWidget("buttonPanel", xmRowColumnWidgetClass,
				   Form,
				   XmNorientation, XmHORIZONTAL,
				   XmNtopAttachment, XmATTACH_FORM,
				   XmNleftAttachment, XmATTACH_FORM,
				   XmNrightAttachment, XmATTACH_FORM,
				   NULL);
    CreatePanelButtons(ButtonPanel, button_panel_items);
    XtManageChild(ButtonPanel);

    Separator = XtVaCreateManagedWidget("separator",
					xmSeparatorWidgetClass,
					Form,
					XmNtopAttachment, XmATTACH_WIDGET,
					XmNtopWidget, ButtonPanel,
					XmNleftAttachment, XmATTACH_FORM,
					XmNrightAttachment, XmATTACH_FORM,
					XmNorientation, XmHORIZONTAL,
					NULL);
    MessageBox = XtVaCreateManagedWidget("messages", xmLabelWidgetClass,
					 Form,
					 XmNrecomputeSize, False,
					 XmNtopAttachment, XmATTACH_WIDGET,
					 XmNtopWidget, Separator,
					 XmNleftAttachment, XmATTACH_FORM,
					 XmNrightAttachment, XmATTACH_FORM,
					 XmNtraversalOn, False,
					 NULL);
    show_message(" ");

    Frame = XtVaCreateManagedWidget("frame", xmFrameWidgetClass,
				    Form,
				    XmNtopAttachment, XmATTACH_WIDGET,
				    XmNtopWidget, MessageBox,
				    XmNleftAttachment, XmATTACH_FORM,
				    XmNrightAttachment, XmATTACH_FORM,
				    XmNbottomAttachment, XmATTACH_FORM,
				    XmNshadowType, XmSHADOW_IN,
				    NULL);
    Desktop = XtVaCreateManagedWidget("desktop", tableauWidgetClass,
				      Frame,
				      NULL);

    XtManageChild(Form);
    return Form;
}


int
main(int argc, char *argv[])
{
    Widget menubar;
    Widget mainwid;
    Widget mainwindowwid;
    int i;
    XSetWindowAttributes winattr;
    long winmask;

    /* use the command line arguments concerning the widgets */
    switch_uid(1);
    toplevel = XtAppInitialize(&app_con, "XPat", options, XtNumber(options),
			       &argc, argv,
			       fallback_resources, NULL, 0);
    switch_uid(0);
    process_extra_args(argc, argv);
    XtAppAddActions(app_con, moreActions, XtNumber(moreActions));
    graphics_control(Disable);

    XtAddEventHandler(toplevel, (EventMask) 0, True,
		      _XEditResCheckMessages, NULL);


    /* ab hier neu */

    mainwid = XmCreateMainWindow (toplevel, "main", NULL, 0);

    menubar = XmCreateMenuBar(mainwid, "menuBar", NULL,0);
    CreatePulldownMenu(menubar);
    XtManageChild (menubar);


    mainwindowwid = CreateMainWindow(mainwid);
    XtManageChild (mainwid);

    dialog = XmCreateQuestionDialog(toplevel, "dialog", NULL, 0);
    XtAddCallback(dialog, XmNokCallback, Ok, NULL);
    XtAddCallback(dialog, XmNcancelCallback, Cancel, NULL);
    XtUnmanageChild(XmMessageBoxGetChild(dialog, XmDIALOG_HELP_BUTTON));

#ifdef ONLINE_HELP
    create_help(toplevel);
#endif
    geo.w_width = geo.w_height = 0;

    XmMainWindowSetAreas(mainwid, menubar, NULL, NULL, NULL, mainwindowwid);

    XtRealizeWidget(toplevel);
    mainwindow = XtWindow(toplevel);
    table  = XtWindow(Desktop);
    winattr.backing_store = card.cardset ? WhenMapped : NotUseful;
    winattr.border_pixel = blackpixel;
    winattr.bit_gravity = NorthWestGravity;
    winattr.event_mask = KeyPressMask | ExposureMask | ButtonPressMask | 
	ButtonReleaseMask | StructureNotifyMask | Button3MotionMask;
    winmask = CWBorderPixel | CWEventMask | CWBackingStore | CWBitGravity;
    XChangeWindowAttributes(dpy, table, winmask, &winattr);

    graphics_control(Enable);
#ifdef LABER
    printf("main function requests init_layout:\n");
#endif
    init_layout();			/* position the piles in a nice way */
    for (i = 0; i < game.numpiles; ++i)
	pile_resize(i);
    show_message(TXT_WELCOME, VERSION);
    XStoreName(dpy, mainwindow,
	       rules.longname ? rules.longname : rules.shortname);
    if (!geo.w_width) {
	geo.w_width = graphic.width;
	geo.w_height = graphic.height;
    }
    XtAppMainLoop(app_con);	/* does not return */
    return 0;			/* keep compiler happy */
}

void
Force_Resize(XSize_t w, XSize_t h) {
    /* for Xlib, we can use this size. It does include space for buttons and messagebox */
    /* for Xaw, we have to add the size of the buttonbox and the message window */
    /* note that the result may have a wrong height, due to recalculation of the box
       widget. A second call to this function will always give the correct result. */
    /* The overall size can be computed by adding the difference between the current
       size of the mainwindow - current size of viewport window */
#if 0
    {   Arg args[1];
        int hh, ww;
	hh = 0; ww = 0;
        XtSetArg(args[0], XmNheight, &hh);
        XtGetValues(sbv, args, 1);
        XtSetArg(args[0], XmNwidth, &ww);
        XtGetValues(sbh, args, 1);
	printf("viewport hat groesse %d,%d\n", ww, hh);
        h += hh - geo.w_height;	/* difference between overall size and Viewport size */
	w += ww - geo.w_width;
    }
#endif
    /* add offsets for borders & menu */
    w += 12;	/* quick, dirty. TODO: obtain true current offsets */
    h += 76;
    XResizeWindow(dpy, mainwindow, w, h);
    /* or should XSetWMSizeHints() be used? */
}
#endif







