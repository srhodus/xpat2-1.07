static Pixmap card_bitmaps[68];	/* these hold pixmaps of full depth */
                                /* we have room for 8 jokers */
static int numcards;		/* when reading external cardsets */
static int inset;

/* read a complete set of card bitmaps from a file */
static void read_bitmap(const char *file) {
    FILE *fp;
    int i, w, h, bpl, cardsize;
    char *card_bits;
    char fullname[200];
    struct {			 /* Note: all hi...-fields are currently 0 */
	char type;               /* 0 for cards without and 1 for cards with an frame 	*/
	char hitype;
	char num;                /* # of cards (without jokers) in file 		*/
	char hinum;
	char x;                  /* width of one card 					*/
	char hix;
	char y;                  /* height of one card on screen (size in file can differ) */
	char hiy;
	char rx;                 /* horizontal half axe of rounded corner 		*/
	char hirx;
	char ry;                 /* vertical half axe of rounded corner 		*/
	char hiry;
	char stddelta;           /* fraction of height for displaying 			*/
	char histddelta;
	char numjokers;          /* # of different joker cards 			*/
	char hinumjokers;
	char numcardbacks;       /* # of different cardbacks 				*/
	char hinumcardbacks;
	char fill[14];           /* reserved for future requirements 			*/
    } hdr;

    if (!strchr(file, '/') &&
	strlen(file) + strlen(LIBDIR) + 8 <= sizeof(fullname)) {
	sprintf(fullname, "%s/%s.cards", LIBDIR, file);
	file = fullname;
    }
    fp = fopen(file, "r");
    if (!fp || fread(&hdr, sizeof(hdr), 1, fp) != 1) {
	fprintf(stderr, "xpat2: Cannot read file %s\n", file);
	exit(EXIT_FAILURE);
    }
    /* check the number of cards in the header */
    if (hdr.num < 52 || hdr.num > 57) {
	fprintf(stderr, "xpat2: Bad value of numcards in file %s\n", file);
	exit(EXIT_FAILURE);
    }
    w = hdr.x; h = hdr.y; numcards = hdr.num;
    CARD_WIDTH = w;
    CARD_HEIGHT = h;
    ROUND_W = hdr.rx;           /* default radii of rounded corners */
    ROUND_H = hdr.ry;
    STD_DELTA = hdr.stddelta;
    bpl = (w + 7) >> 3;         /* bytes per line */
    if (!(card_bits = malloc(bpl * h * numcards))) {
	fprintf(stderr, "xpat2: Not enough memory for external cardset (file %s)\n",
		file);
	exit(EXIT_FAILURE);
    }

    /* read the card bitmaps */
    fread(card_bits, bpl * h * numcards, 1, fp);
    fclose(fp);

    /* hdr.type & 1 is the number of pixels omitted in the bitmap */
    cardsize = (h - 2 * (inset = (hdr.type & 1))) * bpl;

    /* turn data into bitmaps */
    for (i = 0; i < numcards; i++)	{
	card_bitmaps[i] = XCreateBitmapFromData(dpy, 
		RootWindow(dpy, screen), card_bits+i*cardsize, w-2*inset, h-2*inset);
    }
}

static void paint_external_card(int x, int y, int cardnumber) {
    if (cardnumber == CARDBACK)
	cardgc = backgc;
    else if (SUIT(cardnumber) == Spade || SUIT(cardnumber) == Club) {
	cardgc = graphic.is_color ? blackgc: whitegc;
    } else {
	cardgc = redgc;
    }

#ifndef NO_ROUND_CARDS
    if (ROUND_W) {
	XSetClipMask(dpy, cardgc, cardclipmap);
	XSetClipOrigin(dpy, cardgc, x, y);
	if (inset) {
	    XSetClipMask(dpy, blackgc, cardclipmap);
	    XSetClipOrigin(dpy, blackgc, x, y);
	}
    }
#endif

    XCopyPlane(dpy, card_bitmaps[cardnumber], table, cardgc, 0, 0, 
	CARD_WIDTH-2*inset, CARD_HEIGHT-2*inset, x+inset, y+inset, 1);

    if (inset) {	/* must draw border */
#ifndef NO_ROUND_CARDS
        if (ROUND_W)
  	    XmuDrawRoundedRectangle(dpy, table, blackgc, x, y, 
		CARD_WIDTH-1, CARD_HEIGHT-1, ROUND_W, ROUND_H);
	else
#endif
	    XDrawRectangle(dpy, table, blackgc, x, y, CARD_WIDTH-1, CARD_HEIGHT-1);
    }

    if (ROUND_W) {
	XSetClipMask(dpy, cardgc, None);
	if (inset)
	    XSetClipMask(dpy, blackgc, None);
    }
}
