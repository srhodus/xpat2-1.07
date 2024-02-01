/* -*- C++ -*-	Time-stamp: <05 Nov 00 21:19:14 Michael Bischoff> */
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

#ifndef QMASKEDIT_H
#define QMASKEDIT_H

#ifndef QLINEEDIT_H
#include <qlineedit.h>
#endif

class Q_EXPORT QMaskEdit : public QLineEdit {
    Q_OBJECT
public:
    QMaskEdit(int maxn = 99, int minn = 0, QWidget *parent = 0, const char *name = 0);
    void setRange(int maxn = 99, int minn = 0);
    int getFieldSize()	const { return fieldsize; }
    void setValue(int value);
    int value();
private:
    int maxnum;
    int minnum;
    int fieldsize;
protected:
    void	keyPressEvent( QKeyEvent * );
};
#endif
