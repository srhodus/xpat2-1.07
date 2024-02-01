/****************************************************************************
** QMaskEdit meta object code from reading C++ file 'qmaskedit.h'
**
** Created: Sun Nov 5 20:22:25 2000
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.2.0   edited 2000-08-31 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_QMaskEdit
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "qmaskedit.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *QMaskEdit::className() const
{
    return "QMaskEdit";
}

QMetaObject *QMaskEdit::metaObj = 0;

void QMaskEdit::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QLineEdit::className(), "QLineEdit") != 0 )
	badSuperclassWarning("QMaskEdit","QLineEdit");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString QMaskEdit::tr(const char* s)
{
    return qApp->translate( "QMaskEdit", s, 0 );
}

QString QMaskEdit::tr(const char* s, const char * c)
{
    return qApp->translate( "QMaskEdit", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* QMaskEdit::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QLineEdit::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"QMaskEdit", "QLineEdit",
	0, 0,
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
