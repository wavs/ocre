/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/init.c
 *   This file contains functions about the initialization
 *   of the program like the SDL for example.
 */

#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"

/**
 * This function initializes SDL lib. and create a window if
 * display option is activate.
 * @param screen SDL surface destination.
 * @param display Integer if >0 then display is activated.
 */
void InitSDL()
{
  /* Initialization of the SDL */
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
      /* Logs the error */
      fprintf(stderr, "SDL Initialization error: %s\n",SDL_GetError());
      /* End of the program */
      exit(EXIT_FAILURE);
    }
  printf("SDL initialized.\n");
  atexit(SDL_Quit);
}
