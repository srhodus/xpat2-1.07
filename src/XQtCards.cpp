/* -*- C++ -*-	Time-stamp: <05 Nov 00 21:10:54 Michael Bischoff> */
/* Changes:
   changed CopyROP to Qt::CopyROP for Qt 2.x
   */
#include "XQtCards.h"
#include <stdio.h>
#include <stdlib.h>
#include <qcolor.h>
#include <qpainter.h>
#include <qbitmap.h>
#include <qpixmap.h>
#include "time.h"

#ifndef LIBDIR
#define LIBDIR "/usr/games/lib/xpat"
#endif

static const char *xpmfilename(const char *xpmdir, const char *file, const char *ext = 0) {
    static char buff[256];
    if (strlen(xpmdir) + strlen(file) + (ext ? strlen(ext) : 3) + 3 > sizeof(buff))
	exit(101);	/* avoid buffer overflow with unpredictable results */
    sprintf(buff, "%s/%s.%s", xpmdir, file, ext ? ext : "xpm");
    return buff;
}


/* with this module, cards are built the following way:
   1) If a complete card image does exist (filename: "(rank).(suit).xpm"),
      this image is read and used as the card pixmap. A rounded rectangle
      is drawn as a border. If the image does not exist, the card is
      constructed as follows.
   2) a white pixmap of full cardsize is created. The width and height
      are taken from the Cards.conf file (1st line) and default to 79x123.
   3) The default card background, taken from Background.xpm, is centered
      in the pixmap.
   4) Rank and small suit symbols are drawn into the pixmap.
   5) If a center picture does exist (filename "(rank).(suit).pic.xpm"),
      it is centered in the card. Otherwise, the card is filled with suit 
      symbols.
   6) A rounded rectangle is drawn as card border.

   For pictures (Jack to King), the procedure in 5) is slightly different,
   as the center pictures have to be mirrored and drawn twice.


   The cards may be configured by the Cards.conf file. This file is optional
   and may end after any line. The values not read from the file take their
   default values then.

   line | entries | comment, [default]
   -----+---------+--------------------------------------------------------
      1 |   2     | width, height of the cards	[79x123]
      2 |   2     | number of cardbacks, jokers [1, 1]
      3 |   1     | flags, bits are ored together, see below [0]
      4 |   2     | x, y distance of the border lines for pictures [6, 7]
      5 |   2     | Position of the medium-sized suit symbols for pictures
        |         |   (0 = omit them)			[11, computed]
      6 |   2     | x, y coordinate of the rank symbols [4,6]
      7 |   2     | x, y coordinate of the small suit symbol below the rank
        |         |   symbol				[3, computed]
      8 |   2     | xdelta, ydelta amount in pixels to shift large symbols
        |         |   closer together                   [0,0]
      9 |   3     | x0,x1,x2 the three possible x-coordinates of the large
        |         |   suit symbols			[computed]
     10 |   9     | y0..y8 the nine possible y-coordinates of the large
        |         |   suit symbols			[computed]
   -----+---------+---------------------------------------------------------
   Use of the lines 9 and 10 is intended for emergency cases only, as line
   8 should allow all configurations with equidistant suit symbols.
*/

/* for flags: */
#define TWORANKS	1	/* display two rank symbols? */
#define PRINT		2	/* print x(i), y(i) (Debugging) */
#define PIC_BG		4	/* use same background for pictures? */
#define NOCENTERLINE	8	/* place picture one lower and don't draw black center line */

#define RANKWIDTH	9
#define RANKHEIGHT	14
#define SUITSIZE0	41
#define SUITSIZE1	21
#define SUITSIZE2	15
#define SUITSIZE3	11
#define SUITOFF0	(0)
#define SUITOFF1	(SUITSIZE0)
#define SUITOFF2	(SUITSIZE0+SUITSIZE1)
#define SUITOFF3	(SUITSIZE0+SUITSIZE1+SUITSIZE2)

static struct cardconfig {
    int w, h, rx, ry;
    int flags;
    int ydelta;		/* odd integer! */
    int Ox, Oy;		/* distance of the border for pictures */
    int Rx, Ry;		/* position of the rank symbol */
    int Sx, Sy;		/* position of the small suit symbol */
    int Mx, My;		/* position of the medium suit symbol */
    int x0, x1, x2;	/* x-positions of the large suit symbols */
    int y0, y1, y2, y3, y4, y5, y6, y7, y8;	/* y-positions */
    int numbacks, numjokers;
    int pile_dx, pile_dy, slot_dx, slot_dy;
} cc;

#define CARD_WIDTH	(cc.w)
#define CARD_HEIGHT	(cc.h)

static void read_cardconfig(const char *filename) {
    FILE *fp;
    int tmp[9];
    cc.pile_dx =  4;	/* to be added to Cards.conf later... */
    cc.pile_dy =  4;
    cc.slot_dx =  0;
    cc.slot_dy = 28;
    if (!(fp = fopen(filename, "r"))) {
	fprintf(stderr, "xpat2: WARNING, cannot load configuration file %s\n", filename);
	goto stdconfig;
    }
    if (fscanf(fp, "%d %d", &CARD_WIDTH, &CARD_HEIGHT) != 2 ||
	CARD_WIDTH < 48 || CARD_WIDTH > 123 ||
	CARD_HEIGHT < 64 || CARD_HEIGHT > 200) {
	fclose(fp);
	fp = NULL;
	goto stdconfig;
    } else
	goto havesize;

 stdconfig:
    CARD_WIDTH = 79;
    CARD_HEIGHT = 123;
 havesize:
    cc.rx = cc.ry = CARD_WIDTH / 8;	/* to be added to Cards.conf later... */
    cc.numbacks = cc.numjokers = 1;
    cc.ydelta = (((CARD_HEIGHT - 2 - 4 * SUITSIZE1) / 7) | 1);

    cc.x0 = (CARD_WIDTH - 1 * SUITSIZE1) / 2 - 2 * CARD_WIDTH / 9 + 1;
    cc.x1 = (CARD_WIDTH - 1 * SUITSIZE1) / 2;
    cc.x2 = (CARD_WIDTH - 1 * SUITSIZE1) / 2 + 2 * CARD_WIDTH / 9 - 1;

    cc.y0 = (CARD_HEIGHT - 3 * cc.ydelta - 4 * SUITSIZE1) / 2;
    cc.y1 = (CARD_HEIGHT - 2 * cc.ydelta - 3 * SUITSIZE1) / 2;
    cc.y2 = (CARD_HEIGHT - 1 * cc.ydelta - 2 * SUITSIZE1) / 2;
    cc.y3 = (CARD_HEIGHT - 0 * cc.ydelta - 1 * SUITSIZE1) / 2;
    cc.y4 = (CARD_HEIGHT + 1 * cc.ydelta - 0 * SUITSIZE1) / 2;
    cc.y5 = (CARD_HEIGHT + 2 * cc.ydelta + 1 * SUITSIZE1) / 2;
    cc.y6 = (CARD_HEIGHT + 3 * cc.ydelta + 2 * SUITSIZE1) / 2;
    cc.y7 = (cc.y0 + cc.y3) / 2;
    cc.y8 = (cc.y6 + cc.y3) / 2;

    cc.flags = 0;
    cc.Mx = 11;
    cc.My = cc.y0 + 3;
    cc.Ox = 6;
    cc.Oy = 7;
    cc.Rx = 4;
    cc.Ry = 6;
    cc.Sx = 3;
    cc.Sy = cc.y0 + SUITSIZE1 - SUITSIZE3;
    if (fp) {	/* Cards.Conf does exist */
	/* possibility to override the defaults */
	if (fscanf(fp, "%d %d", tmp, tmp+1) == 2)
	    cc.numbacks = tmp[0], cc.numjokers = tmp[1];
	if (cc.numbacks <= 0 || cc.numbacks > 99)
	    cc.numbacks = 1;
	if (fscanf(fp, "%d", tmp) == 1)
	    cc.flags = tmp[0];
	if (fscanf(fp, "%d %d", tmp, tmp+1) == 2)
	    cc.Ox = tmp[0],	cc.Oy = tmp[1];
	if (fscanf(fp, "%d %d", tmp, tmp+1) == 2)
	    cc.Mx = tmp[0],	cc.My = tmp[1];
	if (fscanf(fp, "%d %d", tmp, tmp+1) == 2)
	    cc.Rx = tmp[0],	cc.Ry = tmp[1];
	if (fscanf(fp, "%d %d", tmp, tmp+1) == 2)
	    cc.Sx = tmp[0],	cc.Sy = tmp[1];
	if (fscanf(fp, "%d %d", tmp, tmp+1) == 2) {	/* xdelta and ydelta */
	    cc.x0 += tmp[0], cc.x2 -= tmp[0],
	    cc.y0 += 3 * tmp[1];
	    cc.y1 += 2 * tmp[1];
	    cc.y2 += 1 * tmp[1];
	    cc.y4 -= 1 * tmp[1];
	    cc.y5 -= 2 * tmp[1];
	    cc.y6 -= 3 * tmp[1];
	    tmp[1] = tmp[1] * 3 / 2;
	    cc.y7 += tmp[1];
	    cc.y8 -= tmp[1];
	}
	if (fscanf(fp, "%d %d %d", tmp, tmp+1, tmp+2) == 3)
	    cc.x0 = tmp[0],	cc.x1 = tmp[1], cc.x2 = tmp[2];
	if (fscanf(fp, "%d %d %d %d %d %d %d %d %d", tmp, tmp+1, tmp+2, tmp+3,
		   tmp+4, tmp+5, tmp+6, tmp+7, tmp+8) == 9)
	    cc.y0 = tmp[0],	cc.y1 = tmp[1], cc.y2 = tmp[2],
	    cc.y3 = tmp[3],	cc.y4 = tmp[4], cc.y5 = tmp[5],
	    cc.y6 = tmp[6],	cc.y7 = tmp[7], cc.y8 = tmp[8];
	fclose(fp);
    }
    if (cc.flags & PRINT)
	printf("y = %d %d %d  %d %d %d  %d %d %d, x = %d %d %d\n",
	   cc.y0, cc.y1, cc.y2,
	   cc.y3, cc.y4, cc.y5,
	   cc.y6, cc.y7, cc.y8,
	   cc.x0, cc.x1, cc.x2);
    return;
}


static const unsigned char suitflags[] = {  /* 25 => 03 for different 8 */
    0x80, 0x08, 0x88, 0x01, 0x81, 0x05, 0x45, 0x25, 0x83, 0x13, 0, 0, 0, 0 };

static const char
  n_ace[] = "Ace", n_deuce[] = "Deuce", n_three[] = "Three",
  n_four[] = "Four", n_five[] = "Five", n_six[] = "Six", n_seven[] = "Seven",
  n_eight[] = "Eight", n_nine[] = "Nine", n_ten[] = "Ten", n_jack[] = "Jack",
  n_queen[] = "Queen", n_king[] = "King", n_joker[] = "Joker",
  n_diamonds[] = "Diamonds", n_hearts[] = "Hearts", n_spades[] = "Spades",
  n_clubs[] = "Clubs";

static const char *US_rank_name[] = {
    n_ace, n_deuce, n_three, n_four, n_five, n_six, n_seven, n_eight, n_nine,
    n_ten, n_jack, n_queen, n_king
};
static const char *US_suit_name[] = {
    n_clubs, n_spades, n_hearts, n_diamonds
};

static void MirrorCard(QPixmap *d, QPainter *p) {
    p->rotate(180.0);
    p->drawPixmap(1-CARD_WIDTH, 1-CARD_HEIGHT, *d, 0, 0,
		     CARD_WIDTH, CARD_HEIGHT/2);
    p->rotate(0.0);
}

/* load a cardback. 0 = fallback cardback with few colors, -1 = random one */
QPixmap *XQtCards::load_cardback(int num) {
    QPixmap *cb;
    int rxp = 0, ryp = 0;
    if (rx && ry) {
	rxp = 198 * rx / w;
	ryp = 198 * ry / h;
    }
    char filename[12];
    if (num > numcardbacks)	/* this can happen when switching images during the game */
	num = -1;	/* select a new one */
    if (num < 0)
	num = 1 + (int)((time(0) & 0x7fff) % numcardbacks);
    sprintf(filename, "Cardback%d", num);
    cb = new QPixmap(xpmfilename(directory, filename));
    if (!cb) {
	fprintf(stderr, "loading the cardback pixmap %s FAILED!\n", filename);
	// fallback to empty pixmap
	cb = new QPixmap(w, h);
    }
    currentcardback = num;

    QPainter paint;
    paint.begin(cb);
    paint.drawRoundRect(0, 0, w, h, rxp, ryp);
    paint.end();
    cb->setMask(*clipmap);
    return cb;
}

void XQtCards::set_cardback(int num = 0) {
    delete pm_cardback;
    if (num > numcardbacks || num < 1)
	num = -1;
    pm_cardback = load_cardback(num);
}


/* overlay an xpm file onto the current pixmap */
/* if two is set, the image is just half a card */
static int overlap_picture(const char *name, int two, QPixmap *d, QPainter *paint) {
    QPixmap *p;
    int x, y, w, h;

    p = new QPixmap(name);
    if (!p)	/* file does not exist or cannot be loaded */
	return 0;
    w = p->width();
    h = p->height();
    if (!w || !h) {
	delete p;
	return 0;
    }

    if (two == 2 && 2 * h > CARD_HEIGHT) {
	two = 0;	/* just a single picture */
	MirrorCard(d, paint);
    }
    if (two) {
	x = (CARD_WIDTH-w) / 2;
	y = CARD_HEIGHT/2 - h;
	if (cc.flags & NOCENTERLINE)
	    ++y;
    } else {
	x = (CARD_WIDTH-w) / 2;
	y = (CARD_HEIGHT-h) / 2;
    }
    bitBlt(d, x, y, p, 0, 0, w, h, Qt::CopyROP, FALSE);
    delete p;

    if (two == 2)
	MirrorCard(d, paint);
    return 1;
}



XQtCards::XQtCards(const char *xpmdir) {
    if (!xpmdir)
	xpmdir = LIBDIR "/default";	// default xpm directory
    local_constructor(xpmdir);
}

void XQtCards::local_constructor(const char *xpmdir) {
    int rxp = 0, ryp = 0;
    int bxo = 0, byo = 0, bw = 0, bh = 0;	// background offsets and sizes
    int bigw = 0, bigh = 0;
    char name[32];

    directory = new char [strlen(xpmdir) + 1];
    strcpy(directory, xpmdir);

    read_cardconfig(xpmfilename(directory, "Cards", "conf"));
    w = cc.w;
    h = cc.h;
    rx = cc.rx;
    ry = cc.ry;
    pile_dx = cc.pile_dx;
    pile_dy = cc.pile_dy;
    slot_dx = cc.slot_dx;
    slot_dy = cc.slot_dy;
    numcardbacks = cc.numbacks;

    // sanity checks:
    if (rx > w/2)
	rx = w/2;
    if (ry > h/2)
	ry = h/2;

    if (rx && ry) {
	rxp = 198 * rx / w;
	ryp = 198 * ry / h;
	clipmap = new QBitmap(w, h, TRUE);
	QPainter clippaint(clipmap);
	clippaint.setPen(color1);
	clippaint.setBrush(color1);
	clippaint.drawRoundRect(0, 0, w, h, rxp, ryp);

	clipempty = new QBitmap(w, h, TRUE);
	QPainter clippaintempty(clipempty);
	clippaintempty.setPen(color1);
	clippaintempty.drawRoundRect(0, 0, w, h, rxp, ryp);
    }
    QPixmap Ranks     (xpmfilename(directory, "Ranks"));
    QPixmap Suits     (xpmfilename(directory, "Suits"));
    QPixmap Pictures  (xpmfilename(directory, "Pictures"));
    QPixmap Background(xpmfilename(directory, "Background"));


    QPainter paint;
    pm_empty = new QPixmap(w, h);
    paint.begin(pm_empty);
    paint.setBrush(black);
    paint.fillRect(0, 0, w, h, black);
    paint.end();
    pm_empty->setMask(*clipempty);

    bigw = Pictures.width() / 4;
    bigh = Pictures.height() / 3;
    bw = Background.width();
    bh = Background.height();
    if (bw <= w)
	bxo = (w - bw) / 2;
    else
	bw = w;
    if (bh <= h)
	byo = (h - bh) / 2;
    else
	bh = h;

//	printf("bw = %d, bh = %d\n", bw, bh);

    for (int i = 0; i < 59; ++i) {
	int x, y, suit, rank;
	suit = i & 3;
	rank = i >> 2;
	pm_cards[i] = new QPixmap(w, h);
//	fprintf(stderr, "Begin (%d, %p) ", i, pm_cards[i]);
	paint.begin(pm_cards[i]);
	paint.fillRect(0, 0, w, h, white);
	if (bw && bh && (((cc.flags & PIC_BG) || !(rank >= 10 && rank <= 12)))) {
	    /* move background */
	    bitBlt(pm_cards[i], bxo, byo, &Background,
		0, 0, bw, bh, Qt::CopyROP, FALSE);
	}
	paint.drawRoundRect(0, 0, w, h, rxp, ryp);
	if (i < 52) {
	    if (cc.Rx) {
		x = 3 * (suit/2) * RANKWIDTH + (rank / 5) * RANKWIDTH;
	        y = (rank % 5) * RANKHEIGHT;
        	// if (p_rank.clip) XSetClipOrigin(dpy, rankgc, cc.Rx-x, cc.Ry-y);
	        bitBlt(pm_cards[i], cc.Rx, cc.Ry, &Ranks, x, y,
			RANKWIDTH, RANKHEIGHT, Qt::CopyROP, FALSE);
	        if (cc.flags & TWORANKS)
		    bitBlt(pm_cards[i], CARD_WIDTH-RANKWIDTH-cc.Rx, cc.Ry, &Ranks, x, y,
                        RANKWIDTH, RANKHEIGHT, Qt::CopyROP, FALSE);
	    }
	    if (cc.Sx) {
        	/* Draw the upper small suit symbol(s). */
	        x = cc.Sx;
	        y = cc.Sy;
        	bitBlt(pm_cards[i], x, y, &Suits, suit * SUITSIZE3, SUITOFF3,
		       SUITSIZE3, SUITSIZE3,  Qt::CopyROP, FALSE);
	        if (cc.flags & TWORANKS)
		    bitBlt(pm_cards[i], CARD_WIDTH-SUITSIZE3 - x, y, &Suits, suit * SUITSIZE3, SUITOFF3,
			   SUITSIZE3, SUITSIZE3,  Qt::CopyROP, FALSE);
  	    }
	    if (rank >= 10) {
		/* picture */
		if (cc.Mx > 0) {
		    bitBlt(pm_cards[i], SUITSIZE2 * suit, SUITOFF2, &Suits, SUITSIZE2, SUITSIZE2,
			   cc.Mx, cc.My, Qt::CopyROP, FALSE);
		}
		/* horizontal line in the midst of the card: */
		if (!(cc.flags & NOCENTERLINE))
		    paint.drawLine(cc.Ox, CARD_HEIGHT/2, CARD_WIDTH-1-cc.Ox, CARD_HEIGHT/2);
		if (cc.Oy)
		    paint.drawLine(4 + RANKWIDTH + 1, cc.Oy, CARD_WIDTH - 1 - 4 - RANKWIDTH - 1, cc.Oy);
		if (cc.Ox) {
		    paint.drawLine(cc.Ox,              cc.y7+1, cc.Ox,              CARD_HEIGHT/2);
		    paint.drawLine(CARD_WIDTH-1-cc.Ox, cc.y7+1, CARD_WIDTH-1-cc.Ox, CARD_HEIGHT/2);
		}

		{   /* load a card image */
		    if (bigw && bigh) {
			/* have it! */
			x = (CARD_WIDTH-bigw) / 2;
			y = CARD_HEIGHT/2 - bigh;
			if (cc.flags & NOCENTERLINE)
			    ++y;
			bitBlt(pm_cards[i], x, y, &Pictures, bigw*suit, bigh*(rank-10), bigw, bigh, Qt::CopyROP, FALSE);
		    } else {
			sprintf(name, "%s.%s.pic", US_rank_name[rank], US_suit_name[suit]);
			if (overlap_picture(xpmfilename(directory, name),
					    2, pm_cards[i], &paint))
			    goto picture_done;	 /* has done the mirroring  */
		    }
		}
#if 1
		MirrorCard(pm_cards[i], &paint);
#else
		paint.rotate(180.0);
		paint.drawPixmap(1-CARD_WIDTH, 1-CARD_HEIGHT, *(pm_cards[i]),
				  0, 0, CARD_WIDTH, CARD_HEIGHT/2);
		paint.rotate(0.0);
#endif
	    } /* rank >= 10 */ else {	/* ace to ten */
		int cx, cy, dl;
#if 0 // not required, mirroring
		if (cc.Rx) {
		    /* Draw the lower rank symbol(s). */
		    x = (8 + 3 * (suit/2) - (rank / 5)) * RANKWIDTH;
		    y = (4 - rank % 5) * RANKHEIGHT;
		    dl = CARD_WIDTH-RANKWIDTH;
		    cx = dl-cc.Rx;
		    cy = CARD_HEIGHT-cc.Ry-RANKHEIGHT;
		    bitBlt(pm_cards[i], cx, cy, &Ranks, x, y, RANKWIDTH, RANKHEIGHT, Qt::CopyROP, FALSE);
		    if (cc.flags & TWORANKS) {
			cx = dl - cx;
			bitBlt(pm_cards[i], cx, cy, &Ranks, x, y, RANKWIDTH, RANKHEIGHT, Qt::CopyROP, FALSE);
		    }
		}
		if (cc.Sx) {
		    /* Draw the lower small suit symbol(s). */
		    x = (suit+4) * SUITSIZE3;
		    y = SUITOFF3;
		    dl = CARD_WIDTH-SUITSIZE3;
		    cx = dl-cc.Sx;
		    cy = CARD_HEIGHT-cc.Sy-SUITSIZE3;
		    bitBlt(pm_cards[i], cx, cy, &Suits, x, y,
			   SUITSIZE3, SUITSIZE3,  Qt::CopyROP, FALSE);
		    if (cc.flags & TWORANKS) {
			cx = dl - cx;
			bitBlt(pm_cards[i], cx, cy, &Suits, x, y,
			       SUITSIZE3, SUITSIZE3,  Qt::CopyROP, FALSE);
		    }
		}
#endif
		/* load picture instead of standard symbols? */
		sprintf(name, "%s.%s.pic", US_rank_name[rank], US_suit_name[suit]);
		if (overlap_picture(xpmfilename(directory, name),
				    0, pm_cards[i], &paint))
		    goto picture_done;
		/* OK, draw the suit symbols */
		/* first, all symbols which are not mirrored */

#define PAINT_AT(xx, yy) {                                      \
	       bitBlt(pm_cards[i], xx, yy, &Suits, x, SUITSIZE0, SUITSIZE1, SUITSIZE1, Qt::CopyROP, FALSE); \
								    }


		x = SUITSIZE1 * suit;
		if (suitflags[rank] & 0x01) {
		    PAINT_AT(cc.x0, cc.y0);
		    PAINT_AT(cc.x2, cc.y0);
		}
		if (suitflags[rank] & 0x02) {
		    PAINT_AT(cc.x0, cc.y2);
		    PAINT_AT(cc.x2, cc.y2);
		}
		if (suitflags[rank] & 0x08) {
		    PAINT_AT(cc.x1, cc.y0);
		}
		if (suitflags[rank] & 0x10) {
		    PAINT_AT(cc.x1, cc.y1);
		}
		if (suitflags[rank] & 0x20) {
		    PAINT_AT(cc.x1, cc.y7);
		}
#if 1
		MirrorCard(pm_cards[i], &paint);
#else
		paint.rotate(180.0);
		paint.drawPixmap(1-CARD_WIDTH, 1-CARD_HEIGHT, *(pm_cards[i]),
				 0, 0,
				 CARD_WIDTH, CARD_HEIGHT/2);
#endif

		if (suitflags[rank] & 0x04) {
		    PAINT_AT(cc.x0, cc.y3);
		    PAINT_AT(cc.x2, cc.y3);
		}
		if (suitflags[rank] & 0x40) {
		    PAINT_AT(cc.x1, cc.y7);
		}
		if (suitflags[rank] & 0x80) {
		    PAINT_AT(cc.x1, cc.y3);
		}
	    } /* ace to ten */
	} else {
	    if (i < 56) {	// is a suit symbol
		/* load picture instead of standard symbols? */
		sprintf(name, "Empty.%s", US_suit_name[suit]);
		if (overlap_picture(xpmfilename(directory, name),
				    0, pm_cards[i], &paint))
		    goto picture_done;
		x = (CARD_WIDTH-SUITSIZE0)/2;
		y = (CARD_HEIGHT-SUITSIZE0)/2;
		bitBlt(pm_cards[i], x, y, &Suits, SUITSIZE0 * suit, 0,
		       SUITSIZE0, SUITSIZE0, Qt::CopyROP, FALSE);

	    }
	}
    picture_done:
	paint.end();
//	fprintf(stderr, "endd(%p)\n", pm_cards[i]);
 	pm_cards[i]->setMask(*clipmap);
    }

    pm_cardback = load_cardback(-1);	/* load a random cardback */
    if (!pm_cardback)
	pm_cardback = load_cardback(0);	/* load the fallback cardback */
}

void XQtCards::local_destructor() {
    for (int i = 0; i < 59; ++i) {
	delete pm_cards[i];
    }
    delete pm_cardback;
    delete pm_empty;
    delete clipmap;
    delete clipempty;
    delete [] directory;
}
XQtCards::~XQtCards() {
    local_destructor();
    delete directory;
}
void XQtCards::reloadGraphics(const char *xpmdir) {
    local_destructor();
    local_constructor(xpmdir);
    emit cards_changed();
}
