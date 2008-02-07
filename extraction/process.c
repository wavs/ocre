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
    {
      pic = bitmap_to_binaryimage(image,infos->inFile);
      if (pic != NULL)
	{
      horizontal_projection(pic);
      result = extract_line(pic);
      trace_boxline(image,result->linelist);
      SDL_SaveBMP(image, infos->outFile);
      SDL_FreeSurface(image);
      free_all(pic,result);
	}
    }
  else
    {
      fprintf(stderr, "SDL BMP Loader error\n");
      exit(EXIT_FAILURE);
    }
}
