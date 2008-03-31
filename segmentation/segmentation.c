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
  int i, j, kmin, kmax, pmin, pmax, first;
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
  first = 1;

  /* Route of the connected component */
  do
    {
      /* xtmp, ytmp = defiler (i,j) */
      if (!first)
	{
	  res = qDequeue(q);
	  if (res != NULL)
	    {
	      xtmp = res->x;
	      ytmp = res->y;
	    }
	  /*if (*q == NULL)
	    printf("La file est vide\n");*/
	}
      
      /*printf("x: %d   y: %d\n",xtmp,ytmp);
	printf("je repasse la \n"); */
      kmin = ytmp-1;
      if (kmin < 0)
	kmin = 0;
      kmax = ytmp+1;
      if (kmax >= matrix->nbrows)
	kmax = matrix->nbrows - 1;
      for (i=kmin; i <= kmax; i++)
	{
	  pmin = xtmp-1;
	  if (pmin < 0)
	    pmin = 0;
	  pmax = xtmp+1;
	  if (pmax >= matrix->nbcols)
	    pmax = matrix->nbcols - 1;
	  for (j=pmin; j <= pmax; j++)
	    {
	     
	      /* printf("\n >> Test de la case (%d,%d)\n", j, i); */
	      if ((matrix->data[i][j] == 1) && (mark[i][j] == 'o'))
		{
		  coord = wmalloc(sizeof(t_coordinate));
		  coord->x = j;
		  coord->y = i;
		  /*if (*q == NULL)
		    printf("Cest ici que la file est vide avant.\n");*/
		  qEnqueue(q, coord);
		  /*if (*q == NULL)
		  printf("Cest ici que la file est vide apres.\n");*/
		  mark[i][j] = 'x';
		  updateMinMax(minmax, j, i);
		  pix_count++;
		}
	    }
	}
      first = 0;
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
  /*printf("\n\n >> CC <<\n");
  printf(" id: %d\n",elt->id);
  printf(" chr: %d\n",elt->chr);
  printf(" nbpix: %d\n",elt->nbpix);
  printf(" (x,y)min: (%d,%d)\n",elt->coord.xmin,elt->coord.ymin);
  printf(" (x,y)max: (%d,%d)\n\n",elt->coord.xmax,elt->coord.ymax);
  */
  /* Update of the linked list */

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

  return(ret);
}


t_block_elt *create_block(int id, t_cc_list *cclist,
                          int nbcc, int xmin, int xmax,
                          int ymin, int ymax, int type)
{
  t_block_elt *block;
  block = wmalloc(sizeof(t_block_elt));

  block->id = id;
  block->cclist = cclist;
  block->nbcc = nbcc;
  block->posx = xmin;
  block->posy = ymin;
  block->height = ymax - ymin;
  block->width = xmax - xmin;
  block->type = type;

  return block;
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
  int id = 0;
  int hchar, wchar, disty, hmoy, seuil_hmoy, nbcc;
  t_block_list *blocklist, *headlist;
  t_block_elt *block;
  t_cc_list *tmplist;
  t_cc_elt *tmp;

  blocklist = wmalloc(sizeof(t_block_list));
  block = wmalloc(sizeof(t_block_elt));
  tmplist = wmalloc(sizeof(t_cc_list));
  blocklist->elt = block;
  headlist = blocklist;
  tmp = cc_list->head;
  nbcc = 1;

  while (tmp != NULL)
    {
      if (tmp->chr == 0)
        {
          tmplist->head = tmp;
          tmplist->tail = tmp;
          block = create_block(id, tmplist, 1,
                               tmp->coord.xmin, tmp->coord.xmax,
                               tmp->coord.ymin, tmp->coord.ymax, 2);
        }
      else
        {
	  tmplist->head = tmp;
          do
            {
              hchar = tmp->coord.xmax - tmp->coord.xmin;
              wchar = tmp->coord.ymax - tmp->coord.ymin;
	      if (tmp->next != NULL)
		disty = tmp->next->coord.ymin - tmp->coord.ymax;
	      else
		disty = wchar;
              hmoy = ( hchar + (tmp->next->coord.xmax
                                - tmp->next->coord.xmin))/2;
              seuil_hmoy = 0.2*hchar;
              nbcc++;
              tmp = tmp->next;
            }
          while (((hmoy < seuil_hmoy) /* diff de hauteur entre 2 lettres  */
                  || ( (hmoy > hchar*0.8) && (hmoy < hchar*1.2) )) /* diff de hauteur entre 2 lignes */
                 && (disty < (wchar/2))
		 && (tmp->next != NULL)); /* distance entre 2 lettres */
          tmplist->tail = tmp;
          block = create_block (id, tmplist, nbcc,
                                tmplist->head->coord.xmin,
                                tmplist->head->coord.xmax,
                                tmplist->head->coord.ymin,
                                tmplist->head->coord.ymax, 1);
        }
      tmplist = wmalloc(sizeof(t_cc_list));
      if (tmp->next != NULL)
	tmp = tmp->next;
      blocklist->elt = block;
      blocklist->elt = block;
      blocklist = blocklist->next;
      id++;
      nbcc = 1;
    }
  return(headlist);
}


/**
 * This function checks if the connected components
 * represent a character.
 *
 * @param cc_list Linked list of connected components
 */
void checkIfCharacter(t_cc_list *cc_list)
{
  int nbpixtot, height, width;
  float seuil = 1.6;
  t_cc_elt* tmp;
  tmp = wmalloc(sizeof(t_cc_elt));
  tmp = cc_list->head;

  while (tmp != NULL)
    {
      width = tmp->coord.xmax - tmp->coord.xmin;
      height = tmp->coord.ymax - tmp->coord.ymin;
      nbpixtot = height * width;
      if ((tmp->nbpix < seuil*nbpixtot)
          && (width < 2*height))
        {
          tmp->chr = 1;
        }
      tmp = tmp->next;
    }
  wfree(tmp);
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
 * This function traces all the CC with boxes
 * in an output image.
 *
 * @param block_list Linked list of blocks
 * @param limit Margins of the input image.
 */
void traceCC(t_cc_list *cc_list, t_limit *limit)
{
  // FIXME
}


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
