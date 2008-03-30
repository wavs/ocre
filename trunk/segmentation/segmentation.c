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
#include "print.h"

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
  unsigned int i;
  int pix_count;
  unsigned int xtmp, ytmp;
  t_coordinate *coord, *res;
  t_cc_coordinate *minmax;
  t_queue **q;

  /* Initialization */
  pix_count = 1;
  q = NULL;
  q = (t_queue **)wcalloc(1, sizeof(t_queue *));
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

      printf("x: %d   y: %d\n",xtmp,ytmp);

      if ((ytmp < matrix->nbrows) && ((xtmp+1) < matrix->nbcols))
	{
	  if ((matrix->data[ytmp][xtmp+1] == 1) && (mark[ytmp][xtmp+1] == 'o'))
	    {
	      printf("A");
	      /* enfiler (i,j) dans q */
	      coord = wmalloc(sizeof(t_coordinate));
	      coord->x = xtmp + 1;
	      coord->y = ytmp;
	      qEnqueue(q, coord);
	      mark[ytmp][xtmp+1] = 'x';
	      /* Update of min,max coordinates */
	      updateMinMax(minmax, (xtmp+1), ytmp);
	      pix_count++;
	    }
	}

      k = xtmp;
      if (xtmp-1 < 0)
	k = 0;
      for (i=k; i <= (xtmp+1); i++)
	{
	  if (((ytmp+1) < matrix->nbrows) && (i < matrix->nbcols) )
	    {
	      if ((matrix->data[ytmp+1][i] == 1) && (mark[ytmp+1][i] == 'o'))
		{
		  printf("R");
		  /* enfiler (i,j) dans q */
		  coord = wmalloc(sizeof(t_coordinate));
		  coord->x = i;
		  coord->y = ytmp + 1;
		  qEnqueue(q, coord);
		  mark[ytmp+1][i] = 'x';
		  /* Update of min,max coordinates */
		  updateMinMax(minmax, i, (ytmp+1));
		  pix_count++;
		}
	    }
	}
 
      /* xtmp, ytmp = defiler (i,j) */
      res = qDequeue(q);
      if (res != NULL)
	{
	  xtmp = res->x;
	  ytmp = res->y;
	}
 
      /*wfree(res);*/
    }
  while (*q != NULL);
  elt->coord = *minmax;
  elt->nbpix = pix_count;
  qDelete(q);
  wfree(q);
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
t_cc_list *makeCC(int i,
		  int j,
		  int cc_count,
		  t_matrix *matrix,
		  char **mark,
		  t_cc_list *cc_list)
{
  t_cc_elt *elt;

  /* Initialization */
  elt = wmalloc(sizeof(t_cc_elt));
  elt->id = cc_count;
  elt->chr = 0;
  elt->next = NULL;

  /* Route of the connected component */
  crossCC(i, j, elt, matrix, mark);

  /* DEBUG */
  printf("\n\n >> CC <<\n");
  printf(" id: %d\n",elt->id);
  printf(" chr: %d\n",elt->chr);
  printf(" nbpix: %d\n",elt->nbpix);
  printf(" (x,y)min: (%d,%d)\n",elt->coord.xmin,elt->coord.ymin);
  printf(" (x,y)max: (%d,%d)\n\n",elt->coord.xmax,elt->coord.ymax);

  /* Update of the linked list */

  if (cc_list == NULL)
    printf("IOPapres");

  return(addListCC(elt, cc_list));

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
  unsigned int i, j ;
  int cc_count;
  t_cc_list *ret,*cc_list;

  /* Initialization */
  mark = initMarkMatrix(matrix->nbrows, matrix->nbcols);
  cc_count = 0;
  cc_list = NULL;

  for (i=0; i < matrix->nbrows; ++i)
    for(j=0; j < matrix->nbcols; ++j)
      {
	/* Creation of connected component */
	if ((matrix->data[i][j]) && (mark[i][j] == 'o'))
	  {
	    mark[i][j] = 'x';
	    cc_count++;
	    ret = makeCC(i, j, cc_count, matrix, mark, ret);
	    if (ret == NULL)
	      printf("DEBUG: il est a NULL");
	  }
	mark[i][j] = 'x';
	
	/* DEBUG 
	printf("\n\n");
	for (k=0; k < matrix->nbrows; k++)
	  {
	    printf("\n");
	    for(o=0; o < matrix->nbcols; o++)
	      printf(" %c",mark[k][o]);
	  }
	printf("\n\n");
	 DEBUG */

      }

  /* Free memory */
  for (i=0; i < matrix->nbrows; i++)
    free(mark[i]);
  free(mark);

  if (ret == NULL)
    printf("IOP");

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
void checkIfCharacter(t_cc_list *cc_list)
{
  int nbpixtot;
  t_cc_elt tmp = wmalloc(sizeof(t_cc_elt));
  tmp = cc_list->head;

  while (tmp <> NULL)
    {
      nbpixtot = (tmp->coord.xmax - tmp->coord.xmin)
        * (tmp->coord.ymax - tmp->coord.ymin);
      tmp = tmp->next;
    }
  free(tmp);
}


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
