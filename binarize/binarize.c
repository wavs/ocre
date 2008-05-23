/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: binarize/
 *   Binarize creates a binary file from a bitmap image.
 * About this file: binarize/binarize.c
 *   This file contains functions about the binarization.
 */

#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "binarize.h"
#include "pixel.h"

/**
 * This function initializes SDL lib. and create a window if
 * display option is activate.
 *
 * @param screen SDL surface destination.
 * @param display Integer if >0 then display is activated.
 */
void InitSDL()
{
  /* Initialization of the SDL */
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
      /* Logs the error */
      fprintf(stderr, " > SDL Initialization error: %s <\n",
	      SDL_GetError());
      /* End of the program */
      exit(EXIT_FAILURE);
    }
  atexit(SDL_Quit);
}

/**
 * This function gets the name of the file
 * without the extension (.bmp).
 *
 * @param filename Name of the bitmap file
 *
 * @return Tha name without the extension
 */
char *getName(char *filename)
{
  int i;
  char *ret;
  
  i = 0;
  ret = strdup(filename);
  while (ret[i] != '\0')
    i++;
  ret[i-1] = 't';
  ret[i-2] = 'x';
  ret[i-3] = 't';
  
  return(ret);
}

/**
 * This function determines if the extension of a
 * filename is ".bmp".
 *
 * @param filename Name of the bitmap file
 */
int is_bmp(char *filename)
{
  int i;

  i = 0;
  while (filename[i] != '\0')
    i++;
  if (i >= 4)
    {
      i--;
      if ((filename[i] == 'p')
	  && (filename[i-1] == 'm')
	  && (filename[i-2] == 'b')
	  && (filename[i-3] == '.'))
	{
	  return(1);
	}
    }
  return(0);
}

/**
 * This function converts a bitmap image
 * into a binary image.
 *
 * @param image A bitmap image loaded in an allocated SDL surface.
 * @param filename Name of the bitmap file.
 */
void binarizeTheBitmap(SDL_Surface *image, char *output)
{
  int i;
  int j;
  Uint32 black;
  FILE *file;

  file = NULL;
  if ((file = fopen(output, "w+")) != NULL)
    {
      black = SDL_MapRGB(image->format, 0x00, 0x00, 0x00);
      
      SDL_LockSurface(image);

      for (i=0; i < image->h; ++i)
	{
	  for (j=0; j < image->w; ++j)
	    {
	      if (getpixel(image,j,i) == black)
		fputc('1', file);
	      else
		fputc('0', file);
	    }
	  fputc('\n', file);
	}
      fputc('\n', file);
      
      SDL_UnlockSurface(image);

      fclose(file);
      
    }
  else
    printf(" > Can't open BMP file sorry :( <\n");
}
