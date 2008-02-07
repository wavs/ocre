/*
** OCRe - The ultimate OCR - HUGE Software
** OCRe is a project developed by 2nd year EPITA students
** - website: http://huge.ocre.free.fr/
** - svn repository: http://code.google.com/p/ocre
**
** About this folder: /extraction
**   OCRec is the character extraction part of OCRe.
** About this file: /extraction/event.c
**   This file contains a function which manages SDL events.
*/

#include "SDL/SDL.h"

/*
** This function waits an event from user.
*/
void waitLoop()
{
  short int exitProgram;
  SDL_Event event;

  exitProgram = 0;
  while ( !exitProgram )
    {
      /* Reading of the tail of events */
      while ( SDL_PollEvent(&event) )
	{
	  switch (event.type)
	    {
	      /* End of the program */
	    case SDL_QUIT:
	      exitProgram = 1;
	      break;
	    case SDL_KEYDOWN:
	      if ( event.key.keysym.sym == SDLK_ESCAPE )
		{
		  exitProgram = 1;
		}
	      break;
	    }
	}
    }
}
