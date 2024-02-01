/************************************************************************/
/* MODULE   : Xm-platform.c                                             */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/*          : Compilation platform                                      */
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

#include "Xm-platform.h"
 
/************************************************************************/
/* FUNCTION : platform                                                  */
/* LONGNAME : get the platform for which the program is compiled        */
/* AUTHOR   : Christian Anzenberger                                     */
/* CREATED  : 1998-08-12                                                */
/* INPUT    :                                                           */
/* OUTPUT   : string "Operating-System X.x (Processor-Family)"          */
/* NOTES    : -                                                         */
/************************************************************************/
char	*platform ( void )
{
  return (PLATFORM);
}
