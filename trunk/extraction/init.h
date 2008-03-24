/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /extraction
 *   OCRec is the character extraction part of OCRe.
 * About this file: /extraction/init.h
 *   This is the header of "init.c".
 */

#ifndef INIT_H
#define INIT_H

#endif /* INIT_H */

#include "SDL/SDL.h"

/**
 * This function initializes SDL lib. and create a window if
 * display option is activate.
 * @param screen SDL surface destination.
 * @param display Integer if >0 then display is activated.
 */
void InitSDL(SDL_Surface *screen, int display);
