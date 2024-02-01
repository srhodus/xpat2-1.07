/****************************************************************************
** QHelpWindow meta object code from reading C++ file 'qhelpwin.h'
**
** Created: Sun Nov 5 20:23:03 2000
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.2.0   edited 2000-08-31 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_QHelpWindow
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "qhelpwin.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *QHelpWindow::className() const
{
    return "QHelpWindow";
}

QMetaObject *QHelpWindow::metaObj = 0;

void QHelpWindow::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("QHelpWindow","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString QHelpWindow::tr(const char* s)
{
    return qApp->translate( "QHelpWindow", s, 0 );
}

QString QHelpWindow::tr(const char* s, const char * c)
{
    return qApp->translate( "QHelpWindow", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* QHelpWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void(QHelpWindow::*m1_t0)();
    m1_t0 v1_0 = Q_AMPERSAND QHelpWindow::closeHelp;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "closeHelp()";
    slot_tbl[0].ptr = (QMember)v1_0;
    slot_tbl_access[0] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"QHelpWindow", "QWidget",
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}
