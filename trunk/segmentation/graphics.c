/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/graphics.c
 *   This file contains functions about loading bitmap
 *   and drawing lines & box.
 */

#include "structures.h"
#include "SDL/SDL.h"

/**
 * This function loads a bitmap image.
 *
 * @param flename Name of bitmap file.
 *
 * @return SDL surface with the bitmap image loaded.
 */
SDL_Surface *load_image(char *filename)
{
  SDL_Surface *loadedImage;
  SDL_Surface *optimizedImage;

  loadedImage = NULL;
  optimizedImage = NULL;
  loadedImage = SDL_LoadBMP(filename);
  if (loadedImage != NULL)
    {
      optimizedImage = SDL_DisplayFormat(loadedImage);
      SDL_FreeSurface(loadedImage);
    }
  return (optimizedImage);
}

/**
 * This function blitts a source surface on a destination surface.
 *
 * @param x X Coordinate.
 * @param y Y Coordinate.
 * @param src SDL surface source.
 * @param dst SDL surface destination.
 */
void apply_surface(int x, int y, SDL_Surface *src, SDL_Surface *dst)
{
  SDL_Rect offset;

  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src,NULL,dst,&offset);
}

/**
 * This function draws a line on a SDL surface.
 *
 * @param x X Coordinate.
 * @param y Y Coordinate.
 * @param w Width of the line.
 * @param h Height of the line.
 * @param color Color of the line.
 * @param surface SDL surface destination.
 */
void draw_line(int x, int y, int w,int h, Uint32 color,
	       SDL_Surface* surface)
{
  SDL_Rect r;

  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
  SDL_FillRect(surface, &r, color);
}

/**
 * This function draws the box around the detected lines.
 *
 * @param image SDL surface destination.
 * @param linelist Set of extracted lines.
 */
void trace_boxline(SDL_Surface *image, t_line_set *linelist)
{
  t_line_set *tmp;
  Uint32 cl;

  cl = SDL_MapRGB(image->format, 0x00, 0x00, 0x00);
  draw_line(0, 230, 3, 23, cl, image);
  tmp = linelist;
  while (tmp != NULL)
    {
      draw_line(0, tmp->pos, image->w, 1, cl, image);
      draw_line(0, (tmp->pos + tmp->height), image->w, 1, cl, image);
      tmp = tmp->next;
    }
}
