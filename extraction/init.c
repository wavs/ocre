/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /extraction
 *   OCRec is the character extraction part of OCRe.
 * About this file: /extraction/init.c
 *   This file contains functions about the initialization
 *   of the program like the SDL for example.
 */

#include "SDL/SDL.h"

/**
 * This function initializes SDL lib. and create a window if
 * display option is activate.
 * @param screen SDL surface destination.
 * @param display Integer if >0 then display is activated.
 */
void InitSDL(SDL_Surface *screen, int display)
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
  /* Option -d: display the SDL window. */
  if (display)
    {
      /* Creation of the screen surface */
      screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
      /* Logs the error */
      if ( screen == NULL )
	{
	  fprintf(stderr, "SDL Video mode error: %s\n",SDL_GetError());
	  /* End of the program */
	  exit(EXIT_FAILURE);
	}
      fprintf(stderr, "SDL screen opened.");
      /* Title of the window */
     SDL_WM_SetCaption("OCRe - HUGE Software - Extraction Part", NULL);
    }
}
