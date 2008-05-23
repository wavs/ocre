/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/process.c
 *   This file contains a function which executes the
 *   extraction process.
 */

#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "SDL/SDL.h"
#include "binarization.h"
#include "projections.h"
#include "segmentation.h"
#include "print.h"
#include "free.h"
#include "tools.h"
#include "export.h"
#include "wrappers.h"

/**
 * This function executes the extraction process.
 *
 * @param infos Informations about the launch process.
 */
void processAll(t_launch_infos *infos)
{
  t_binary_image *pic;
  SDL_Surface *image;
  t_cc_list *cc_list;
  t_word_list *word_list;
  t_line_list *line_list;
  t_paragraph_list *paragraph_list;
  
  pic = NULL;
  image = NULL;
  image = SDL_LoadBMP(infos->inFile);
  if (image != NULL)
    { 
      if (infos->verbose)
	printf("\n >> Image %s loaded.\n", infos->inFile);
      pic = bitmap_to_binaryimage(image,infos->inFile);
      if (pic != NULL)
	{ 
	  if (infos->verbose)
	    printf(" >> Binarization done.\n");
	  cc_list = findCC(pic->matrix);
	  if (cc_list != NULL)
	    {
	      checkIfCharacter(cc_list, pic->height, pic->width);

	      /*  print_listCC(cc_list); */
	      if (infos->verbose)
		printf(" >> Extraction of %d characters done.\n", cc_list->nbcc);
	      word_list = makeWords(cc_list);
	      if (word_list != NULL)
		{
		  if (infos->verbose)
		    printf(" >> Extraction of %d words done.\n", word_list->nbword);
		  traceWords(image, word_list);
		  
		  line_list = makeLines(word_list);
		  if (line_list != NULL)
		    {
		      if (infos->verbose)
			printf(" >> Extraction of %d lines done.\n", line_list->nbline);
		      traceLines(image, line_list);

		      paragraph_list = makeParagraphes(line_list);
		      if (paragraph_list != NULL)
			{
			  if (infos->verbose)
			    printf(" >> Extraction of %d paragraphs done.\n", paragraph_list->nbparagraph);
			  updateCC(paragraph_list, image);
			  traceParagraphes(image, paragraph_list);
			  exportAll(paragraph_list, "seg_export.xml");
			}
		    }
		  
		}
	      
	      /*traceCC(image, cc_list); */

	      if (SDL_SaveBMP(image, infos->outFile) < 0)
		fprintf(stderr," > SDL BMP saving error <\n");
	      else
		if (infos->verbose)
		  printf(" >> Image %s saved.\n\n", infos->outFile);
	      /* free_listCC(cc_list) */
	      free_pic(pic);
	    }
	}
      SDL_FreeSurface(image);
    }
  else
    {
      fprintf(stderr, " > SDL BMP Loader error <\n");
      wfree(infos);
      exit(EXIT_FAILURE);
    }
}
