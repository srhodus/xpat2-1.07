/* The static data describing the geometry of the
   Tableau and the cards */

struct pilegeometry {
    int x, y;			/* position on the Tableau widget	*/
    int w, h;			/* size of the pile, at least card size	*/
    int ox, oy;			/* offset of lowest card in this pile	*/
    int dx, dy;			/* for slots: std. replacement		*/
    int cdx, cdy;		/* for slots: current replacement
				   (may be smaller due to many cards)   */
};

struct Coord {			/* for storing arrow coordinates */
    int x;
    int y;
};
#define ARROW_MAX_COORDINATES	10	/* max number of coords for arrow */
#define UPDOWN_MINDIST	(geo.ya_h + geo.ah + 1)

struct geometry {
    int w, h;			/* width and height of the tableau	*/
    int dx, dy;			/* gaps between the cards		*/
    int cw, ch;			/* width and height of a card		*/
    int rx, ry;			/* size of card roundness		*/
    int ya_w, ya_h, xa_w, xa_h;	/* arrow head dimension, set by init 	*/
    int aw, ah;			/* width and height of an arrow 	*/
    struct pilegeometry pg[MAXPILES];	/* where the piles are and how large */
    int lsw, lsh;		/* largest slot width, height		*/
    int preferred_width, preferred_height;	/* w, h for this layout type */
    int min_width, min_height;	/* minimal w, h for these rules		*/
    int w_width, w_height;      /* if using ScrollView: size of pane    */
};
extern struct geometry geo;
#define NOT_DISPLAYED(p)     ((p)->x == -1 && (p)->y == -1)

/* BOTTOM_INC is the amout a slot is extended below the end of the tableau */
/* define BOTTOM_INC = 0 if you do not want this */

#define RIGHT_INC		(geo.dx + geo.cw * 2 / 3)
#define BOTTOM_INC		(geo.dy + geo.ch * 2 / 3)

/* layout types for Spider, Gypsy are 0..7 */
/* for new rules, just add any value */
#define GEN_BIG_LAYOUT_NO_DECK		0
#define GEN_BIG_LAYOUT_WITH_DECK	1
#define GEN_BIG_LAYOUT_WITH_DECK	1
#define GEN_BIG_STAR_LAYOUT		3

#define FREECELL_MAGIC		0x220
#define DELIGHT_MAGIC		0x260
#define MONTECARLO_MAGIC	0x320
#define MIDNIGHTOIL_MAGIC	0x370
#define MICHAELS_MAGIC		0x3c0
#define ROYAL_MAGIC		0x3e0
#define BAKERS_MAGIC		0x400
#define CANFIELD_MAGIC		0x420
#define OONSOO_MAGIC		0x440
#define BLUEMOON_MAGIC		0x460

/* typedef enum { arrow_x, arrow_y, arrow_z, mark_s } BitBlt_type; */

#define BITBLT_ARROW_X	0
#define BITBLT_ARROW_Y	1
#define BITBLT_ARROW_Z	2
#define BITBLT_MARK	3
void bitblt_arrow(int type, int save, int x, int y, int w, int h);
void draw_arrow_polygon(int npoints, const struct Coord *poly);
