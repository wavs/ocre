/*
** OCRe - The ultimate OCR - HUGE Software
** OCRe is a project developed by 2nd year EPITA students
** - website: http://huge.ocre.free.fr/
** - svn repository: http://code.google.com/p/ocre
**
** About this folder: OCRec
**   OCRec is the character extraction part of OCRe.
** About this file: OCRec/binarization.h
**   This is the header of "binarization.c".
*/

#include "SDL/SDL.h"

/*
** This function converts a bitmap image (loaded in a SDL surface)
** into a binary image (t_binary_image in structures.h).
** Prerequisites: Allocation of the SDL_Surface image.
*/
t_binary_image *bitmap_to_binaryimage(SDL_Surface *image, char *filename);
