/****************************************************************************
** XQtXPat2Window meta object code from reading C++ file 'XQtWindow.h'
**
** Created: Sun Nov 5 20:18:27 2000
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.2.0   edited 2000-08-31 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_XQtXPat2Window
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "XQtWindow.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *XQtXPat2Window::className() const
{
    return "XQtXPat2Window";
}

QMetaObject *XQtXPat2Window::metaObj = 0;

void XQtXPat2Window::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QMainWindow::className(), "QMainWindow") != 0 )
	badSuperclassWarning("XQtXPat2Window","QMainWindow");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString XQtXPat2Window::tr(const char* s)
{
    return qApp->translate( "XQtXPat2Window", s, 0 );
}

QString XQtXPat2Window::tr(const char* s, const char * c)
{
    return qApp->translate( "XQtXPat2Window", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* XQtXPat2Window::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QMainWindow::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void(XQtXPat2Window::*m1_t0)();
    typedef void(XQtXPat2Window::*m1_t1)();
    typedef void(XQtXPat2Window::*m1_t2)();
    typedef void(XQtXPat2Window::*m1_t3)();
    typedef void(XQtXPat2Window::*m1_t4)();
    typedef void(XQtXPat2Window::*m1_t5)();
    typedef void(XQtXPat2Window::*m1_t6)();
    typedef void(XQtXPat2Window::*m1_t7)();
    typedef void(XQtXPat2Window::*m1_t8)();
    typedef void(XQtXPat2Window::*m1_t9)();
    typedef void(XQtXPat2Window::*m1_t10)();
    typedef void(XQtXPat2Window::*m1_t11)();
    typedef void(XQtXPat2Window::*m1_t12)();
    typedef void(XQtXPat2Window::*m1_t13)();
    typedef void(XQtXPat2Window::*m1_t14)();
    typedef void(XQtXPat2Window::*m1_t15)();
    typedef void(XQtXPat2Window::*m1_t16)();
    typedef void(XQtXPat2Window::*m1_t17)();
    typedef void(XQtXPat2Window::*m1_t18)();
    typedef void(XQtXPat2Window::*m1_t19)();
    typedef void(XQtXPat2Window::*m1_t20)();
    typedef void(XQtXPat2Window::*m1_t21)();
    typedef void(XQtXPat2Window::*m1_t22)();
    typedef void(XQtXPat2Window::*m1_t23)();
    typedef void(XQtXPat2Window::*m1_t24)();
    typedef void(XQtXPat2Window::*m1_t25)();
    typedef void(XQtXPat2Window::*m1_t26)();
    typedef void(XQtXPat2Window::*m1_t27)();
    typedef void(XQtXPat2Window::*m1_t28)();
    typedef void(XQtXPat2Window::*m1_t29)();
    typedef void(XQtXPat2Window::*m1_t30)();
    typedef void(XQtXPat2Window::*m1_t31)();
    typedef void(XQtXPat2Window::*m1_t32)();
    typedef void(XQtXPat2Window::*m1_t33)();
    typedef void(XQtXPat2Window::*m1_t34)();
    typedef void(XQtXPat2Window::*m1_t35)();
    typedef void(XQtXPat2Window::*m1_t36)();
    typedef void(XQtXPat2Window::*m1_t37)();
    typedef void(XQtXPat2Window::*m1_t38)();
    typedef void(XQtXPat2Window::*m1_t39)();
    typedef void(XQtXPat2Window::*m1_t40)();
    typedef void(XQtXPat2Window::*m1_t41)();
    typedef void(XQtXPat2Window::*m1_t42)();
    typedef void(XQtXPat2Window::*m1_t43)();
    typedef void(XQtXPat2Window::*m1_t44)();
    typedef void(XQtXPat2Window::*m1_t45)();
    typedef void(XQtXPat2Window::*m1_t46)();
    typedef void(XQtXPat2Window::*m1_t47)();
    m1_t0 v1_0 = Q_AMPERSAND XQtXPat2Window::QtCmd_NewGame;
    m1_t1 v1_1 = Q_AMPERSAND XQtXPat2Window::QtCmd_SaveGame;
    m1_t2 v1_2 = Q_AMPERSAND XQtXPat2Window::QtCmd_LoadGame;
    m1_t3 v1_3 = Q_AMPERSAND XQtXPat2Window::QtCmd_UndoMove;
    m1_t4 v1_4 = Q_AMPERSAND XQtXPat2Window::QtCmd_RedoMove;
    m1_t5 v1_5 = Q_AMPERSAND XQtXPat2Window::QtCmd_RestartGame;
    m1_t6 v1_6 = Q_AMPERSAND XQtXPat2Window::QtCmd_DropBM;
    m1_t7 v1_7 = Q_AMPERSAND XQtXPat2Window::QtCmd_GotoBM;
    m1_t8 v1_8 = Q_AMPERSAND XQtXPat2Window::QtCmd_DealCards;
    m1_t9 v1_9 = Q_AMPERSAND XQtXPat2Window::QtCmd_ReplayGame;
    m1_t10 v1_10 = Q_AMPERSAND XQtXPat2Window::QtCmd_ShowScore;
    m1_t11 v1_11 = Q_AMPERSAND XQtXPat2Window::QtCmd_Info;
    m1_t12 v1_12 = Q_AMPERSAND XQtXPat2Window::QtCmd_ShowVersion;
    m1_t13 v1_13 = Q_AMPERSAND XQtXPat2Window::QtCmd_AllToStack;
    m1_t14 v1_14 = Q_AMPERSAND XQtXPat2Window::QtCmd_AllMoves;
    m1_t15 v1_15 = Q_AMPERSAND XQtXPat2Window::QtCmd_NextHint;
    m1_t16 v1_16 = Q_AMPERSAND XQtXPat2Window::QtCmd_PrevHint;
    m1_t17 v1_17 = Q_AMPERSAND XQtXPat2Window::QtCmd_DoHint;
    m1_t18 v1_18 = Q_AMPERSAND XQtXPat2Window::QtCmd_MinWindow;
    m1_t19 v1_19 = Q_AMPERSAND XQtXPat2Window::QtCmd_PrefWindow;
    m1_t20 v1_20 = Q_AMPERSAND XQtXPat2Window::QtCmd_AdaptWindow;
    m1_t21 v1_21 = Q_AMPERSAND XQtXPat2Window::QtCmd_RotateUp;
    m1_t22 v1_22 = Q_AMPERSAND XQtXPat2Window::QtCmd_RotateDown;
    m1_t23 v1_23 = Q_AMPERSAND XQtXPat2Window::QtCmd_rSpider;
    m1_t24 v1_24 = Q_AMPERSAND XQtXPat2Window::QtCmd_rGypsy;
    m1_t25 v1_25 = Q_AMPERSAND XQtXPat2Window::QtCmd_rKlondike;
    m1_t26 v1_26 = Q_AMPERSAND XQtXPat2Window::QtCmd_rSHT;
    m1_t27 v1_27 = Q_AMPERSAND XQtXPat2Window::QtCmd_rFreeCell;
    m1_t28 v1_28 = Q_AMPERSAND XQtXPat2Window::QtCmd_rIdiots;
    m1_t29 v1_29 = Q_AMPERSAND XQtXPat2Window::QtCmd_rMC;
    m1_t30 v1_30 = Q_AMPERSAND XQtXPat2Window::QtCmd_rMO;
    m1_t31 v1_31 = Q_AMPERSAND XQtXPat2Window::QtCmd_rCalc;
    m1_t32 v1_32 = Q_AMPERSAND XQtXPat2Window::QtCmd_rmodCan;
    m1_t33 v1_33 = Q_AMPERSAND XQtXPat2Window::QtCmd_rMichaels;
    m1_t34 v1_34 = Q_AMPERSAND XQtXPat2Window::QtCmd_rCanfield;
    m1_t35 v1_35 = Q_AMPERSAND XQtXPat2Window::QtCmd_rRC;
    m1_t36 v1_36 = Q_AMPERSAND XQtXPat2Window::QtCmd_rBakers;
    m1_t37 v1_37 = Q_AMPERSAND XQtXPat2Window::QtCmd_rOonsoo;
    m1_t38 v1_38 = Q_AMPERSAND XQtXPat2Window::QtCmd_rBluemoon;
    m1_t39 v1_39 = Q_AMPERSAND XQtXPat2Window::about;
    m1_t40 v1_40 = Q_AMPERSAND XQtXPat2Window::toggleMenuBar;
    m1_t41 v1_41 = Q_AMPERSAND XQtXPat2Window::toggleStatusBar;
    m1_t42 v1_42 = Q_AMPERSAND XQtXPat2Window::toggleToolBar;
    m1_t43 v1_43 = Q_AMPERSAND XQtXPat2Window::toggleSound;
    m1_t44 v1_44 = Q_AMPERSAND XQtXPat2Window::toggleDragNDrop;
    m1_t45 v1_45 = Q_AMPERSAND XQtXPat2Window::toggleAnimation;
    m1_t46 v1_46 = Q_AMPERSAND XQtXPat2Window::QtCmd_hlpKeys;
    m1_t47 v1_47 = Q_AMPERSAND XQtXPat2Window::QtCmd_hlpRules;
    QMetaData *slot_tbl = QMetaObject::new_metadata(48);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(48);
    slot_tbl[0].name = "QtCmd_NewGame()";
    slot_tbl[0].ptr = (QMember)v1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "QtCmd_SaveGame()";
    slot_tbl[1].ptr = (QMember)v1_1;
    slot_tbl_access[1] = QMetaData::Private;
    slot_tbl[2].name = "QtCmd_LoadGame()";
    slot_tbl[2].ptr = (QMember)v1_2;
    slot_tbl_access[2] = QMetaData::Private;
    slot_tbl[3].name = "QtCmd_UndoMove()";
    slot_tbl[3].ptr = (QMember)v1_3;
    slot_tbl_access[3] = QMetaData::Private;
    slot_tbl[4].name = "QtCmd_RedoMove()";
    slot_tbl[4].ptr = (QMember)v1_4;
    slot_tbl_access[4] = QMetaData::Private;
    slot_tbl[5].name = "QtCmd_RestartGame()";
    slot_tbl[5].ptr = (QMember)v1_5;
    slot_tbl_access[5] = QMetaData::Private;
    slot_tbl[6].name = "QtCmd_DropBM()";
    slot_tbl[6].ptr = (QMember)v1_6;
    slot_tbl_access[6] = QMetaData::Private;
    slot_tbl[7].name = "QtCmd_GotoBM()";
    slot_tbl[7].ptr = (QMember)v1_7;
    slot_tbl_access[7] = QMetaData::Private;
    slot_tbl[8].name = "QtCmd_DealCards()";
    slot_tbl[8].ptr = (QMember)v1_8;
    slot_tbl_access[8] = QMetaData::Private;
    slot_tbl[9].name = "QtCmd_ReplayGame()";
    slot_tbl[9].ptr = (QMember)v1_9;
    slot_tbl_access[9] = QMetaData::Private;
    slot_tbl[10].name = "QtCmd_ShowScore()";
    slot_tbl[10].ptr = (QMember)v1_10;
    slot_tbl_access[10] = QMetaData::Private;
    slot_tbl[11].name = "QtCmd_Info()";
    slot_tbl[11].ptr = (QMember)v1_11;
    slot_tbl_access[11] = QMetaData::Private;
    slot_tbl[12].name = "QtCmd_ShowVersion()";
    slot_tbl[12].ptr = (QMember)v1_12;
    slot_tbl_access[12] = QMetaData::Private;
    slot_tbl[13].name = "QtCmd_AllToStack()";
    slot_tbl[13].ptr = (QMember)v1_13;
    slot_tbl_access[13] = QMetaData::Private;
    slot_tbl[14].name = "QtCmd_AllMoves()";
    slot_tbl[14].ptr = (QMember)v1_14;
    slot_tbl_access[14] = QMetaData::Private;
    slot_tbl[15].name = "QtCmd_NextHint()";
    slot_tbl[15].ptr = (QMember)v1_15;
    slot_tbl_access[15] = QMetaData::Private;
    slot_tbl[16].name = "QtCmd_PrevHint()";
    slot_tbl[16].ptr = (QMember)v1_16;
    slot_tbl_access[16] = QMetaData::Private;
    slot_tbl[17].name = "QtCmd_DoHint()";
    slot_tbl[17].ptr = (QMember)v1_17;
    slot_tbl_access[17] = QMetaData::Private;
    slot_tbl[18].name = "QtCmd_MinWindow()";
    slot_tbl[18].ptr = (QMember)v1_18;
    slot_tbl_access[18] = QMetaData::Private;
    slot_tbl[19].name = "QtCmd_PrefWindow()";
    slot_tbl[19].ptr = (QMember)v1_19;
    slot_tbl_access[19] = QMetaData::Private;
    slot_tbl[20].name = "QtCmd_AdaptWindow()";
    slot_tbl[20].ptr = (QMember)v1_20;
    slot_tbl_access[20] = QMetaData::Private;
    slot_tbl[21].name = "QtCmd_RotateUp()";
    slot_tbl[21].ptr = (QMember)v1_21;
    slot_tbl_access[21] = QMetaData::Private;
    slot_tbl[22].name = "QtCmd_RotateDown()";
    slot_tbl[22].ptr = (QMember)v1_22;
    slot_tbl_access[22] = QMetaData::Private;
    slot_tbl[23].name = "QtCmd_rSpider()";
    slot_tbl[23].ptr = (QMember)v1_23;
    slot_tbl_access[23] = QMetaData::Private;
    slot_tbl[24].name = "QtCmd_rGypsy()";
    slot_tbl[24].ptr = (QMember)v1_24;
    slot_tbl_access[24] = QMetaData::Private;
    slot_tbl[25].name = "QtCmd_rKlondike()";
    slot_tbl[25].ptr = (QMember)v1_25;
    slot_tbl_access[25] = QMetaData::Private;
    slot_tbl[26].name = "QtCmd_rSHT()";
    slot_tbl[26].ptr = (QMember)v1_26;
    slot_tbl_access[26] = QMetaData::Private;
    slot_tbl[27].name = "QtCmd_rFreeCell()";
    slot_tbl[27].ptr = (QMember)v1_27;
    slot_tbl_access[27] = QMetaData::Private;
    slot_tbl[28].name = "QtCmd_rIdiots()";
    slot_tbl[28].ptr = (QMember)v1_28;
    slot_tbl_access[28] = QMetaData::Private;
    slot_tbl[29].name = "QtCmd_rMC()";
    slot_tbl[29].ptr = (QMember)v1_29;
    slot_tbl_access[29] = QMetaData::Private;
    slot_tbl[30].name = "QtCmd_rMO()";
    slot_tbl[30].ptr = (QMember)v1_30;
    slot_tbl_access[30] = QMetaData::Private;
    slot_tbl[31].name = "QtCmd_rCalc()";
    slot_tbl[31].ptr = (QMember)v1_31;
    slot_tbl_access[31] = QMetaData::Private;
    slot_tbl[32].name = "QtCmd_rmodCan()";
    slot_tbl[32].ptr = (QMember)v1_32;
    slot_tbl_access[32] = QMetaData::Private;
    slot_tbl[33].name = "QtCmd_rMichaels()";
    slot_tbl[33].ptr = (QMember)v1_33;
    slot_tbl_access[33] = QMetaData::Private;
    slot_tbl[34].name = "QtCmd_rCanfield()";
    slot_tbl[34].ptr = (QMember)v1_34;
    slot_tbl_access[34] = QMetaData::Private;
    slot_tbl[35].name = "QtCmd_rRC()";
    slot_tbl[35].ptr = (QMember)v1_35;
    slot_tbl_access[35] = QMetaData::Private;
    slot_tbl[36].name = "QtCmd_rBakers()";
    slot_tbl[36].ptr = (QMember)v1_36;
    slot_tbl_access[36] = QMetaData::Private;
    slot_tbl[37].name = "QtCmd_rOonsoo()";
    slot_tbl[37].ptr = (QMember)v1_37;
    slot_tbl_access[37] = QMetaData::Private;
    slot_tbl[38].name = "QtCmd_rBluemoon()";
    slot_tbl[38].ptr = (QMember)v1_38;
    slot_tbl_access[38] = QMetaData::Private;
    slot_tbl[39].name = "about()";
    slot_tbl[39].ptr = (QMember)v1_39;
    slot_tbl_access[39] = QMetaData::Private;
    slot_tbl[40].name = "toggleMenuBar()";
    slot_tbl[40].ptr = (QMember)v1_40;
    slot_tbl_access[40] = QMetaData::Private;
    slot_tbl[41].name = "toggleStatusBar()";
    slot_tbl[41].ptr = (QMember)v1_41;
    slot_tbl_access[41] = QMetaData::Private;
    slot_tbl[42].name = "toggleToolBar()";
    slot_tbl[42].ptr = (QMember)v1_42;
    slot_tbl_access[42] = QMetaData::Private;
    slot_tbl[43].name = "toggleSound()";
    slot_tbl[43].ptr = (QMember)v1_43;
    slot_tbl_access[43] = QMetaData::Private;
    slot_tbl[44].name = "toggleDragNDrop()";
    slot_tbl[44].ptr = (QMember)v1_44;
    slot_tbl_access[44] = QMetaData::Private;
    slot_tbl[45].name = "toggleAnimation()";
    slot_tbl[45].ptr = (QMember)v1_45;
    slot_tbl_access[45] = QMetaData::Private;
    slot_tbl[46].name = "QtCmd_hlpKeys()";
    slot_tbl[46].ptr = (QMember)v1_46;
    slot_tbl_access[46] = QMetaData::Private;
    slot_tbl[47].name = "QtCmd_hlpRules()";
    slot_tbl[47].ptr = (QMember)v1_47;
    slot_tbl_access[47] = QMetaData::Private;
    metaObj = QMetaObject::new_metaobject(
	"XQtXPat2Window", "QMainWindow",
	slot_tbl, 48,
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
