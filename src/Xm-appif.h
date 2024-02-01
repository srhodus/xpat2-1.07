/************************************************************************/
/* MODULE   : Xm-appif.h                                                */
/* LONGNAME : X-Patience / Motif based Graphical User Interface         */
/* AUTHOR   : Christian Anzenberger                                     */
/*          : Several methods exported by the GUI                       */
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

#ifndef XM_ _H
#define XM_ _H

void	show_active_rules ( void );

void	show_message (
	const char	*string, 
	... );

int	checksound ( void );

void	Force_Resize (
	XSize_t		width, 
	XSize_t		height );

void	request_confirm (
	void		(*dofunc)( void ),
	const char	prompt[] );

void	cmd_LeavePat ( void );

void	cmd_Cancel ( void );

void	cmd_Confirm ( void );

#endif /* XM_ _H */
