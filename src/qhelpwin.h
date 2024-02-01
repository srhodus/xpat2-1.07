/* -*- C++ -*-	Time-stamp: <15 May 99 20:56:18 Michael Bischoff> */
/*
   Description:
   class QHelpWindow displays a simple help window.
   The window is not modal and may be closed at any time.

   Sources:
   qhelpwin.h		header file
   qhelpwin.cpp		implements the class
   mhelpwin.cpp		generated by moc

   Dependencies:
   requires the widget qmultilineedit and the Qt library (tested with version 1.42)

   Author:
   Michael Bischoff	(Michael.Bischoff@gmx.net)
*/

#include <qwidget.h>

class QMultiLineEdit;
class QPushButton;
class QVBoxLayout;

class QHelpWindow : public QWidget {
    Q_OBJECT
private:
    QMultiLineEdit *e;
    QVBoxLayout *v;
    QWidget *w;
    QPushButton *close;
public:
    QHelpWindow(const char *filename, const char *caption);
    ~QHelpWindow();
public slots:
    void closeHelp();
};
