/************************************************************************/
/* MODULE   : Xm-args.c                                                 */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/*          : process command arguments                                 */
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
#include <stdio.h>
#include <stdarg.h>

#include "Xm-main.h"
#include "X-pat.h"
#include "Xm-platform.h"
#include "version.h"


/************************************************************************/
/* FUNCTION : process_extra_args                                        */
/* LONGNAME : process extra arguments                                   */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1999-03-28                                                */
/* INPUT    :                                                           */
/* OUTPUT   : -                                                         */
/* NOTES    : -                                                         */
/************************************************************************/
int	process_extra_args (
	int	argc, 
	char	**argv )
{
  char	progname[256];

  char	*string_ptr;
  int	print_usage	= FALSE;
  int	return_ok	= TRUE;
  int	i;

  /* initalize argvs */
  game.seed		= -1L;
  loadfilename		= NULL;

  /* get own program name from command */
  if (string_ptr = strrchr(argv[0], '/'))
    string_ptr		+= 1;
  else
    string_ptr		= argv[0];
  strncpy (progname, string_ptr, sizeof(progname));
  progname[sizeof(progname)-1]	= '\0';
  
  for (i = 1; i < argc; i++)
  { /* argv is an option */
    if ('-' == (argv[i])[0])
    { /* argument is an option */
      if (0 == strcmp(argv[i], "-help"))
      { /* print usage */
        print_usage	= TRUE;
        continue;
      }
      
      if (0 == strcmp(argv[i], "-version"))
      { /* print program version */
        fprintf(stderr, "%s: X-Patience for " PLATFORM " Version " VERSION "\n"
			"   Last built: " __DATE__ " / " __TIME__ "\n",
			progname);
        return_ok	= FALSE;
        continue;
      }

      /* unknown option */
      fprintf(stderr, "%s: unrecognized option %s\n", progname, argv[i]);
      print_usage	= TRUE;
      continue;
    }
    else
    { /* argument is not an option */
      if (isdigit(*argv[i]))
      { /* argument is number */
        if (NULL == loadfilename)
	{
          game.seed	= atol (argv[i]);
          if ((0L > game.seed) || (1000000000L <= game.seed))
	  { /* seed out of range */
            print_usage	= TRUE;
          }
        }
	else
	{ /* conflicting parameters */
          fprintf(stderr, "%s: unrecognized option %s\n", progname, argv[i]);
          print_usage	= TRUE;
        }
        continue;
      }
      else
      { /* argument is string */
        if (-1L == game.seed)
	{
	  loadfilename = argv[i];
        }
	else
	{ /* conflicting parameters */
          fprintf(stderr, "%s: unrecognized option %s\n", progname, argv[i]);
          print_usage	= TRUE;
        }
        continue;
      }
    }
  }

  if (print_usage)
  {
    fprintf(stderr, 
      "Usage:\t%s [options] [seed|loadfilename]\n"
	"\toptions are all standard X11 toolkit options and\n"
	"\t-xpmdir (dir)       to set directory for xpm files\n"
	"\t-rules (ruleset)    to initially use specified rules\n"
	"\t-faceup|facedown|decks|slots|jokers|tmps (num) customize parameters\n"
	"\t-relaxed|flips|turn|rotations (num)            customize parameters\n"
	"\t-tb (color)         set background color of tableau\n"
	"\t-arrowcolor (color) set color of hint arrow\n"
	"\t-markcolor (color)  set color of frame to mark cards\n"
	"\t-markwidth (wdth)   set width of frame to mark cards\n"
#ifdef SOUND
	"\t-sound              sound toggle on\n"
	"\t-nosound            sound toggle off\n"
#endif
#ifdef GFX1
#ifdef LOADCARDS
	"\t-cards (filename)   to load external bitmap cardset\n"
#endif
	"\t-cb (color)         set cardback color\n"
	"\t-red (color)        use a different 'red' for static grey screens\n"
#endif
	"\t-help               print this message and exit\n"
	"\t-version            print version and exit\n",
	progname);
    return_ok		= FALSE;
  }

  return (return_ok);
}
