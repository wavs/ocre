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
#include <math.h>
#include "wrappers.h"
#include "structures.h"
#include "tools.h"
#include "segmentation.h"
#include "print.h"
#include "graphics.h"
#include "SDL/SDL.h"

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
void crossCC(int y,
	     int x,
	     t_cc_elt *elt,
	     t_matrix *matrix,
	     char **mark)
{
  int i, j, kmin, kmax, pmin, pmax, first; int pix_count;
  int xtmp, ytmp; t_coordinate *coord, *res;
  t_box_coordinate *minmax; t_queue **q;
  pix_count = 1;
  q = NULL;
  q = (t_queue **)wcalloc(1, sizeof(t_queue *));
  xtmp = x; ytmp = y;
  minmax = wcalloc(1, sizeof(t_box_coordinate));
  minmax->xmin = x; minmax->xmax = x;
  minmax->ymin = y; minmax->ymax = y; first = 1;
  do
    { if (!first)
	{ res = qDequeue(q);
	  if (res != NULL)
	    { xtmp = res->x;
	      ytmp = res->y; } }
      kmin = ytmp-1;
      if (kmin < 0) kmin = 0;
      kmax = ytmp+1;
      if (kmax >= matrix->nbrows) kmax = matrix->nbrows - 1;
      for (i=kmin; i <= kmax; i++)
	{ pmin = xtmp-1;
	  if (pmin < 0) pmin = 0;
	  pmax = xtmp+1;
	  if (pmax >= matrix->nbcols) pmax = matrix->nbcols - 1;
	  for (j=pmin; j <= pmax; j++)
	    { if ((matrix->data[i][j] == 1) && (mark[i][j] == 'o'))
		{ coord = wmalloc(sizeof(t_coordinate));
		  coord->x = j;
		  coord->y = i;
		  qEnqueue(q, coord);
		  mark[i][j] = 'x';
		  updateMinMax(minmax, j, i);
		  pix_count++; } } }
      first = 0; }
  while (*q != NULL);
  elt->coord = *minmax; elt->nbpix = pix_count; qDelete(q); wfree(q);
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

  /* Update of the linked list */
  return(addListCCsort(elt, cc_list));

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
  int i, j ;
  int cc_count;
  t_cc_list *ret,*cc_list;

  /* Initialization */
  mark = initMarkMatrix(matrix->nbrows, matrix->nbcols);
  cc_count = 0;
  cc_list = NULL;
  ret = NULL;

  for (i=0; i < matrix->nbrows; ++i)
    for(j=0; j < matrix->nbcols; ++j)
      {
	/* Creation of connected component */
	if ((matrix->data[i][j]) && (mark[i][j] == 'o'))
	  {
	    mark[i][j] = 'x';
	    cc_count++;
	    ret = makeCC(i, j, cc_count, matrix, mark, ret);
	  }
	mark[i][j] = 'x';
      }

  /* Free memory */
  for (i=0; i < matrix->nbrows; i++)
    free(mark[i]);
  free(mark);

  return(ret);
}

/**
 * This function checks if the connected components
 * represent a character.
 *
 * @param cc_list Linked list of connected components
 */
void checkIfCharacter(t_cc_list *cc_list, int height, int width)
{
  int nbpixtot, h, w;
  float seuil = 1.6;
  t_cc_elt* tmp;
  tmp = wmalloc(sizeof(t_cc_elt));
  tmp = cc_list->head;

  while (tmp != NULL)
    {
      w = tmp->coord.xmax - tmp->coord.xmin;
      h = tmp->coord.ymax - tmp->coord.ymin;
      nbpixtot = h * w;
      if ((tmp->nbpix < seuil*nbpixtot)
          && (w < 2.5*h)
          && (w < 0.1*width)
          && (h < 0.1*height))
        {
          tmp->chr = 1;
        }
      tmp = tmp->next;
    }
  wfree(tmp);
}

/**
 * This function traces all the words with boxes
 * in an output image.
 *
 * @param image SDL surface
 * @param cc_list Linked list of connected components
 */
void traceCC(SDL_Surface *image, t_cc_list *cc_list)
{
  t_cc_elt *tmp;
  Uint32 cl;
  int width, height;

  cl = SDL_MapRGB(image->format, 0x00, 0x53, 0xdd);
  if (cc_list != NULL)
    {
      tmp = cc_list->head;
      while (tmp != NULL)
	{
	  width = tmp->coord.xmax - tmp->coord.xmin;
	  height = tmp->coord.ymax - tmp->coord.ymin;

	  if (tmp->chr)
	    {
	      draw_line(tmp->coord.xmin, tmp->coord.ymin, width, 1, cl, image);
	      draw_line(tmp->coord.xmin, tmp->coord.ymax, width, 1, cl, image);
	      draw_line(tmp->coord.xmin, tmp->coord.ymin, 1, height, cl, image);
	      draw_line(tmp->coord.xmax, tmp->coord.ymin, 1, height, cl, image);
	    }
	  
	  tmp = tmp->next;
	}
    }
}


/**
 * This function updates the coordinates of the
 * connected components 
 */
void updateCC(t_cc_list *cc_list)
{
  int ymin, ymax;
  t_cc_elt *tmp;

  /* Search of the min,max coordinate */
  tmp = cc_list->head;
  ymin = tmp->coord.ymin;
  ymax = tmp->coord.ymax;
  while (tmp != NULL)
    {
      /* Search of minimum */
      if(ymin > tmp->coord.ymin)
	ymin = tmp->coord.ymin;
      /* Search of maximum */
      if (ymax < tmp->coord.ymax)
	ymax = tmp->coord.ymax;
      tmp = tmp->next;
    }
  
  /* Update of connected components */
  tmp = cc_list->head;
  while (tmp != NULL)
    {
      /* Update of minimum */
      tmp->coord.ymin = ymin;
      /* update of maximum */
      tmp->coord.ymax = ymax;
      tmp = tmp->next;
    }
}

/**
 * This function resizes a matrix.
 */
t_matrix *resizeMatrix(t_matrix *mat, t_cc_elt *cc, t_binary_image *pic)
{
  int height_cc, width_cc;
  int i, j, itmp, jtmp;
  t_matrix *ccmat;
  float percent;

  /* Search of cc informations */
  height_cc = cc->coord.ymax - cc->coord.ymin;
  width_cc = cc->coord.xmax - cc->coord.xmin;
  
  /* Creation of the unresized cc matrix */
  ccmat = wmalloc(sizeof(t_matrix));
  ccmat->nbrows = height_cc;
  ccmat->nbcols = width_cc;
  ccmat->data= NULL;
  ccmat->data = (int **)wmalloc(height_cc * sizeof(int *));
  for (i=0; i < height_cc; ++i)
    ccmat->data[i] = (int *)wcalloc(width_cc, sizeof(int));
  for (i=0; i < height_cc; ++i)
    for (j=0; j < width_cc; ++j)
      {
	itmp = i + cc->coord.ymin;
	jtmp = j + cc->coord.xmin;
	ccmat->data[i][j] = pic->matrix->data[itmp][jtmp];
      }
  
  if (height_cc > width_cc)
    percent = 10 / height_cc;
  else
    percent = 10 / width_cc;

  for (i=0; i < 10; ++i)
    for (j=0; j < 10; ++j)
      {
	itmp = trunc(i / percent);
	jtmp = trunc(j / percent);
	if (checkIfUnderLimits(itmp, jtmp, width_cc, height_cc))
	  mat->data[i][j] = ccmat->data[itmp][jtmp];
	else
	  mat->data[i][j] = 0;
      }
  

  return(mat);
}

/**
 * This function returns a resized matrix (10x10)  for the cc.
 *
 * @param cc Connected component
 * @param pic Binary image
 *
 * @return Matrix 10x10
 */
t_matrix *resizeCC(t_cc_elt *cc, t_binary_image *pic)
{
  int i, j, itmp, jtmp;
  t_matrix *ret;
  int height_cc, width_cc;

  /* Initialization */
  ret = wmalloc(sizeof(t_matrix));
  ret->nbrows = 10;
  ret->nbcols = 10;
  ret->data= NULL;
  ret->data = (int **)wmalloc(10 * sizeof(int *));
  for (i=0; i < 10; ++i)
    ret->data[i] = (int *)wcalloc(10, sizeof(int));
  for (i=0; i < 10; ++i)
    for (j=0; j < 10; ++j)
      ret->data[i][j] = 0;
  
  /* Search of cc informations */
  height_cc = cc->coord.ymax - cc->coord.ymin;
  width_cc = cc->coord.xmax - cc->coord.xmin;

  if ((height_cc <= 10) && (width_cc <= 10))
    {
      /* Just a rewrite of the cc matrix */
      for (i=0; i < height_cc; ++i)
	for (j=0; j < width_cc; ++j)
	  {
	    itmp = i + cc->coord.ymin;
	    jtmp = j + cc->coord.xmin;
	    ret->data[i][j] = pic->matrix->data[itmp][jtmp];
	  }
    }
  else
    ret = resizeMatrix(ret, cc, pic);

  return(ret);
}

/**
 * This function writes a txt file with the list of cc.
 *
 * @param cc_list Linked list of connected component
 */
void exportCC(t_cc_list *cc_list, t_binary_image *pic)
{
  int i, j;
  t_cc_elt *tmp;
  t_matrix *tmpmat;
  FILE *file;

  file = NULL;
  if ((file = fopen("learn_export.txt", "w+")) != NULL)
    {
      tmp = cc_list->head;
      while (tmp != NULL)
	{
	  tmpmat = resizeCC(tmp, pic);

	  for (i=0; i < tmpmat->nbrows; ++i)
	    {
	      for (j=0; j < tmpmat->nbcols; ++j)
		{
		  if (tmpmat->data[i][j] == 1)
		    fputc('1', file);
		  else
		    fputc('0', file);
		}
	    }
	  fputc('\n', file);
	  
	  tmp = tmp->next;
	}
      fclose(file);
    }
  else
    printf(" > Can't create/open the file sorry :( <\n");
}


      

      
