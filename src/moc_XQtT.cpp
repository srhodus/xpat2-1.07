/****************************************************************************
** XQtTableau meta object code from reading C++ file 'XQtTableau.h'
**
** Created: Sun Nov 5 20:18:15 2000
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.2.0   edited 2000-08-31 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_XQtTableau
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "XQtTableau.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *XQtTableau::className() const
{
    return "XQtTableau";
}

QMetaObject *XQtTableau::metaObj = 0;

void XQtTableau::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("XQtTableau","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString XQtTableau::tr(const char* s)
{
    return qApp->translate( "XQtTableau", s, 0 );
}

QString XQtTableau::tr(const char* s, const char * c)
{
    return qApp->translate( "XQtTableau", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* XQtTableau::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void(XQtTableau::*m1_t0)();
    typedef void(XQtTableau::*m1_t1)(XQtCardPile*,int,int,bool,int,int,int);
    typedef void(XQtTableau::*m1_t2)();
    typedef void(XQtTableau::*m1_t3)(int,int);
    typedef void(XQtTableau::*m1_t4)(int,int);
    typedef void(XQtTableau::*m1_t5)();
    typedef void(XQtTableau::*m1_t6)();
    typedef void(XQtTableau::*m1_t7)();
    m1_t0 v1_0 = Q_AMPERSAND XQtTableau::move_dragpile;
    m1_t1 v1_1 = Q_AMPERSAND XQtTableau::startDrag;
    m1_t2 v1_2 = Q_AMPERSAND XQtTableau::stopDrag;
    m1_t3 v1_3 = Q_AMPERSAND XQtTableau::Drag;
    m1_t4 v1_4 = Q_AMPERSAND XQtTableau::startAnimate;
    m1_t5 v1_5 = Q_AMPERSAND XQtTableau::CustomizeModal;
    m1_t6 v1_6 = Q_AMPERSAND XQtTableau::CustomizeModeless;
    m1_t7 v1_7 = Q_AMPERSAND XQtTableau::repaintAll;
    QMetaData *slot_tbl = QMetaObject::new_metadata(8);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(8);
    slot_tbl[0].name = "move_dragpile()";
    slot_tbl[0].ptr = (QMember)v1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "startDrag(XQtCardPile*,int,int,bool,int,int,int)";
    slot_tbl[1].ptr = (QMember)v1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "stopDrag()";
    slot_tbl[2].ptr = (QMember)v1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "Drag(int,int)";
    slot_tbl[3].ptr = (QMember)v1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "startAnimate(int,int)";
    slot_tbl[4].ptr = (QMember)v1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "CustomizeModal()";
    slot_tbl[5].ptr = (QMember)v1_5;
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "CustomizeModeless()";
    slot_tbl[6].ptr = (QMember)v1_6;
    slot_tbl_access[6] = QMetaData::Public;
    slot_tbl[7].name = "repaintAll()";
    slot_tbl[7].ptr = (QMember)v1_7;
    slot_tbl_access[7] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"XQtTableau", "QWidget",
	slot_tbl, 8,
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
