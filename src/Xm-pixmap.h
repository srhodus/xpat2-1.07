/************************************************************************/
/* MODULE   : Xm-pixmap.h                                               */
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

#ifndef XM_PIXMAP_H
#define XM_PIXMAP_H

typedef struct	PixelResources_s
{ 
  Pixel		iconColor1;
  Pixel		iconColor2;
  Pixel		iconColor3;
  Pixel		iconColor4;
  Pixel		iconColor5;
  Pixel		iconColor6;
  Pixel		iconColor7;
  Pixel		iconColor8;
  Pixel		iconGrey1;
  Pixel		iconGrey2;
  Pixel		iconGrey3;
  Pixel		iconGrey4;
} PixelResources_t;


typedef struct	PixmapResources_s
{ 
  Pixmap	pixmapIcon;
  Pixmap	pixmapAboutA;
  Pixmap	pixmapAboutB;
  Pixmap	pixmapDealCard;
  Pixmap	pixmapUndo;
  Pixmap	pixmapUndoU;
  Pixmap	pixmapRedo;
  Pixmap	pixmapRedoU;
  Pixmap	pixmapReplay;
  Pixmap	pixmapReplayU;
  Pixmap	pixmapRestart;
  Pixmap	pixmapRestartU;
  Pixmap	pixmapToStack;
  Pixmap	pixmapHint;
} PixmapResources_t;


extern PixelResources_t		pixel_resources;

extern PixmapResources_t	pixmap_resources;


void	init_icon_pixmap (
	Widget	toplevel,
	Pixel	bg );

void	init_helpabout_pixmaps (
	Widget	toplevel,
	Pixel	bg );

void	init_toolbar_pixmaps (
	Widget	toplevel,
	Pixel	bg );

#endif /* XM_PIXMAP_H */
