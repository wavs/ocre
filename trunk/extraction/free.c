/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /extraction
 *   OCRec is the character extraction part of OCRe.
 * About this file: /extraction/free.c
 *   This file contains functions which free memory.
 */

#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "wrappers.h"

/**
 * This function frees the structure of binary image.
 * @param pic Binary image.
 */
void free_pic(t_binary_image *pic)
{
  int i;

  if (pic != NULL)
    {
      wfree(pic->hproj);
      for (i=0; i < pic->height; i++)
	wfree(pic->data[i]);
      wfree(pic->data);
      wfree(pic);
    }
}

/**
 * This function frees the structure of the extraction result.
 * @param result Result structure with lines set.
 */
void free_result(t_result_extraction *result)
{
  t_character_set *son_char;
  t_line_set *son_line;

  /* Free of linked list of lines */
  if (result != NULL)
    {
      if (result->linelist != NULL)
	{
	  son_line = result->linelist->next;
	  while (son_line != NULL)
	    {
	      /* Free of linked list of characters*/
	      if (result->linelist->charlist != NULL)
		{
		  son_char = result->linelist->charlist->next;
		  while (son_char != NULL)
		    {
		      wfree(result->linelist->charlist);
		      result->linelist->charlist = son_char;
		      son_char = son_char->next;
		    }
		  wfree(result->linelist->charlist);
		}
	      wfree(result->linelist);
	      result->linelist = son_line;
	      son_line = son_line->next;
	    }
	  wfree(result->linelist);
	}
      wfree(result);
    }
}

/**
 * This function frees all structures from the extraction part.
 * @param pic Binary image.
 * @param result Result structure with lines set.
 */
void free_all(t_binary_image *pic, t_result_extraction *result)
{
  free_result(result);
  free_pic(pic);
}
