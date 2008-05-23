/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: binarize/
 *   Binarize creates a binary file from a bitmap image.
 * About this file: binarize/main.c
 *   This file contains functions about computations on pixels.
 */

#include "SDL/SDL.h"

/**
 * This function returns the color of a pixel.
 * Before calling this function, SDL surface must be locked.
 *
 * @param surface Allocated SDL surface source.
 * @param x X Coordinate of the pixel.
 * @param y Y Coordinate of the pixel.
 *
 * @return Color of the pixel
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
  int bpp;
  Uint8 *p;

  bpp = surface->format->BytesPerPixel;
  p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
  switch(bpp)
    {
    case 1:
      return (*p);

    case 2:
      return (*(Uint16 *)p);

    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
	  return (p[0] << 16 | p[1] << 8 | p[2]);
	}
      else
	{
	  return (p[0] | p[1] << 8 | p[2] << 16);
	}

    case 4:
      return (*(Uint32 *)p);

    default:
      return (0);
    }
}

/**
 * This function sets the color of a pixel.
 *
 * Before calling this function, SDL surface must be locked.
 * @param surface Allocated SDL surface source.
 * @param x X Coordinate of the pixel.
 * @param y Y Coordinate of the pixel.
 * @param pixel Color of the pixel.
 */
void setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  int bpp;
  Uint8 *p;

  bpp = surface->format->BytesPerPixel;
  p = (Uint8 *)surface->pixels + y * surface->pitch + x *bpp;

  switch(bpp)
    {
    case 1:
      *p = pixel;
      break;

    case 2:
      *(Uint16 *)p = pixel;
      break;

    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
	  p[0] = (pixel >> 16) & 0xff;
	  p[1] = (pixel >> 8) & 0xff;
	  p[2] = pixel & 0xff;
	}
      else
	{
	  p[0] = pixel & 0xff;
	  p[1] = (pixel >> 8) & 0xff;
	  p[2] = (pixel >> 16) & 0xff;
	}
      break;

    case 4:
      *(Uint32 *)p = pixel;
      break;
    }
}
