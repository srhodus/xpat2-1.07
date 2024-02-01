
static void usage(const char *arg) {
    fprintf(stderr, "usage: xpat2 [options] [<seed> or <savedgame>]\n");
    fprintf(stderr, "valid options are:\n");
#ifdef useXlib
    fprintf(stderr, "-display <display>      set display\n");
    fprintf(stderr, "-geometry <geometry>    set initial geometry\n");
#ifdef LOADCARDS
    fprintf(stderr, "-cards <cardset>        set cardset to external file\n");
#endif
#endif
    fprintf(stderr, "-xpmdir <directory>     directory to load xpm files from\n");
    fprintf(stderr, "-xpmcls <value>         allow colours of this closeness (0 to 65535)\n");
    fprintf(stderr, "-sound <0/1>            enables/disables sound\n");

    fprintf(stderr, "-tb <backgroundcolor>   set background color of tableau\n");
    fprintf(stderr, "-cb <cardbackcolor>     set cardback color\n");
    fprintf(stderr, "-markcolor <markcolor>  set color of card marks\n");
    fprintf(stderr, "-markwidth <markwidth>  set width of card marks\n");
    fprintf(stderr, "-bfont <fontname>       set font for buttons\n");
    fprintf(stderr, "-sfont <fontname>       set font for status line\n");
    fprintf(stderr, "-gapx, -gapy            set space between cards (0 to 20)\n");
    fprintf(stderr, "\ngame customization:\n");
    fprintf(stderr, "-rules <ruleset>        set rules to HM or Spider or Stairs\n");
    fprintf(stderr, "-slots <slots>          set number of slots (2 to 60)\n");
    fprintf(stderr, "-decks <decks>          set number of decks (1 to 9)\n");
    fprintf(stderr, "-tmps <tmps>            set number of tmps (1 to 9)\n");
    fprintf(stderr, "-faceup <faceup>        set initial deal parameter (0 to 20)\n");
    fprintf(stderr, "-facedown <facedown>    set initial deal parameter (0 to 20)\n");
    fprintf(stderr, "-jokers <jokers>        set number of jokers (do not use, it's too easy)\n");
    fprintf(stderr, "-flips <flips>          limit number of flips (0 to 99)\n");
    fprintf(stderr, "-relaxed 0|1            choose easy or hard variant\n");
    fprintf(stderr, "-turn <turn>            set number of cards to turn (1 to 9)\n");
    fprintf(stderr, "-rotations <num>        set maximum number of slot rotations (0 to 9)\n");
    fprintf(stderr, "-p{0,1,2,3} <param>     set various rule parameters\n");
#if 0	/* for insiders only */
    fprintf(stderr, "-autolayout <0/1>       0: to avoid automatic re-layout at resize time\n");
    fprintf(stderr, "-mem <0/1>              0: do not store card images at full depth internally\n");
    fprintf(stderr, "-by <buttongap>         set button gap y size\n");
    fprintf(stderr, "-bx <buttongap>         set button gap x size\n");
    fprintf(stderr, "-cround <cornersize>    set size of round card corners (0 to 20)\n");
    fprintf(stderr, "-bround <cornersize>    set size of round button corners (0 to 20)\n");
#endif
    if (arg)
 	fprintf(stderr,"argument \"%s\" caused this message\n", arg);
    exit(EXIT_FAILURE);
}
