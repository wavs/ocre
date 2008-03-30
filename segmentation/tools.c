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

#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "tools.h"
#include "wrappers.h"

/**
 * This functions initiates a matrix;
 *
 * @return Matrix
 */
t_matrix *initializeEnv()
{
  unsigned int i, j;
  t_matrix *ret;

  ret = wmalloc(sizeof(t_matrix));
  ret->nbrows = 4;
  ret->nbcols = 4;
  ret->data = NULL;
  ret->data = (int **)wmalloc(ret->nbrows * sizeof(int *));
  for (i=0; i < ret->nbrows; ++i)
    ret->data[i] = (int *)wcalloc(ret->nbcols, sizeof(int));

  for (i=0; i < ret->nbrows; ++i)
    for(j=0; j < ret->nbcols; ++j)
      ret->data[i][j] = 1;

  ret->data[2][2] = 1;

  
  return(ret);
}

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
  return(0);
}

/**
 * This function tests if we are under the limits.
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @param limit_x Limit of x coordinate
 * @param limit_y Limit of y coordinate
 *
 * @return 1 if under limits, 0 else
 */
int checkIfUnderLimits(int x, int y, int limit_x, int limit_y)
{
  if (((x+1) >= 0 && (x+1) < limit_x) &&
      ((x-1) >= 0 && (x-1) < limit_x) &&
      (x >= 0 && x < limit_x) &&
      (y >= 0 && y < limit_y) &&
      ((y+1) >= 0 && (y+1) < limit_y))
    return(1);
  else
    return(0);
}

/**
 * This function updates the minimum and the maximum
 * values of the coodinates.
 *
 * @param minmax Structure which stores the min/max coordinates
 * @param x X coordinate
 * @param y Y coordinate
 */
void updateMinMax(t_cc_coordinate *minmax, int x, int y)
{
  /* Update of minimum */
  if (x < minmax->xmin)
    minmax->xmin = x;
  if (y < minmax->ymin)
    minmax->ymin = y;

  /* Update of maximum */
  if (x > minmax->xmax)
    minmax->xmax = x;
  if (y > minmax->ymax)
    minmax->ymax = y;
}

/**
 * This function adds a connected component in
 * a list.
 * 
 * @param elt Connected component
 * @param cc_list List of connected components
 */
t_cc_list *addListCC(t_cc_elt *elt, t_cc_list *cc_list)
{
  t_cc_list *res;

  if (elt != NULL)
    {
      if (cc_list == NULL)
	{
	  printf("A");
	  res = wmalloc(sizeof(t_cc_list));
	  res->head = elt;
	  res->tail = elt;
	  res->nbcc = 1;
	  if (res == NULL)
	    printf("NULL");
	  return(res);
	}
      else
	{
	  printf("B");
	  cc_list->nbcc++;
	  cc_list->tail->next = elt;
	  cc_list->tail = elt;
	  return(cc_list);
	}
    }
  return(NULL);
}

/**
 * This function initializes a matrix of marks.
 *
 * @param height Height of the matrix
 * @param width Width of the matrix
 * 
 * @return Matrix filled with the value 0
 */
char **initMarkMatrix(int height, int width)
{
  int i, j;
  char **ret;

  ret = NULL;
  /* Allocation of memory */
  ret = (char **)wmalloc(height * sizeof(char *));
  for (i=0; i < height; ++i)
    ret[i] = (char *)wcalloc(width, sizeof(char));

  /* Initialization of the matrix */
  for (i=0; i < height; ++i)
    for (j=0; j < width; ++j)
      ret[i][j] = 'o';
 
  return(ret);
}

/**
 * This function adds an element to
 * the queue.
 *
 * @param p_queue Queue
 * @param coord Data stored in the queue
 */
void qEnqueue(t_queue **p_queue, t_coordinate *coord)
{
  t_queue *p_new, *p_tmp;
  
  p_new = wmalloc(sizeof(*p_new));
  if (p_new != NULL)
    {
      p_new->next = NULL;
      p_new->coord = coord;
      if (*p_queue == NULL)
	*p_queue = p_new;
      else
	{
	  p_tmp = *p_queue;
	  while (p_tmp->next != NULL)
	    p_tmp = p_tmp->next;
	  p_tmp->next = p_new;
	}
    }
}


/**
 * This function extracts an element of
 * the queue.
 *
 * @param p_queue Queue
 *
 * @return Data stored in the first element of the queue
 */
t_coordinate *qDequeue(t_queue **p_queue)
{
  t_coordinate *ret;
  t_queue *p_tmp;
  
  ret = NULL;
  if (*p_queue != NULL)
    {
      p_tmp = (*p_queue)->next;
      ret = (*p_queue)->coord;
      wfree((*p_queue)->coord);
      wfree(*p_queue);
      *p_queue = NULL;
      *p_queue = p_tmp;
    }
  return(ret);
}

/**
 * This function deletes the queue.
 *
 * @param p_queue Queue
 */
void qDelete(t_queue **p_queue)
{
  while(*p_queue != NULL)
    qDequeue(p_queue);
}

/**
 * This function returns the value of the
 * first element of the queue. (without destroy).
 *
 * @param p_queue Queue
 *
 * @return Data stored in the first element of the queue
 */
t_coordinate *qQeek(t_queue *p_queue)
{
  t_coordinate *ret;
  
  ret = NULL;
  if (p_queue != NULL)
    ret = p_queue->coord;
  return(ret);
}
