/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /extraction
 *   OCRec is the character extraction part of OCRe.
 * About this file: /extraction/tools.c
 *   This file contains some useful functions.
 */

#include "tools.h"
#include "wrappers.h"

/**
 * This function determines if the extension of a
 * filename is ".bmp".
 *
 * @param filename Name of the bitmap file
 */
int is_bmp(char *filename)
{
  int i;

  i = 0;
  while (filename[i] != '\0')
    i++;
  if (i >= 4)
    {
      i--;
      if ((filename[i] == 'p')
	  && (filename[i-1] == 'm')
	  && (filename[i-2] == 'b')
	  && (filename[i-3] == '.'))
	{
	  return 1;
	}
    }
  return 0;
}

/**
 * This function initializes a matrix of marks.
 *
 * @param height Height of the matrix
 * @param width Width of the matrix
 * 
 * @return Matrix filled with the value 0
 */
short int **initMarkMatrix(int height, int width)
{
  int i, j;
  short int **ret;

  /* Allocation of memory */
  ret = wmalloc(height * sizeof(short int));
  for (i=0; i < width; i++)
    ret[i] = wmalloc(height * sizeof(short int));

  /* Initialization of the matrix */
  for (i=0; i < height; i++)
    for (j=0; j < width; j++)
      ret[i][j] = 0;
  
  return(ret);
}

/**
 * QUEUE MANAGER
 */
