/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developep by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   This folder contains the character extraction part of OCRe.
 * About this file: /segmentation/projections.c
 *   This file contains functions about the projection of pixels.
 */

#include "structures.h"
#include "wrappers.h"

/**
 * This function computes the horizontal projection
 *  of a binary matrix.
 *
 * @param pic Binary image
 */
void horizontal_projection(t_binary_image *pic)
{
  unsigned int i,j;

  pic->hproj = (int *)wcalloc(pic->matrix->nbrows, sizeof(int));
  for (i=0; i < pic->matrix->nbrows; ++i)
    {
      pic->hproj[i] = 0;
      for (j=0; j < pic->matrix->nbcols; ++j)
	{
	  pic->hproj[i] = pic->hproj[i] + pic->matrix->data[i][j];
	}
    }
}

/**
 * This function computes the vertical projection
 * of a binary matrix.
 *
 * @param pic Binary image
 */
void vertical_projection(t_binary_image *pic)
{
  unsigned int i,j;

  pic->vproj = (int*)wcalloc(pic->matrix->nbcols, sizeof(int));
  for (i=0; i < pic->matrix->nbcols; ++i)
    {
      pic->vproj[i] = 0;
      for (j=0; j < pic->matrix->nbrows; ++j)
	{
	  pic->vproj[i] = pic->vproj[i] + pic->matrix->data[j][i];
	}
    }
}
