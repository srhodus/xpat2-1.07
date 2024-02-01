/* Time-stamp: <05 Nov 00 21:11:43 Michael Bischoff> */
/* arrays for commandline option handling for Qt and Xlib */

/* enum { String, Number, Bool } argtype; */
#define String 0
#define Number 1
#define Self   2
    int i;
    long seed = -1L;
    const char *restoregame = NULL;
    static const char *display = NULL, *cmdname;

    /* these must be static, since their address is taken */
    static int Xslots, faceup, facedown, decks, p0, p1, p2, p3; /* rules customization */
    static int linewidth, cround, bround, gapx, gapy, bx, by, autolayout, mem;
    static int tmps, arrw, arrh, jokers, sound = 1, xpmcls = 0;
    static const char *geometry, *ruleset, *cbcolor, *bkcolor = "DarkKhaki";
    static const char *buttonfont, *statusfont, *cardset = NULL, *markcolor, *xpmdir;
    static const char *arrowcolor;

    static struct option_struct {
	const char *option;
	const char *resource;
	const char *value;
	void *where;
	int type;
	int minval;       /* only for Number */
	int maxval;       /* only for Number */
	const char *cmdarg;
    } options[] = {
    /* first option must be -rules */
    { "-rules",	    "Rules",	     "Gypsy",     &ruleset,   String },
#ifdef LOADCARDS
    { "-cards",     "Cards",         NULL,        &cardset,   String },
#endif
    { "-xpmdir",    "Xpmdir",        NULL,        &xpmdir,    String },
    { "-xpmcls",    "Xpmcls",        "0",	  &xpmcls,    Number,  0, 65535 },
    { "-autolayout","AutoLayout",    "1",         &autolayout,Number,  0,  1 },
    { "-mem",       "Mem",           "1",         &mem,       Number,  0,  1 },
    { "-slots",     "Slots",	     NULL,        &Xslots,    Number, -1, MAXPILES },
    { "-flips",     "Flips",	     NULL,        &p1,	      Number, -1,999 },
    { "-turn",      "Turn",	     NULL,        &p2,        Number, -1,  9 },
    { "-relaxed",   "relaxed",	     NULL,        &p0,        Number, -1,  9 },
    { "-flips",     "flips",	     NULL,        &p1,        Number, -1, 99 },
    { "-turn",      "turn",	     NULL,        &p2,        Number, -1,  9 },
    { "-rotations", "rotations",     NULL,        &p3,        Number, -1,  9 },
    { "-decks",     "Decks",         NULL,        &decks,     Number, -1,  9 },
    { "-tmps",      "Tmps",          NULL,        &tmps,      Number, -1, 16 },
    { "-faceup",    "Faceup",        NULL,        &faceup,    Number, -1, 16 },
    { "-facedown",  "Facedown",      NULL,        &facedown,  Number, -1, 16 },
    { "-jokers",    "Jokers", 	     NULL,        &jokers,    Number, -1, 16 },
    { "-cround",    "CardRound",     NULL,        &cround,    Number, -1, 99 },
    { "-bround",    "ButtonRound",   "4",         &bround,    Number,  0, 20 },
    { "-sound",     "Sound",         "1",         &sound,     Number,  0,  1 },
    { "-bx",        "ButtonGapX",    "4",         &bx,        Number,  0, 99 },
    { "-by",        "ButtonGapY",    "4",         &by,        Number,  0, 99 },
    { "-aw",        "ArrowWidth",    NULL,        &arrw,      Number, -1, 30 },
    { "-ah",        "ArrowHeight",   NULL,        &arrh,      Number, -1, 30 },
    { "-gapx",      "GapX",          "4",         &gapx,      Number,  0, 99 },
    { "-gapy",      "GapY",          "4",         &gapy,      Number,  0, 99 },
    { "-rng",       "Rng",	     "1",	  &rng,       Number,  0,  1 },
    { "-cb",        "CardbackColor", "SlateGrey", &cbcolor,   String },
    { "-tb",   	    "TableColor",    "DarkKhaki", &bkcolor,   String },
    { "-markcolor", "MarkColor",     NULL,        &markcolor, String },
    { "-markwidth", "MarkWidth",     "999",       &linewidth, Number,  1,999 },
    { "-arrowcolor","ArrowColor",    "Gold",      &arrowcolor,String },
    { "-bfont",     "ButtonFont",    NULL,        &buttonfont,String },
    { "-sfont",     "StatusFont",    "fixed",     &statusfont,String }
#ifdef useXlib
    ,
    { "-geometry",  "Geometry",      NULL,        &geometry,  String },
    { "-display",   NULL,            NULL,        &display,   String }
#endif
};
#define NUMOPTIONS      (sizeof(options) / sizeof(options[0]) - 1)

    for (i = 0; i <= NUMOPTIONS; ++i)
        options[i].cmdarg = NULL;

    if (!(cmdname = strrchr(argv[0], '/')))
	cmdname = argv[0];
    else
	++cmdname;
    if (strncmp(cmdname, "xpat2", 5))
	options[0].cmdarg = cmdname;

    for (i = 1; i < argc - 1; ++i) {    /* merge command line options */
	int j;
	if (*argv[i] != '-')
	    break;
	for (j = 0; j <= NUMOPTIONS; ++j) {
	    if (!strcmp(argv[i], options[j].option)) {
		options[j].cmdarg = options[j].type == Self ? "1" : argv[++i];
		break;
	    }
        }
        if (j > NUMOPTIONS)
	    usage(argv[i]);
    }
    if (i < argc) {		/* seed or savegame left */
	if (i != argc - 1)
	    usage(argv[i]);
	if (isdigit(*argv[i])) {
	    seed = atol(argv[i]);
	    if (seed < 0L || seed >= 1000000000L)
		usage(argv[i]);
	} else
	    if (*argv[i] != '-')
		restoregame = loadfilename = argv[i];
	    else
		usage(argv[i]);
    }
    display = options[NUMOPTIONS].cmdarg;
