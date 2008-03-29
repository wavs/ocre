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
  if (((x-1) >= 0 && (x+1) < limit_x) &&
      (y >= 0 && (y+1) < limit_y))
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
	  res = (t_cc_list *)wcalloc(1, sizeof(t_cc_list));
	  res->head = elt;
	  res->tail = elt;
	  res->nbcc = 1;
	  return(res);
	}
      else
	{
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
      ret[i][j] = 'x';
 
  return(ret);
}

/**
 * This function gives the precedent
 * element in the queue.
 *
 * @param pp Queue
 */
static void qPrev (t_queue **pp)
{
  if (pp != NULL && *pp != NULL)
    *pp = (*pp)->prev;
}

/**
 * This function allows to move at the
 * beginning of the queue.
 *
 * @param pp Queue
 */
static void qFirst (t_queue **pp)
{
  if (pp != NULL && *pp != NULL)
    while ((*pp)->prev != NULL)
      qPrev(pp);
}

/**
 * This function gives the next element
 * in the queue.
 *
 * @param pp Queue
 */
static void qNext (t_queue **pp)
{
  if (pp != NULL && *pp != NULL)
    *pp = (*pp)->next;
}

/**
 * This function allows to move at the end
 * of the queue.
 *
 * @param pp Queue
 */
static void qLast (t_queue **pp)
{
  if (pp != NULL && *pp != NULL)
    {
      while ((*pp)->next != NULL)
	qNext(pp);
    }
}

/**
 * This function creates an emtpy queue.
 *
 * @return Queue
 */
t_queue *qNew()
{
  return(NULL);
}

/**
 * This function adds an element to
 * the queue.
 *
 * @param pp Queue
 * @param data Data stored in the queue
 */
void qPost (t_queue **pp, void *data)
{
  t_queue *pl, *tmp;
  
  if (pp != NULL)
    {
      pl = NULL;
      tmp = NULL;
      qFirst(pp);
      pl = *pp;
      tmp = wmalloc(sizeof(t_queue));
      tmp->data = data;
      tmp->next = pl;
      tmp->prev = NULL;
      if (pl != NULL)
	pl->prev = tmp;
      *pp = tmp;
    }
}

/**
 * This function extracts an element of
 * the queue.
 *
 * @param pp Queue
 */
void *qGet (t_queue **pp)
{
  void *ret;
  t_queue *pl, *tmp;

  ret = NULL;
  if (pp != NULL && *pp != NULL)
    {
      pl = NULL;
      tmp = NULL;
      qLast(pp);
      pl = *pp;
      if (pl != NULL)
	tmp = pl->prev;
      ret = pl->data;
      wfree(pl);
      if (tmp != NULL)
	tmp->next = NULL;
      *pp = tmp;
    }
  return(ret);
  
}
/**
 * This function deletes the queue.
 *
 * @param pp Queue
 */
void qDelete (t_queue **pp)
{
  if (pp != NULL && *pp != NULL)
    {
      while (*pp != NULL)
	qGet(pp);
    }
}
