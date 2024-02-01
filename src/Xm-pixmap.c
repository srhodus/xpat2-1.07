/************************************************************************/
/* MODULE   : Xm-pixmap.c                                               */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/*          : Pixmaps for icons and buttons                             */
/* AUTHOR   : Christian Anzenberger                                     */
/* CONTACT  : christian.anzenberger@siemens.at                          */
/* CREATED  : 1999-02-13                                                */
/* NOTES    : see README.motif for details on release                   */
/*          : see COPYRIGHT.motif for details on copyright              */
/************************************************************************/
/* History of Change:                                                   */
/*-------+--------+----------------------------------------------+------*/
/*Version|  Date  | Changes                                      |Author*/
/*-------+--------+----------------------------------------------+------*/
/* 0.1   |19990213| Initial creation for xpat2-1.04              | ac   */
/************************************************************************/

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#include <xpm.h>

#include "Xpat2.icon.pm"
#include "Xpat2.l.pm"
#include "Xpat2B.l.pm"
#ifdef KDESTYLE
#include "./Xpm.KDE/DealCard.m.pm"
#include "./Xpm.KDE/Undo.m.pm"
#include "./Xpm.KDE/UndoU.m.pm"
#include "./Xpm.KDE/Redo.m.pm"
#include "./Xpm.KDE/RedoU.m.pm"
#include "./Xpm.KDE/Replay.m.pm"
#include "./Xpm.KDE/ReplayU.m.pm"
#include "./Xpm.KDE/Restart.m.pm"
#include "./Xpm.KDE/RestartU.m.pm"
#include "./Xpm.KDE/ToStack.m.pm"
#include "./Xpm.KDE/Hint.m.pm"
#else
#ifdef GNOMESTYLE
#include "./Xpm.Gnome/DealCard.m.pm"
#include "./Xpm.Gnome/Undo.m.pm"
#include "./Xpm.Gnome/UndoU.m.pm"
#include "./Xpm.Gnome/Redo.m.pm"
#include "./Xpm.Gnome/RedoU.m.pm"
#include "./Xpm.Gnome/Replay.m.pm"
#include "./Xpm.Gnome/ReplayU.m.pm"
#include "./Xpm.Gnome/Restart.m.pm"
#include "./Xpm.Gnome/RestartU.m.pm"
#include "./Xpm.Gnome/ToStack.m.pm"
#include "./Xpm.Gnome/Hint.m.pm"
#else
#include "./Xpm/DealCard.m.pm"
#include "./Xpm/Undo.m.pm"
#include "./Xpm/UndoU.m.pm"
#include "./Xpm/Redo.m.pm"
#include "./Xpm/RedoU.m.pm"
#include "./Xpm/Replay.m.pm"
#include "./Xpm/ReplayU.m.pm"
#include "./Xpm/Restart.m.pm"
#include "./Xpm/RestartU.m.pm"
#include "./Xpm/ToStack.m.pm"
#include "./Xpm/Hint.m.pm"
#endif
#endif

#include "Xm-pixmap.h"

PixelResources_t	pixel_resources;

PixmapResources_t	pixmap_resources;


/************************************************************************/
/* FUNCTION : init_icon_pixmap                                          */
/* LONGNAME : create application icon pixmap                            */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-06-06                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
void	init_icon_pixmap (
	Widget	toplevel,
	Pixel	bg )
{
  Display	*display;

  XpmAttributes	xpm_attributes;

  display	= XtDisplay(toplevel);

  /* ensure that the pixmaps look OK even if the color map is nearly full */
  xpm_attributes.valuemask	= XpmCloseness;
  xpm_attributes.closeness	= 40000;

  xpm_attributes.numsymbols	= 1;
  xpm_attributes.valuemask	= XpmColorSymbols | xpm_attributes.valuemask;
  xpm_attributes.colorsymbols	=
			(XpmColorSymbol *)XtMalloc (sizeof (XpmColorSymbol) *
			xpm_attributes.numsymbols);

  xpm_attributes.colorsymbols[0].name	= "none";
  xpm_attributes.colorsymbols[0].value	= NULL;
  xpm_attributes.colorsymbols[0].pixel	= bg;

  if (XpmCreatePixmapFromData(display,
	DefaultRootWindow(display), Xpat2_icon_pm,
	&pixmap_resources.pixmapIcon, NULL, &xpm_attributes) != 0)
    pixmap_resources.pixmapIcon	= XmUNSPECIFIED_PIXMAP;

  XtFree ((char *) xpm_attributes.colorsymbols);
}


/************************************************************************/
/* FUNCTION : init_helpabout_pixmaps                                    */
/* LONGNAME : create icons for Help->About popup                        */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-06-06                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
void	init_helpabout_pixmaps (
	Widget	toplevel,
	Pixel	bg )
{
  Display	*display;

  XpmAttributes	xpm_attributes;

  display	= XtDisplay(toplevel);

  /* ensure that the pixmaps look OK even if the color map is nearly full */
  xpm_attributes.valuemask	= XpmCloseness;
  xpm_attributes.closeness	= 40000;

  xpm_attributes.numsymbols	= 1;
  xpm_attributes.valuemask	= XpmColorSymbols | xpm_attributes.valuemask;
  xpm_attributes.colorsymbols	=
			(XpmColorSymbol *)XtMalloc (sizeof (XpmColorSymbol) *
			xpm_attributes.numsymbols);

  xpm_attributes.colorsymbols[0].name	= "none";
  xpm_attributes.colorsymbols[0].value	= NULL;
  xpm_attributes.colorsymbols[0].pixel	= bg;


  if (XpmCreatePixmapFromData(display,
	DefaultRootWindow(display), Xpat2_l_pm,
	&pixmap_resources.pixmapAboutA, NULL, &xpm_attributes) != 0)
    pixmap_resources.pixmapAboutA	= XmUNSPECIFIED_PIXMAP;

  if (XpmCreatePixmapFromData(display,
	DefaultRootWindow(display), Xpat2B_l_pm,
	&pixmap_resources.pixmapAboutB, NULL, &xpm_attributes) != 0)
    pixmap_resources.pixmapAboutB	= XmUNSPECIFIED_PIXMAP;

  XtFree ((char *) xpm_attributes.colorsymbols);
}


/************************************************************************/
/* FUNCTION : init_toolbar_pixmaps                                      */
/* LONGNAME : create toolbar button pixmaps                             */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-06-06                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
void	init_toolbar_pixmaps (
	Widget	toplevel,
	Pixel	bg )
{
  Display	*display;

  XpmAttributes	xpm_attributes;

  display	= XtDisplay(toplevel);

  /* ensure that the pixmaps look OK even if the color map is nearly full */
  xpm_attributes.valuemask	= XpmCloseness;
  xpm_attributes.closeness	= 40000;

  xpm_attributes.numsymbols	= 1;
  xpm_attributes.valuemask	= XpmColorSymbols | xpm_attributes.valuemask;
  xpm_attributes.colorsymbols	=
			(XpmColorSymbol *)XtMalloc (sizeof (XpmColorSymbol) *
			xpm_attributes.numsymbols);

  xpm_attributes.colorsymbols[0].name	= "none";
  xpm_attributes.colorsymbols[0].value	= NULL;
  xpm_attributes.colorsymbols[0].pixel	= bg;

  if (XpmCreatePixmapFromData(display,
	DefaultRootWindow(display), DealCard_m_pm,
	&pixmap_resources.pixmapDealCard, NULL, &xpm_attributes) != 0)
    pixmap_resources.pixmapDealCard	= XmUNSPECIFIED_PIXMAP;

  if (XpmCreatePixmapFromData(display,
	DefaultRootWindow(display), Undo_m_pm,
	&pixmap_resources.pixmapUndo, NULL, &xpm_attributes) != 0)
    pixmap_resources.pixmapUndo	= XmUNSPECIFIED_PIXMAP;

  if (XpmCreatePixmapFromData(display,
	DefaultRootWindow(display), UndoU_m_pm,
	&pixmap_resources.pixmapUndoU, NULL, &xpm_attributes) != 0)
    pixmap_resources.pixmapUndoU	= XmUNSPECIFIED_PIXMAP;

  if (XpmCreatePixmapFromData(display,
	DefaultRootWindow(display), Redo_m_pm,
	&pixmap_resources.pixmapRedo, NULL, &xpm_attributes) != 0)
    pixmap_resources.pixmapRedo	= XmUNSPECIFIED_PIXMAP;

  if (XpmCreatePixmapFromData(display,
	DefaultRootWindow(display), RedoU_m_pm,
	&pixmap_resources.pixmapRedoU, NULL, &xpm_attributes) != 0)
    pixmap_resources.pixmapRedoU	= XmUNSPECIFIED_PIXMAP;

  if (XpmCreatePixmapFromData(display,
	DefaultRootWindow(display), Replay_m_pm,
	&pixmap_resources.pixmapReplay, NULL, &xpm_attributes) != 0)
    pixmap_resources.pixmapReplay	= XmUNSPECIFIED_PIXMAP;

  if (XpmCreatePixmapFromData(display,
	DefaultRootWindow(display), ReplayU_m_pm,
	&pixmap_resources.pixmapReplayU, NULL, &xpm_attributes) != 0)
    pixmap_resources.pixmapReplayU	= XmUNSPECIFIED_PIXMAP;

  if (XpmCreatePixmapFromData(display,
	DefaultRootWindow(display), Restart_m_pm,
	&pixmap_resources.pixmapRestart, NULL, &xpm_attributes) != 0)
    pixmap_resources.pixmapRestart	= XmUNSPECIFIED_PIXMAP;

  if (XpmCreatePixmapFromData(display,
	DefaultRootWindow(display), RestartU_m_pm,
	&pixmap_resources.pixmapRestartU, NULL, &xpm_attributes) != 0)
    pixmap_resources.pixmapRestartU	= XmUNSPECIFIED_PIXMAP;

  if (XpmCreatePixmapFromData(display,
	DefaultRootWindow(display), ToStack_m_pm,
	&pixmap_resources.pixmapToStack, NULL, &xpm_attributes) != 0)
    pixmap_resources.pixmapToStack	= XmUNSPECIFIED_PIXMAP;

  if (XpmCreatePixmapFromData(display,
	DefaultRootWindow(display), Hint_m_pm,
	&pixmap_resources.pixmapHint, NULL, &xpm_attributes) != 0)
    pixmap_resources.pixmapHint	= XmUNSPECIFIED_PIXMAP;

  XtFree ((char *) xpm_attributes.colorsymbols);
}
