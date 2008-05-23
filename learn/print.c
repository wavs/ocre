/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/structures.h
 *   This file contains printing functions.
 */

#include <stdlib.h>
#include <stdio.h>
#include "structures.h"

void print_vector(int *vector, int length)
{
  int i;

  printf("-- Vector display --\n");
  printf("  length: %d\n", length);
  for (i=0; i < length; i++)
    printf(" %d",vector[i]);
  printf("\n\n");
}

void print_matrix(t_matrix *matrix)
{
  int i,j;

  printf("-- Matrix display --\n");
  printf("  rows: %d\n", matrix->nbrows);
  printf("  colums: %d\n\n", matrix->nbcols);
  for (i=0; i < matrix->nbrows; ++i)
    {
      printf("\n");
      for(j=0; j < matrix->nbcols; ++j)
	printf(" %d",matrix->data[i][j]);
    }
  printf("\n\n");
}

void print_listCC(t_cc_list *cc_list)
{
  t_cc_elt *tmp;

  if (cc_list != NULL)
    {
      printf("Connected component list\n");
      printf(" number of CC: %d\n\n", cc_list->nbcc);
      tmp = cc_list->head;
      while (tmp != NULL)
	{
	  printf(" id: %d\n", tmp->id);
	  printf(" number of pixels: %d\n", tmp->nbpix);
	  printf(" coordinates minimum: ( %d, %d )\n", tmp->coord.xmin,
		 tmp->coord.ymin);
	  printf(" coordinates maximum: ( %d, %d )\n", tmp->coord.xmax,
		 tmp->coord.ymax);
	  if (tmp->chr)
	    printf(" This CC is a character.\n");
	  else
	    printf(" This isn't a character.\n");
	  printf("\n");
	  tmp = tmp->next;
	}
    }
  else
    printf("Empty list\n");
}
