/*
** OCRe - The ultimate OCR - HUGE Software
** OCRe is a project developed by 2nd year EPITA students
** - website: http://huge.ocre.free.fr/
** - svn repository: http://code.google.com/p/ocre
**
** About this folder: /extraction
**   This folder contains the character extraction part of OCRe.
** About this file: /extraction/extraction.c
**   This file contains functions about the extraction of lines
**   and characters.
*/

#include <stdlib.h>
#include "structures.h"

/*
** This function extracts the lines of the picture.
** It returns the set of lines in a linked list which
** is in a t_result_extraction structure.
** Prerequired: Allocation of the structure pointed by pic
** and the two vectors hproj & vproj
*/
t_result_extraction *extract_line(t_binary_image *pic)
{
  int i;
  int i_tmp;
  int index;
  int height_tmp;
  t_line_set *tmp;
  t_line_set *father;
  t_result_extraction *result;
  
  result = NULL;
  result = malloc(sizeof(t_result_extraction));
  /* Gestion d'erreurs mémoire */
  result->linelist = NULL;
  result->name = pic->name;
  index = 0;
  i = 0;
  while (i < pic->height)
    {
      if (pic->hproj[i] > 0)
	{
	  i_tmp = i;
	  height_tmp = 0;
	  while ((pic->hproj[i] != 0) && (i < pic->height))
	    {
	      height_tmp++;
	      i++;
	    }
	  if (height_tmp > (0.5*(pic->height / 100)))
	    {
	      index++;
	      tmp = malloc(sizeof(t_line_set));
	      /* Gestion d'erreurs de mémoire */
	      tmp->id = index;
	      tmp->pos = i_tmp;
	      tmp->charlist = NULL;
	      tmp->next = NULL;
	      tmp->height = height_tmp;
	      if (index == 1)
		{
		  result->linelist = tmp;
		}
	      else
		{
		  father->next = tmp;
		}
	      father = tmp;
	    }
	}
      i++;
    }
  return (result);
}
