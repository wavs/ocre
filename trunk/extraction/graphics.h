/*
** OCRe - The ultimate OCR - HUGE Software
** OCRe is a project developed by 2nd year EPITA students
** - website: http://huge.ocre.free.fr/
** - svn repository: http://code.google.com/p/ocre
**
** About this folder: /extraction
**   OCRec is the character extraction part of OCRe.
** About this file: /extraction/graphics.h
**   This is the header of "graphics.c".
*/

#include "SDL/SDL.h"

/*
** This function loads a bitmap image
*/
SDL_Surface *load_image(char *filename);

/*
** This function blitts a source surface on a destination surface.
*/
void apply_surface(int x, int y, SDL_Surface *src, SDL_Surface *dst);

/*
** This function draws a line on a SDL surface.
*/
void draw_line(int x, int y, int w,int h, Uint32 color,
	       SDL_Surface* surface);

/*
** This function draws the box around the detected lines.
*/
void trace_boxline(SDL_Surface *image, t_line_set *linelist);
