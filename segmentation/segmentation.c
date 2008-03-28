/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/structures.h
 *   This file contains declarations of all structures
 *   about the extraction.
 */

#include <stdio.h>
#include <stdlib.h>
#include "wrappers.h"
#include "structures.h"
#include "segmentation.h"
#include "tools.h"

/**
 * This function crosses a connected component
 * and calculates the number of black boxes.
 *
 * @param i Current y coordinate
 * @param j Current x coordinate
 * @param matrix Binary matrix
 * @param mark Matrix of marks
 *
 * @return Number of black boxes
 */
void crossCC(int y, int x, t_cc_elt *elt, t_matrix *matrix, char **mark)
{
  int i;
  int pix_count;
  int xtmp, ytmp;
  t_coordinate *coord, *res;
  t_cc_coordinate *minmax;
  t_queue **q;

  /* Initialization */
  pix_count = 1;
  qNew(q);
  xtmp = x;
  ytmp = y;
  minmax = wcalloc(1, sizeof(t_cc_coordinate));
  minmax->xmin = x;
  minmax->xmax = x;
  minmax->ymin = y;
  minmax->ymax = y;

  /* Route of the connected component */
  do
    {
      if (checkIfUnderLimits(xtmp, ytmp, matrix->nbcols, matrix->nbrows))
	{
	  if ((matrix->data[ytmp][xtmp+1] == 1) && (mark[ytmp][xtmp+1] == 'o'))
	    {
	      /* enfiler (i,j) dans q */
	      coord = wcalloc(1, sizeof(t_coordinate));
	      coord->x = xtmp + 1;
	      coord->y = ytmp;
	      qPost(q, coord);
	      mark[ytmp][xtmp+1] = 'x';
	      /* Update of min,max coordinates */
	      updateMinMax(minmax, (xtmp+1), ytmp);
	      pix_count++;
	    }
	  
	  for (i=(xtmp-1); i <= (xtmp+1); ++i)
	    {
	      /* WARNING WE MUST TEST IF IT IS OVER LIMIT */
	      if ((matrix->data[ytmp+1][i] == 1) && (mark[ytmp+1][i] == 'o'))
		{
		  /* enfiler (i,j) dans q */
		  coord = wcalloc(1, sizeof(t_coordinate));
		  coord->x = i;
		  coord->y = ytmp + 1;
		  qPost(q, coord);
		  mark[ytmp+1][i] = 'x';
		  /* Update of min,max coordinates */
		  updateMinMax(minmax, i, (ytmp+1));
		  pix_count++;
		}
	    }
	  /* xtmp, ytmp = defiler (i,j) */
	  res = qGet(q);
	  xtmp = res->x;
	  ytmp = res->y;
	  wfree(res);
	}
      else
	{
	  printf("Matrix error: Out of range\n Process aborted.\n");
	  exit(EXIT_FAILURE);
	}
    }
      while (q != NULL);
  elt->nbpix = pix_count;
  qDelete(q);
}

/**
 * This function create a connected component.
 *
 * @param i Current y coordinate
 * @param j Current x coordinate
 * @param cc_count Number of the connected component
 * @param matrix Binary matrix
 * @param mark Matrix of marks
 * @param cc_list Linked list of connected components
 */
void makeCC(int i,
	    int j,
	    int cc_count,
	    t_matrix *matrix,
	    char **mark,
	    t_cc_list *cc_list)
{
  t_cc_elt *elt;

  /* Initialization */
  elt = wcalloc(1, sizeof(t_cc_elt));
  elt->id = cc_count;
  elt->chr = 0;
  elt->next = NULL;

  /* Route of the connected component */
  crossCC(i, j, elt, matrix, mark);

  /* Update of the linked list */
  addListCC(elt, cc_list);
}

/**
 * This function finds all the connected components of
 * the matrix.
 *
 * @param matrix Binary matrix
 * @param height Height of the matrix
 * @param width Width of the matrix
 *
 * @return Linked list of connected components
 */
t_cc_list *findCC(t_matrix *matrix)
{
  char **mark;
  unsigned int i, j;
  int cc_count;
  t_cc_list *ret;

  /* Initialization */
  mark = initMarkMatrix(matrix->nbrows, matrix->nbcols);
  cc_count = 0;
  ret = NULL;

  for (i=0; i < matrix->nbrows; ++i)
    for(j=0; j < matrix->nbcols; ++j)
      {
	/* Creation of connected component */
	if ((matrix->data[i][j]) && (mark[i][j] == 'o'))
	  {
	    mark[i][j] = 'x';
	    cc_count++;
	    makeCC(i, j, cc_count, matrix, mark, ret);
	  }
	mark[i][j] = 'x';
      }
  return(ret);
}

/**
 * This function creates all the blocks according to
 * the list of connected components.
 *
 * @param cc_list Linked list of connected components
 * 
 * @return Linked list of blocks
 */
/*t_block_list *makeBlocks(t_cc_list *cc_list)
{
  // FIXME
  return(NULL);
}
*/

/**
 * This function checks if the connected components
 * represent a character.
 *
 * @param cc_list Linked list of connected components
 */
/*void checkIfCharacter(t_cc_list *cc_list)
{
  // FIXME
}
*/

/**
 * This function detects the type of blocks
 * (text, image, ...)
 * 
 * @param block_list Linked list of blocks
 */
/*void detectTypeOfBlocks(t_block_list *block_list)
{
  // FIXME
}
*/

/**
 * This function traces all the blocks with boxes
 * in an output image.
 *
 * @param block_list Linked list of blocks
 * @param limit Margins of the input image.
 */
/*void traceBlocks(t_block_list *block_list, t_limit *limit)
{
  // FIXME
}
*/
