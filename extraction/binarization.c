/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: OCRec
 *   OCRec is the character extraction part of OCRe.
 * About this file: OCRec/binarization.c
 *   This file contains functions about the binarization.
 */

#include <stdlib.h>
#include "structures.h"
#include "SDL/SDL.h"
#include "projections.h"
#include "pixel.h"
#include "wrappers.h"

/**
 * This function converts a bitmap image
 * into a binary image.
 * @param image A bitmap image loaded in an allocated SDL surface.
 * @param filename Name of the bitmap file.
 * @return Binary image.
 */
t_binary_image *bitmap_to_binaryimage(SDL_Surface *image,
				      char *filename)
{
  int i;
  int j;
  Uint32 black;
  t_binary_image *pic;

  black = SDL_MapRGB(image->format, 0x00, 0x00, 0x00);
  pic = NULL;
  pic = wmalloc(sizeof(t_binary_image));
  pic->name = filename;
  pic->width = image->w;
  pic->height = image->h;
  pic->data = wmalloc(pic->height * sizeof(int));
  for (i=0; i < pic->width; i++)
    pic->data[i] = wmalloc(pic->height * sizeof(int));
  SDL_LockSurface(image);
  for (i=0; i < image->h; i++)
    {
      for (j=0; j < image->w; j++) 
	{
	  if (getpixel(image,j,i) == black)
	    pic->data[j][i] = 1;
	  else
	    pic->data[j][i] = 0;
	}
    }
  SDL_UnlockSurface(image);
  pic->hproj = NULL;
  horizontal_projection(pic);
  printf("Horizontal projection done.\n");
  return(pic);
}
