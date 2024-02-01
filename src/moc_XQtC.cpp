/****************************************************************************
** XQtCards meta object code from reading C++ file 'XQtCards.h'
**
** Created: Sun Nov 5 20:19:48 2000
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.2.0   edited 2000-08-31 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_XQtCards
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "XQtCards.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *XQtCards::className() const
{
    return "XQtCards";
}

QMetaObject *XQtCards::metaObj = 0;

void XQtCards::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QObject::className(), "QObject") != 0 )
	badSuperclassWarning("XQtCards","QObject");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString XQtCards::tr(const char* s)
{
    return qApp->translate( "XQtCards", s, 0 );
}

QString XQtCards::tr(const char* s, const char * c)
{
    return qApp->translate( "XQtCards", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* XQtCards::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QObject::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void(XQtCards::*m1_t0)();
    typedef void(XQtCards::*m1_t1)();
    typedef void(XQtCards::*m1_t2)();
    typedef void(XQtCards::*m1_t3)();
    typedef void(XQtCards::*m1_t4)();
    m1_t0 v1_0 = Q_AMPERSAND XQtCards::cards_reset;
    m1_t1 v1_1 = Q_AMPERSAND XQtCards::cards_apply;
    m1_t2 v1_2 = Q_AMPERSAND XQtCards::cards_ok;
    m1_t3 v1_3 = Q_AMPERSAND XQtCards::cards_cancel;
    m1_t4 v1_4 = Q_AMPERSAND XQtCards::cards_browse;
    QMetaData *slot_tbl = QMetaObject::new_metadata(5);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(5);
    slot_tbl[0].name = "cards_reset()";
    slot_tbl[0].ptr = (QMember)v1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "cards_apply()";
    slot_tbl[1].ptr = (QMember)v1_1;
    slot_tbl_access[1] = QMetaData::Private;
    slot_tbl[2].name = "cards_ok()";
    slot_tbl[2].ptr = (QMember)v1_2;
    slot_tbl_access[2] = QMetaData::Private;
    slot_tbl[3].name = "cards_cancel()";
    slot_tbl[3].ptr = (QMember)v1_3;
    slot_tbl_access[3] = QMetaData::Private;
    slot_tbl[4].name = "cards_browse()";
    slot_tbl[4].ptr = (QMember)v1_4;
    slot_tbl_access[4] = QMetaData::Private;
    typedef void(XQtCards::*m2_t0)();
    m2_t0 v2_0 = Q_AMPERSAND XQtCards::cards_changed;
    QMetaData *signal_tbl = QMetaObject::new_metadata(1);
    signal_tbl[0].name = "cards_changed()";
    signal_tbl[0].ptr = (QMember)v2_0;
    metaObj = QMetaObject::new_metaobject(
	"XQtCards", "QObject",
	slot_tbl, 5,
	signal_tbl, 1,
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

// SIGNAL cards_changed
void XQtCards::cards_changed()
{
    activate_signal( "cards_changed()" );
}
