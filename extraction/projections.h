/*
** OCRe - The ultimate OCR - HUGE Software
** OCRe is a project developep by 2nd year EPITA students
** - website: http://huge.ocre.free.fr/
** - svn repository: http://code.google.com/p/ocre
**
** About this folder: /extraction
**   This folder contains the character extraction part of OCRe.
** About this file: /extraction/projections.h
**   This is the header of "projections.c".
*/


/*
** This function returns a pointer on an int vector which
** contains the horizontal projection of the picture.
** Prerequired: Allocation of the t_binary_image pointed by pic.
*/
void horizontal_projection(t_binary_image *pic);

/*
** This function returns a pointer on an int vector which
** contains the vertical projection of the picture.
** Prequired: Allocation of the t_binary_image pointed by pic.
*/
/*
void vertical_projection(t_binary_image *pic);
*/
