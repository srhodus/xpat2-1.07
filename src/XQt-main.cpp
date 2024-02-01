/****************************************************************************
** $Id: main.cpp,v 1.6 1998/06/16 11:39:32 warwick Exp $
**
** Copyright (C) 1992-1998 Troll Tech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#include <qapplication.h>
#include "XQtWindow.h"

/* flush event queue */
extern "C" void flush_display(void) {
    QApplication::syncX();
    QApplication::flushX();
}

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include "usage.c"
#include "xpatgame.h"
}
const char *loadfilename = NULL;

int main(int argc, char *argv[]) {
    QApplication a( argc, argv );
#include "options.c"
    for (i = 0; i < NUMOPTIONS; ++i) {  /* get resources from server */
	char *s;
        if (options[i].cmdarg)
	    options[i].value = options[i].cmdarg;
#if 0
        else if ((s = XGetDefault(dpy, "XPat", options[i].resource)))
	    options[i].value = s;
#endif
    }

    for (i = 0; i < NUMOPTIONS; ++i) {  /* value-check Numbers */
	int n;
	struct option_struct *o;
	o = options + i;
        if (o->type == Number) {
	    n = o->value ? atoi(o->value) : -1;
	    if (n < o->minval || n > o->maxval) {
		char s[100];
		sprintf(s, "argument to option \"%s\" / resource \"%s\"",
                    o->option, o->resource);
                usage(s);
            }
            *(int *)(o->where) = n;
        } else if (o->type == Self) {
            *(int *)(o->where) = 1;
        } else /* type == String */
            *(const char **)(o->where) = o->value;
    }

    if (restoregame &&
       (decks != -1 || Xslots != -1 || faceup != -1 || facedown != -1))
	  fprintf(stderr, "warning: customization parameters are ignored\n");


    XQtXPat2Window * mw = new XQtXPat2Window(ruleset, seed);
	mw->resize(800,600);
    a.setMainWidget(mw);
    mw->setCaption( "XPat2 - Qt version" );
    mw->show();
    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    return a.exec();
}
