/* -*- C++ -*-	Time-stamp: <05 Nov 00 21:19:27 Michael Bischoff> */
/*
   Description:
   class QMaskEdit is an extension of the QLineEdit widget.
   A QMaskEdit widget does accept only digits as input (and possibly a sign)
   and only if the range set is not violated.
   This is implemented by filtering the keyPressEvents

   Sources:
   qmaskedit.h		header file
   qmaskedit.cpp	implements the class
   mqmaskedit.cpp	generated by moc

   Dependencies:
   requires the widget qmaskedit and the Qt library (tested with version 1.42)

   Author:
   Michael Bischoff	(Michael.Bischoff@gmx.net)
*/

#include "qmaskedit.h"
#include <qkeycode.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int compute_length(int num) {
    int len = 1;
    if (num < 0) {
	len = 2;
	num = -num;
    }
    while (num >= 10) {
	num /= 10;
	++len;
    }
    return len;
}

void QMaskEdit::setRange(int maxn, int minn) {
    int len1, len2;
    maxnum  = maxn;
    minnum  = minn;
    if (maxnum < 0)
	maxnum = 0;
    if (minnum > maxnum)
	minnum = 0;
    if (maxnum > 9999)
	maxnum = 9999;
    if (minnum < -9999)
	minnum = -9999;
    len1 = compute_length(minnum);
    len2 = compute_length(maxnum);
    fieldsize = len2 > len1 ? len2 : len1;
    setMaxLength(fieldsize);
}

QMaskEdit::QMaskEdit(int maxn, int minn, QWidget *parent, const char *name)
  : QLineEdit(parent, name) {
    setRange(maxn, minn);
}

void QMaskEdit::setValue(int val) {
    char buff[20];
    if (val < minnum || val > maxnum)
	val = maxnum;
    sprintf(buff, "%*d", fieldsize, val);
    setText(buff);
}

int QMaskEdit::value() {
    int val = atoi(text());
    if (val < minnum || val > maxnum)
	val = maxnum;
    return val;
}

void QMaskEdit::keyPressEvent( QKeyEvent *qe ) {

    int num = atoi(text());
    int keycode = qe->ascii();
    char buff[20];

    if (keycode == '-') {
	num = -num;
	if (num < minnum || num > maxnum)
	    return;	// ignore key
	// ok, accept it.
	sprintf(buff, "%*d", fieldsize, num);
	setText(buff);
	return;
    }
    if (keycode >= ' ' &&
	qe->key() != Key_Delete &&
	qe->key() != Key_Backspace ) {
	if (!isdigit(keycode))
	    // no digit, but displayable char: ignore it!
	    return;
	else {
	    num = 10 * num + keycode - '0';
	    if (num < minnum || num > maxnum)
		return;	// ignore key
	    // ok, accept it.
	    sprintf(buff, "%*d", fieldsize, num);
	    setText(buff);
	    return;
	}
    }
    QLineEdit::keyPressEvent(qe);
}