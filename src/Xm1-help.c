/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module Xm1-help.c			     */
/*									     */
/*	Online help systems for the Motif Widget interface		     */
/*	written by Karsten Jensen (karsten.w.jensen@get2net.dk)		     */
/*	October-2000							     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/
#ifdef ONLINE_HELP
#ifdef useXm
#include "X-pat.h"
#include "Tableau.h"
#include "Xm1-help.h"

#include <Xm/MessageB.h>
#include <Xm/Form.h>
#include <Xm/TextP.h>
#include <Xm/List.h>
#include <Xm/PushBG.h>
#include <Xm/CascadeBG.h>
#include <unistd.h>


static int help_active = 0;
static Widget help, helplist, helptext;

#define TXT_HELPFILES		(xpat_messages+71)
extern struct rules *rulepool[];

static void
selecttopic(Widget w,  XtPointer client_data, XtPointer call_data)
{
    XmListCallbackStruct *cb = (XmListCallbackStruct *) call_data;
    Widget text = (Widget) client_data;
    char filename[256];
    const char *langdir = get_lang();
    int i = cb->item_position  == 1 ? 0: cb->item_position + 3;
    char *buffer;
    XmTextPosition position;
    FILE *fd;
    int bytes_read, file_size;
    
    if (TXT_HELPFILES[i][0] != '/') {
        if (*langdir) {
  	    sprintf(filename, "%s/%s/%s", LIBDIR, langdir, TXT_HELPFILES[i]);
	    if (access(filename, R_OK))
	        langdir = "";
	}
        if (!*langdir)
	    sprintf(filename, "%s/%s", LIBDIR, TXT_HELPFILES[i]);
    }
    else {
	strcpy(filename, TXT_HELPFILES[i]);
    }
    fd = fopen(filename, "r");
    if (fd == NULL) {
	char warnstring[300];
	sprintf(warnstring, "Warning could not find %s\n", filename);
	XtWarning(warnstring);
	return;
    }

    fseek(fd, 0L, SEEK_END);
    file_size = ftell(fd);
    if (file_size == 0) {
	char warnstring[300];
	sprintf(warnstring, "Warning file %s has zero size\n", filename);
	XtWarning(warnstring);
	return;
    }
    rewind(fd);
    buffer = XtMalloc((file_size + 1) * sizeof(char));
    bytes_read = fread(buffer, sizeof(char), file_size, fd);
    if (bytes_read > 0) {
	buffer[bytes_read] = 0;
	position = XmTextGetLastPosition(text);
	XmTextReplace(text, 0, position, buffer);
	XmTextSetCursorPosition(text, 0);
    }
    XtFree(buffer);
    fclose(fd);
    XmProcessTraversal(text, XmTRAVERSE_CURRENT);
}

static void
traverse_helptext(Widget widget, XtPointer closure, XEvent *event,
		  Boolean *continue_to_dispatch)
{
    if (event->type == MapNotify) {
	XmProcessTraversal((Widget) closure, XmTRAVERSE_CURRENT);
    }
    *continue_to_dispatch = True;
}

void
create_help(Widget toplevel)
{
    Widget helpform;
    Arg Args[10];
    int n;
    XmString item_str;
    struct rules **rp;

    help = XmCreateMessageDialog(toplevel, "help", NULL, 0);
    XtAddCallback(help, XmNokCallback,
			  popdown_help, NULL);
    XtUnmanageChild(XmMessageBoxGetChild(help, XmDIALOG_HELP_BUTTON));
    XtUnmanageChild(XmMessageBoxGetChild(help, XmDIALOG_CANCEL_BUTTON));
    XtUnmanageChild(XmMessageBoxGetChild(help, XmDIALOG_MESSAGE_LABEL));
    helpform = XtCreateWidget("helpform", xmFormWidgetClass, help,
				      NULL, 0);
    n = 0;
    XtSetArg(Args[n], XmNtopAttachment, XmATTACH_FORM); n++;
    XtSetArg(Args[n], XmNtopAttachment, XmATTACH_FORM); n++;
    XtSetArg(Args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
    XtSetArg(Args[n], XmNselectionPolicy, XmBROWSE_SELECT); n++;
    helplist = XmCreateScrolledList(helpform, "helplist", Args, n);
    item_str = XmStringCreateLocalized((char *) TXT_HELP_KEYS);
    XmListAddItem(helplist,item_str, 0);
    XmStringFree(item_str);
    for (rp = rulepool; *rp; ++rp) {
	item_str = XmStringCreateLocalized((char *) (*rp)->shortname);
	XmListAddItem(helplist,item_str, 0);
	XmStringFree(item_str);
    }
    XtManageChild(helplist);
    n = 0;
    XtSetArg(Args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
    XtSetArg(Args[n], XmNleftWidget, XtParent(helplist)); n++;
    XtSetArg(Args[n], XmNleftOffset, 10); n++;
    XtSetArg(Args[n], XmNtopAttachment, XmATTACH_FORM); n++;
    XtSetArg(Args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
    XtSetArg(Args[n], XmNeditable, False); n++;
    XtSetArg(Args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
    XtSetArg(Args[n], XmNcursorPositionVisible, False); n++;
    helptext = XmCreateScrolledText(helpform, "helptext", Args, n);
    XtAddCallback(helplist, XmNbrowseSelectionCallback, selecttopic, helptext);
    XtAddEventHandler(help, StructureNotifyMask, True, 
		      traverse_helptext, helptext);
    XmListSelectPos(helplist, 1, True);
    XmListSetPos(helplist, 1);
    XtManageChild(helptext);
    XtManageChild(helpform);
}

void
popup_help(Widget w, XtPointer client_data, XtPointer call_data)
{
    if (help_active)
	return;		/* request pending => deny another one */
    XmListSelectPos(helplist, 1, True);
    XmListSetPos(helplist, 1);
    XmProcessTraversal(helptext, XmTRAVERSE_CURRENT);
    help_active = 1;

    XtManageChild(help);
}

void
popdown_help(Widget w, XtPointer client_data, XtPointer call_data)
{
    if (!help_active)
	return;		/* request pending => deny another one */
    help_active = 0;
    /*    XtPopdown(XtParent(help)); */
}

#endif
#endif
