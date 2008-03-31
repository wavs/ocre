/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /extraction
 *   OCRec is the character extraction part of OCRe.
 * About this file: /extraction/pixel.h
 *   This is the header of "pixel.c".
 */

#ifndef PIXEL_H
#define PIXEL_H

/**
 * This function returns the color of a pixel.
 * Before calling this function, SDL surface must be locked.
 * @param surface Allocated SDL surface source.
 * @param x X Coordinate of the pixel.
 * @param y Y Coordinate of the pixel.
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y);

/**
 * This function sets the color of a pixel.
 * Before calling this function, SDL surface must be locked.
 * @param surface Allocated SDL surface source.
 * @param x X Coordinate of the pixel.
 * @param y Y Coordinate of the pixel.
 * @param pixel Color of the pixel.
 */
void setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

#endif /* PIXEL_H */
