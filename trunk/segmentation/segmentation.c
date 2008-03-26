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

#include "segmentation.h"
#include "structures.h"
#include "tools.h"
#include "wrappers.h"


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
void crossCC(int y, int x, t_cc_elt *elt, int **matrix, short int **mark)
{
  int i, j;
  int pix_count;
  int xtmp, ytmp;
  t_queue q;

  /* Initialization */
  pix_count = 1;
  newQueue(q);
  xtmp = x;
  ytmp = y;

  /* Route of the connected component */
  do
    {
      if ((matrix[ytmp][xtmp+1] == 1) && (mark[ytmp][xtmp+1] == 0))
	{
	  /* enfiler (i,j) dans q */
	  mark[ytmp][xtmp+1] = -1;
	  pix_count++;
	}
      
      for (i=(x-1); i <= (x+1); i++)
	{
	  /* WARNING WE MUST TEST IF IT IS OVER LIMIT */
	  if ((matrix[ytmp+1][i] == 1) && (mark[ytmp+1][i] == 0))
	    {
	      /* enfiler (i,j) dans q */
	      mark[ytmp+1][i] = -1;
	      pix_count++;
	    }
	}
      /* xtmp, ytmp = defiler (i,j) */
    }
  while (q != NULL)
  

  elt->nbpix = pix_count;
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
	    int **matrix,
	    short int **mark,
	    t_cc_list *cc_list)
{
  t_cc_elt *elt;
  t_cc_list *res;

  /* Initialization */
  elt = wmalloc(sizeof(t_cc_elt));
  elt->id = cc_count;
  elt->chr = 0;

  /* Route of the connected component */
  crossCC(i, j, elt, matrix, mark);

  /* Update of the linked list */
  if (cc_list == NULL)
    {
      res = wmalloc(sizeof(t_cc_list));
      res->elt = elt;
      res->next = NULL;
      cc_list = res;
    }
  /* else
     addList(elt, cc_list); */
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
t_cc_list *findCC(int **matrix, int height, int width)
{
  short int **mark;
  int i, j, cc_count;
  t_cc_list *ret;

  /* Initialization */
  mark = initMarkMatrix(height, width);
  cc_count = 0;
  ret = NULL;

  for (i=0; i < height; i++)
    for(j=0; j < width; j++)
      {
	/* Creation of connected component */
	if ((matrix[i][j]) && (mark[i][j] == 0))
	  {
	    mark[i][j] = -1;
	    cc_count++;
	    makeCC(i, j, cc_count, matrix, mark, ret);
	  }
	mark[i][j] = -1;
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
t_block_list *makeBlocks(t_cc_list *cc_list)
{
  /* FIXME */
  return(NULL);
}

/**
 * This function checks if the connected components
 * represent a character.
 *
 * @param cc_list Linked list of connected components
 */
void checkIfCharacter(t_cc_list *cc_list)
{
  /* FIXME */
}

/**
 * This function detects the type of blocks
 * (text, image, ...)
 * 
 * @param block_list Linked list of blocks
 */
void detectTypeOfBlocks(t_block_list *block_list)
{
  /* FIXME */
}

/**
 * This function traces all the blocks with boxes
 * in an output image.
 *
 * @param block_list Linked list of blocks
 * @param limit Margins of the input image.
 */
void traceBlocks(t_block_list *block_list, t_limit *limit)
{
  /* FIXME */
}
