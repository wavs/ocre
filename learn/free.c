/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/free.c
 *   This file contains functions which free memory.
 */

#include <stdlib.h>
#include "structures.h"
#include "wrappers.h"

/**
 * This function frees the structure of binary image.
 *
 * @param pic Binary image.
 */
void free_pic(t_binary_image *pic)
{
  int i;

  if (pic != NULL)
    {
      for (i=0; i < pic->matrix->nbrows; i++)
	wfree(pic->matrix->data[i]);
      wfree(pic->matrix->data);
      wfree(pic->matrix);
      wfree(pic->hproj);
      wfree(pic->vproj);
      wfree(pic);
    }
}
