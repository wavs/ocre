/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: binarize/
 *   Binarize creates a binary file from a bitmap image.
 * About this file: binarize/binarize.c
 *   This file is the header of binarize.c
 */

#include "SDL/SDL.h"

/**
 * This function initializes SDL lib. and create a window if
 * display option is activate.
 *
 * @param screen SDL surface destination.
 * @param display Integer if >0 then display is activated.
 */
void InitSDL();

/**
 * This function gets the name of the file
 * without the extension (.bmp).
 *
 * @param filename Name of the bitmap file
 *
 * @return Tha name without the extension
 */
char *getName(char *filename);

/**
 * This function determines if the extension of a
 * filename is ".bmp".
 *
 * @param filename Name of the bitmap file
 */
int is_bmp(char *filename);

/**
 * This function converts a bitmap image
 * into a binary image.
 *
 * @param image A bitmap image loaded in an allocated SDL surface.
 * @param filename Name of the bitmap file.
 */
void binarizeTheBitmap(SDL_Surface *image, char *output);
