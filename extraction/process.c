/*
** OCRe - The ultimate OCR - HUGE Software
** OCRe is a project developed by 2nd year EPITA students
** - website: http://huge.ocre.free.fr/
** - svn repository: http://code.google.com/p/ocre
**
** About this folder: /extraction
**   OCRec is the character extraction part of OCRe.
** About this file: /extraction/process.c
**   This file contains a function which executes the
**   extraction process.
*/

#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "SDL/SDL.h"
#include "binarization.h"
#include "projections.h"
#include "extraction.h"
#include "graphics.h"
#include "free.h"

/*
** This function executes the extraction process.
*/
void processAll(t_launch_infos *infos)
{
  t_binary_image *pic;
  t_result_extraction *result;
  SDL_Surface *image;
  
  pic = NULL;
  result = NULL;
  image = NULL;
  image = SDL_LoadBMP(infos->inFile);
  if (image != NULL)
    { printf("Image %s loaded.\n", infos->inFile);
      pic = bitmap_to_binaryimage(image,infos->inFile);
      if (pic != NULL)
	{ printf("Binarization done.\n");
	  horizontal_projection(pic);
	  printf("Horizontal projection done.\n");
	  result = extract_line(pic);
	  if (result != NULL)
	    { printf("Lines extraction done.\n");
	      trace_boxline(image,result->linelist);
	      if (SDL_SaveBMP(image, infos->outFile) < 0)
		{ fprintf(stderr,"SDL BMP saving error"); }
	      else
		{ printf("Image %s saved.\n", infos->outFile); }
	      /* free_all(pic,result); */
	    }
	}
      SDL_FreeSurface(image);
    }
  else
    {
      fprintf(stderr, "SDL BMP Loader error\n");
      exit(EXIT_FAILURE);
    }
}
