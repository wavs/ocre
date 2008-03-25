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
 * This function computes the vertical projection
 * of a binary matrix.
 *
 * @param pic Binary image
 */
void vertical_projection(t_binary_image *pic)
{
  int i;
  int j;

  pic->vproj = wmalloc(pic->width * sizeof(int));
  for (i=0; i < pic->width; i++)
    {
      pic->vproj[i] = 0;
      for (j=0; j < pic->height; j++)
	{
	  pic->vproj[i] = pic->vproj[i] + pic->data[i][j];
	}
    }
}
