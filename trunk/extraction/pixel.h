/*
** OCRe - The ultimate OCR - HUGE Software
** OCRe is a project developed by 2nd year EPITA students
** - website: http://huge.ocre.free.fr/
** - svn repository: http://code.google.com/p/ocre
**
** About this folder: /extraction
**   OCRec is the character extraction part of OCRe.
** About this file: /extraction/pixel.h
**   This is the header of "pixel.c".
*/

#include "SDL/SDL.h"

/*
** This function returns the color of a pixel.
** Before calling this function, SDL surface must be locked.
** Prerequisites: Allocation of the SDL_Surface surface.
*/
Uint32 getpixel(SDL_Surface *surface, int x, int y);

/*
** This function sets the color of a pixel.
** Before calling this function, SDL surface must be locked.
** Prerequisites: Allocation of the SDL_Surface surface.
*/
void setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
