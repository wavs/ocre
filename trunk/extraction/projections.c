/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developep by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /extraction
 *   This folder contains the character extraction part of OCRe.
 * About this file: /extraction/projections.c
 *   This file contains functions about the projection of pixels.
 */

#include <stdlib.h>
#include "structures.h"
#include "wrappers.h"

/**
 * This function returns a pointer on an int vector which
 * contains the horizontal projection of the picture.
 * @param pic Binary image.
 */
void horizontal_projection(t_binary_image *pic)
{
  int i;
  int j;

  pic->hproj = wmalloc(pic->height * sizeof(int));
  for (i=0; i < pic->height; i++)
    {
      pic->hproj[i] = 0;
      for (j=0; j < pic->width; j++)
	{
	  pic->hproj[i] = pic->hproj[i] + pic->data[j][i];
	}
    }
}

/**
 * This function returns a pointer on an int vector which
 * contains the vertical projection of the picture.
 * @param linelist Set of extracted lines.
 */
void vertical_projection(t_binary_image *pic,
			 t_line_set *line,
			 int *vproj)
{
  int i;
  int j;

  vproj = wmalloc(pic->width * sizeof(int));
  for (i=0; i < pic->width; i++)
    {
      vproj[i] = 0;
      for (j=line->pos; j < (line->pos + line->height); j++)
	{
	  vproj[i] = vproj[i] + pic->data[i][j];
	}
    }
}

