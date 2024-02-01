/************************************************************************/
/* MODULE   : Xm-platform.h                                             */
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
/*-------+--------+----------------------------------------------+------*/
/* 0.9   |19991018| First public snapshot                        | ac   */
/************************************************************************/

#ifndef XM_PLATFORM_H
#define XM_PLATFORM_H

#include "Xm-ostype.h"

#ifdef OS_SOLARIS
  #ifdef OS_SOLARIS_SPARC
    #define PLATFORM  "Solaris 2.x (SPARC)"
  #else
    #ifdef OS_SOLARIS_INTEL
      #define PLATFORM  "Solaris 2.x (Intel)"
    #else
      #define PLATFORM  "Solaris 2.x"
    #endif
  #endif
#endif

#ifdef OS_SUNOS
  #ifdef OS_SUNOS_SPARC
    #define PLATFORM  "SunOS 4.x (SPARC)"
  #else
    #define PLATFORM  "SunOS"
  #endif
#endif

#ifdef OS_DOMAINOS
  #ifdef OS_DOMAINOS_M68K
    #define PLATFORM  "DomainOS (m68k)"
  #else
    #ifdef OS_DOMAINOS_A88K
      #define PLATFORM  "DomainOS (PRISM)"
    #else
      #define PLATFORM  "DomainOS"
    #endif
  #endif
#endif

#ifdef OS_LINUX
  #ifdef OS_LINUX_INTEL
    #ifdef OS_LINUX_INTEL_LIBC5
      #define PLATFORM  "Linux (Intel, libc5)"
    #else
      #ifdef OS_LINUX_INTEL_GLIBC2
        #define PLATFORM  "Linux (Intel, glibc2)"
      #else
        #define PLATFORM  "Linux (Intel)"
      #endif
    #endif
  #else
    #ifdef OS_LINUX_SPARC
      #define PLATFORM  "Linux (SPARC)"
    #else
      #define PLATFORM  "Linux"
    #endif
  #endif
#endif

#ifdef OS_WIN32
  #ifdef OS_WINNT
    #ifdef OS_WINNT_INTEL
      #define PLATFORM  "Windows NT (Intel)"
    #else
      #ifdef OS_WINNT_ALPHA
        #define PLATFORM  "Windows NT (Alpha)"
      #else
        #define PLATFORM  "Windows NT"
      #endif
    #endif
  #else
    #ifdef OS_WIN9X
        #define PLATFORM  "Windows 9x"
    #else
      #ifdef OS_WIN32S
        #define PLATFORM  "Win3.x/Win32s"
      #else
        #define PLATFORM  "Win32 Platform"
      #endif
    #endif
  #endif
#endif

#endif /* XM_PLATFORM_H */
