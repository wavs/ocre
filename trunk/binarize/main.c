/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: binarize/
 *   Binarize creates a binary file from a bitmap image.
 * About this file: binarize/main.c
 *   This file contains the main function.
 */

#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "main.h"
#include "binarize.h"

int main(int argc, char **argv)
{
  SDL_Surface *image;
  char *output;

  if (argc > 1)
    {
      image = NULL;
      InitSDL();
      if (is_bmp(argv[1]))
	{
	  image = SDL_LoadBMP(argv[1]);
	  output = getName(argv[1]);
	  if (image != NULL)
	    binarizeTheBitmap(image, output);
	  else
	    printf(" > SDL BMP Loader error <\n");
	}
      else
	printf("> Not a BMP file <\n");
    }
  else
    printf("> You forget the BMP :p <\n");
  return(1);
}
