/************************************************************************/
/* MODULE   : Xm-tbflatb.c                                              */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/*          : Flat toolbar buttons                                      */
/* AUTHOR   : Christian Anzenberger                                     */
/* CONTACT  : christian.anzenberger@siemens.at                          */
/* CREATED  : 1999-05-09                                                */
/* NOTES    : see README.motif for details on release                   */
/*          : see COPYRIGHT.motif for details on copyright              */
/************************************************************************/
/* History of Change:                                                   */
/*-------+--------+----------------------------------------------+------*/
/*Version|  Date  | Changes                                      |Author*/
/*-------+--------+----------------------------------------------+------*/
/* 0.1   |19990509| Initial creation for xpat2-1.04              | ac   */
/************************************************************************/

#ifdef FLAT_BUTTONS
/* No real need for this ifdef. Module is in-/excluded in Makefile,     */
/* because Sun WorkShop C does not like empty translation units.        */


#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#define	BUTTON_MASK (	Button1Mask | \
			Button2Mask | \
			Button3Mask | \
			Button4Mask | \
			Button5Mask )


static Widget		pressed_button = 0;	/* currently unflatd. button */
static Dimension	shadow_thickness;
static Dimension	margin_width, margin_height;
static Boolean		initialized = FALSE;


/************************************************************************/
/*      Local functions                                                 */
/************************************************************************/
static void	initialize (
	Widget	button );

static void	flatten_button (
	Widget	button );

static void	unflatten_button (
	Widget	button );

static void	CB_DisarmButton (
	Widget		button,
	XtPointer	client_data,
	XtPointer	xt_call_data );

static void	CB_ArmButton (
	Widget		button,
	XtPointer	client_data,
	XtPointer	xt_call_data );

static void	EH_EnterButton (
	Widget		button,
	XtPointer	client_data,
	XEvent		*event, 
	Boolean		*continue_to_dispatch_return );

static void	EH_LeaveButton (
	Widget		button,
	XtPointer	client_data,
	XEvent		*event, 
	Boolean		*continue_to_dispatch_return );


/************************************************************************/
/* FUNCTION : add_flatButtonCB                                          */
/* LONGNAME : add event handlers and callbacks                          */
/*          : to flatten toolbar buttons                                */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-05-09                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
void	add_flatButtonCB (
	Widget		button )
{
  XtAddEventHandler(button, EnterWindowMask, FALSE, EH_EnterButton, (XtPointer)0);
  XtAddEventHandler(button, LeaveWindowMask, FALSE, EH_LeaveButton, (XtPointer)0);
  XtAddCallback(button, XmNarmCallback,    CB_ArmButton, (XtPointer)0);
  XtAddCallback(button, XmNdisarmCallback, CB_DisarmButton, (XtPointer)0);

  if (!initialized)
    initialize(button);

  flatten_button(button);
}


/************************************************************************/
/* FUNCTION : initialize                                                */
/* LONGNAME : save default shadow and margin sizes                      */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-05-11                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
static void	initialize (
	Widget	button )
{
  Arg		al[10];
  register int	ac = 0;

  XtSetArg(al[ac], XmNshadowThickness, &shadow_thickness);	ac++;
  XtSetArg(al[ac], XmNmarginWidth, &margin_width);		ac++;
  XtSetArg(al[ac], XmNmarginHeight, &margin_height);		ac++;
  XtGetValues (button, al, ac);
  ac		= 0;
}


/************************************************************************/
/* FUNCTION : flatten_button                                            */
/* LONGNAME : remove shadow from toolbar button - flat look             */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-05-11                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
static void	flatten_button (
	Widget	button )
{
  Arg		al[10];
  register int	ac = 0;
  Dimension	shadow;

  XtSetArg(al[ac], XmNshadowThickness, &shadow);		ac++;
  XtGetValues (button, al, ac);
  ac		= 0;

  if (0 != shadow)
  { /* button currently unflattened */
    XtSetArg(al[ac], XmNshadowThickness, 0);			ac++;
    XtSetArg(al[ac], XmNmarginWidth, shadow_thickness + margin_width);
								ac++;
    XtSetArg(al[ac], XmNmarginHeight, shadow_thickness + margin_height);
								ac++;
    XtSetValues(button, al, ac);
    ac		= 0;
  }
}


/************************************************************************/
/* FUNCTION : unflatten_button                                          */
/* LONGNAME : restore shadow to toolbar button - normal look            */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-05-11                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
static void	unflatten_button (
	Widget	button )
{
  Arg		al[10];
  register int	ac = 0;
  Dimension	shadow;

  XtSetArg(al[ac], XmNshadowThickness, &shadow);		ac++;
  XtGetValues (button, al, ac);
  ac		= 0;

  if (0 == shadow)
  { /* button currently flattened */
    XtSetArg(al[ac], XmNshadowThickness, shadow_thickness);	ac++;
    XtSetArg(al[ac], XmNmarginWidth, margin_width);		ac++;
    XtSetArg(al[ac], XmNmarginHeight, margin_height);		ac++;
    XtSetValues(button, al, ac);
    ac		= 0;
  }
}


/************************************************************************/
/* FUNCTION : EH_EnterButton, EH_LeaveButton                            */
/* LONGNAME : event handlers - enter, leave button                      */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-05-09                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
static void	EH_EnterButton (
	Widget		button,
	XtPointer	client_data,
	XEvent		*event, 
	Boolean		*continue_to_dispatch_return )
{
  if (!(event->xcrossing.state & BUTTON_MASK))
  { /* no button is active */
    if (EnterNotify == event->type)
    {
      unflatten_button(button);
      pressed_button	= button;
    }
  }
}


static void	EH_LeaveButton (
	Widget		button,
	XtPointer	client_data,
	XEvent		*event, 
	Boolean		*continue_to_dispatch_return )
{
  if (!(event->xcrossing.state & BUTTON_MASK))
  { /* no button is active */
    if (LeaveNotify == event->type)
    {
      flatten_button(button);
      pressed_button	= 0;
    }
  }
}


/************************************************************************/
/* FUNCTION : CB_ArmButton, CB_DisarmButton                             */
/* LONGNAME : callbacks - arm, disarm button                            */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-05-09                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : For those foolish guys of us, who push BSelect over the   */
/*          : separator and release it over the button and such stuff.  */
/************************************************************************/
static void	CB_ArmButton (
	Widget		button,
	XtPointer	client_data,
	XtPointer	call_data )
{
  Boolean	set;

  if (button != pressed_button)
  { /* the EnterEvent was outwitted and */
    /* BSelect was pressed inside the button */
    unflatten_button(button);
    pressed_button	= button;
  }
}


static void	CB_DisarmButton (
	Widget		button,
	XtPointer	client_data,
	XtPointer	call_data )
{
  Boolean	set;

  if (button != pressed_button)
  { /* the EnterEvent was outwitted and */
    /* BSelect was released inside the button */
    unflatten_button(button);
    pressed_button	= button;
  }
}

#endif	/* FLAT_BUTTONS */
