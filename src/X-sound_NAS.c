/*****************************************************************************/
/*									     */
/*									     */
/*	X patience version 2 -- module sound-NAS.c			     */
/*									     */
/*	simple access to the network audio system (tested with NAS-1.2)	     */
/*	written by Michael Bischoff					     */
/*	see COPYRIGHT.xpat2 for Copyright details			     */
/*									     */
/*									     */
/*****************************************************************************/

#include "xpat.h"
#include <audio/audiolib.h>
#include <audio/soundlib.h>

#ifndef NAS_AUDIO_EXT
/* choose "au" or "wav" */
#define NAS_AUDIO_EXT	"wav"
#endif

void play_sound(const char *filename) {
    static int audio = 1;
    if (audio && checksound()) {
	static AuServer *aud;
	char fullname[256];

	if (!(aud = AuOpenServer(NULL, 0, NULL, 0, NULL, NULL))) {
	    /* TODO: use $DISPLAY as default for $AUDIOSERVER? */
	    fprintf(stderr, "xpat2: Warning, cannot connect to NAS audio server!\n"
		    "perhaps AUDIOSERVER is not set correctly?\n");
	    audio = 0;
	    return;		/* cannot open /dev/audio */
	}
	flush_display();
	sprintf(fullname, "%s/audio/%s.%s", LIBDIR, filename, NAS_AUDIO_EXT);
	(void)AuSoundPlaySynchronousFromFile(aud, fullname, 100);
    }
}
