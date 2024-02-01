/************************************************************************/
/* MODULE   : ostype.h                                                  */
/* LONGNAME : determine operating system                                */
/* AUTHOR   : Christian Anzenberger                                     */
/* CONTACT  : christian.anzenberger@siemens.at                          */
/* CREATED  : 1999-02-13                                                */
/* NOTES    :                                                           */
/************************************************************************/
/* History of Change:                                                   */
/*-------+--------+----------------------------------------------+------*/
/*Version|  Date  | Changes                                      |Author*/
/*-------+--------+----------------------------------------------+------*/
/* 0.1   |19980913| Initial creation                             | ac   */
/************************************************************************/


#ifndef _OSTYPE_H
#define _OSTYPE_H

/************************************************************************/
/*      global defines                                                  */
/************************************************************************/
#if (defined (__sun) && defined (__SVR4))
  #define		OS_SOLARIS
  #define		OS_SYSV
  #if defined (__SPARC)
    #define		OS_SOLARIS_SPARC
  #else
    #if defined (__i386)
      #define		OS_SOLARIS_INTEL
    #endif
  #endif
#endif

#if (defined (__sun) && !defined (__SVR4))
  #define		OS_SUNOS
  #define		OS_BSD
  #if defined (__SPARC)
    #define		OS_SUNOS_SPARC
  #endif
#endif

#if defined (__apollo)
  #define		OS_DOMAINOS
  #define		OS_BSD
  #if ISP == m68k
    #define		OS_DOMAINOS_M68K
  #else
    #if ISP == a88k
      #define		OS_DOMAINOS_A88K
    #endif
  #endif
#endif

#if defined (__linux)
  #define		OS_LINUX
  #if defined (__i386)
    #define		OS_LINUX_INTEL
    #if defined (_LINUX_C_LIB_VERSION_MAJOR)
      #if _LINUX_C_LIB_VERSION_MAJOR == 5
        #define		OS_LINUX_INTEL_LIBC5
      #endif
    #else
      #if defined (__GLIBC__)
        #if __GLIBC__ == 2
          #define	OS_LINUX_INTEL_GLIBC2
        #endif
      #endif
    #endif
  #else
    #if defined (__SPARC)
      #define		OS_LINUX_SPARC
    #endif
  #endif
#endif

#if defined (WIN32)
  #define		OS_WIN32
#endif

#endif /* _OSTYPE_H */
