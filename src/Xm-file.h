/************************************************************************/
/* MODULE   : Xm-file.h                                                 */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/*          : File selection dialog                                     */
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

#ifndef XM_FILE_H
#define XM_FILE_H

extern Widget	shellDialogFile;
extern Widget	fileselDialogFile;
extern Widget	butFileApply;
extern Widget	butFileCancel;
extern Widget	butFileHelp;
extern Widget	scrlistFileFiles;
extern Widget	sbhorFileFiles;
extern Widget	sbverFileFiles;
extern Widget	listFileFiles;
extern Widget	labelFileFiles;
extern Widget	butFileOk;
extern Widget	labelFileSelection;
extern Widget	sepFile;
extern Widget	textFileSelection;
extern Widget	labelFileFilter;
extern Widget	textFileFilter;
extern Widget	labelFileDirs;
extern Widget	scrlistFileDirs;
extern Widget	sbhorFileDirs;
extern Widget	sbverFileDirs;
extern Widget	listFileDirs;
extern Widget	optmenuFileSetfilter;
extern Widget	labelFileSetfilter;
extern Widget	cascadeFileSetfilter;
extern Widget	menuFileSetfilter;
extern Widget	butFileSetfilterAll;
extern Widget	butFileSetfilter[];


void	create_shellDialogFile (
	Widget	parent );

#endif /* XM_FILE_H */
