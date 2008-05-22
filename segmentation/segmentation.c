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
  int id = 0; int hchar, wchar, disty, hmoy, seuil_hmoy, nbcc;
  t_block_list *blocklist, *headlist;
  t_block_elt *block; t_cc_list *tmplist; t_cc_elt *tmp;

  blocklist = wmalloc(sizeof(t_block_list));
  block = wmalloc(sizeof(t_block_elt));
  tmplist = wmalloc(sizeof(t_cc_list));
  blocklist->elt = block; headlist = blocklist;
  tmp = cc_list->head; nbcc = 1;

  while (tmp != NULL)
    { if (tmp->chr == 0)
        { tmplist->head = tmp; tmplist->tail = tmp;
          block = create_block(id, tmplist, 1,
                               tmp->coord.xmin, tmp->coord.xmax,
                               tmp->coord.ymin, tmp->coord.ymax, 2); }
      else
        { tmplist->head = tmp; do
            { hchar = tmp->coord.xmax - tmp->coord.xmin;
              wchar = tmp->coord.ymax - tmp->coord.ymin;
	      if (tmp->next != NULL)
		disty = tmp->next->coord.ymin - tmp->coord.ymax;
	      else disty = wchar;
              hmoy = ( hchar + (tmp->next->coord.xmax
                                - tmp->next->coord.xmin))/2;
              seuil_hmoy = 0.2*hchar; nbcc++; tmp = tmp->next; }
          while (((hmoy < seuil_hmoy) /* diff de hauteur entre 2 lettres  */
                  || ( (hmoy > hchar*0.8) && (hmoy < hchar*1.2) )) /* diff de hauteur entre 2 lignes */
                 && (disty < (wchar/2))
		 && (tmp->next != NULL)); /* distance entre 2 lettres */
          tmplist->tail = tmp;
          block = create_block (id, tmplist, nbcc,
                                tmplist->head->coord.xmin,
                                tmplist->head->coord.xmax,
                                tmplist->head->coord.ymin,
                                tmplist->head->coord.ymax, 1); }
      tmplist = wmalloc(sizeof(t_cc_list));
      if (tmp->next != NULL) tmp = tmp->next;
      blocklist->elt = block; blocklist->elt = block;
      blocklist = blocklist->next; id++; nbcc = 1; }
  return(headlist);
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
 * This function traces all the words with boxes
 * in an output image.
 *
 * @param image SDL surface
 * @param word_list Linked list of words
 */
void traceWords(SDL_Surface *image, t_word_list *word_list)
{
  t_word_elt *tmp;
  Uint32 cl;
  int width, height;

  cl = SDL_MapRGB(image->format, 0xdd, 0x53, 0x00);
  if (word_list != NULL)
    {
      tmp = word_list->head;
      while (tmp != NULL)
	{
	  width = tmp->coord.xmax - tmp->coord.xmin;
	  height = tmp->coord.ymax - tmp->coord.ymin;

	  draw_line(tmp->coord.xmin, tmp->coord.ymin, width, 1, cl, image);
	  draw_line(tmp->coord.xmin, tmp->coord.ymax, width, 1, cl, image);
	  draw_line(tmp->coord.xmin, tmp->coord.ymin, 1, height, cl, image);
	  draw_line(tmp->coord.xmax, tmp->coord.ymin, 1, height, cl, image);

	  tmp = tmp->next;
	}
    }
}

/**
 * This function creates a list of words with the list of connected components.
 *
 * @param cc_list Linked list of connected components
 *
 * @return Linked list of words
 */
t_word_list *makeWords(t_cc_list *cc_list)
{
  t_word_list *ret;
  t_word_elt *tmpword;
  t_cc_elt *tmp, *next;

  /* Initialization */
  ret = NULL;
  tmp = cc_list->head;

  while (tmp != NULL)
    {

      if (tmp->chr)
	{
	  tmpword = wmalloc(sizeof(t_word_elt));
	  tmpword->coord.xmin = tmp->coord.xmin;
	  tmpword->coord.xmax = tmp->coord.xmax;
	  tmpword->coord.ymin = tmp->coord.ymin;
	  tmpword->coord.ymax = tmp->coord.ymax;
	  tmpword->cclist = NULL;
	  tmpword->next = NULL;
	  do
	    {
	      tmpword->cclist = addListCC(tmp, tmpword->cclist);
	      updateBoxCoord(tmpword, tmp);
	      next = tmp->next;
	      tmp->next = NULL;
	      tmp = next;
	    }
	  while ((tmp != NULL) && (isInWord(tmp, tmpword)) && (tmp->chr));
	  ret = addListWord(tmpword, ret);
	}
      else
	tmp = tmp->next;
    }
  return(ret);
}

/**
 * This function traces all the lines with boxes
 * in an output image.
 *
 * @param image SDL surface
 * @param line_list Linked list of lines
 */
void traceLines(SDL_Surface *image, t_line_list *line_list)
{
  t_line_elt *tmp;
  Uint32 cl;
  int width, height;

  cl = SDL_MapRGB(image->format, 0x00, 0x53, 0xdd);
  if (line_list != NULL)
    {
      tmp = line_list->head;
      while (tmp != NULL)
	{
	  width = tmp->coord.xmax - tmp->coord.xmin;
	  height = tmp->coord.ymax - tmp->coord.ymin;

	  draw_line(tmp->coord.xmin, tmp->coord.ymin, width, 1, cl, image);
	  draw_line(tmp->coord.xmin, tmp->coord.ymax, width, 1, cl, image);
	  draw_line(tmp->coord.xmin, tmp->coord.ymin, 1, height, cl, image);
	  draw_line(tmp->coord.xmax, tmp->coord.ymin, 1, height, cl, image);

	  tmp = tmp->next;
	}
    }
}

/**
 * This function creates a list of lines with the list of connected components.
 *
 * @param cc_list Linked list of connected components
 *
 * @return t_line_list Linked list of lines
 */
t_line_list *makeLines(t_word_list *word_list)
{
  t_line_list *ret;
  t_line_elt *tmpline;
  t_word_elt *tmp, *next;

  ret = NULL;
  tmp = word_list->head;

  while (tmp != NULL)
    {
      tmpline = wmalloc(sizeof(t_line_elt));
      tmpline->coord.xmin = tmp->coord.xmin;
      tmpline->coord.xmax = tmp->coord.xmax;
      tmpline->coord.ymin = tmp->coord.ymin;
      tmpline->coord.ymax = tmp->coord.ymax;
      tmpline->wordlist = NULL;
      tmpline->next = NULL;
      do
	{
	  tmpline->wordlist = addListWord(tmp, tmpline->wordlist);
	  updateBoxCoordLine(tmpline, tmp);
	  next = tmp->next;
	  tmp->next = NULL;
	  tmp = next;
	}
      while ((tmp != NULL) && (isInLine(tmp, tmpline)));
      ret = addListLine(tmpline, ret);
    }
  return(ret);
}









/*************************************************************/

/**
 * This function traces all the paragraphes with boxes
 * in an output image.
 *
 * @param image SDL surface
 * @param paragraph_list Linked list of paragraphes
 */
void traceParagraphes(SDL_Surface *image, t_paragraph_list *paragraph_list)
{
  t_paragraph_elt *tmp;
  Uint32 cl;
  int width, height;

  cl = SDL_MapRGB(image->format, 0x00, 0xdd, 0x53);
  if (paragraph_list != NULL)
    {
      tmp = paragraph_list->head;
      while (tmp != NULL)
	{
	  width = tmp->coord.xmax - tmp->coord.xmin;
	  height = tmp->coord.ymax - tmp->coord.ymin;

	  draw_line(tmp->coord.xmin, tmp->coord.ymin, width, 1, cl, image);
	  draw_line(tmp->coord.xmin, tmp->coord.ymax, width, 1, cl, image);
	  draw_line(tmp->coord.xmin, tmp->coord.ymin, 1, height, cl, image);
	  draw_line(tmp->coord.xmax, tmp->coord.ymin, 1, height, cl, image);

	  tmp = tmp->next;
	}
    }
}

/**
 * This function creates a list of paragraphes with the list of lines.
 *
 * @param line_list Linked list of lines
 *
 * @return t_paragraph_list Linked list of paragraphes
 */
t_paragraph_list *makeParagraphes(t_line_list *line_list)
{
  t_paragraph_list *ret;
  t_paragraph_elt *tmppara;
  t_line_elt *tmp, *next;

  ret = NULL;
  tmp = line_list->head;

  while (tmp != NULL)
    {
      tmppara = wmalloc(sizeof(t_paragraph_elt));
      tmppara->coord.xmin = tmp->coord.xmin;
      tmppara->coord.xmax = tmp->coord.xmax;
      tmppara->coord.ymin = tmp->coord.ymin;
      tmppara->coord.ymax = tmp->coord.ymax;
      tmppara->linelist = NULL;
      tmppara->next = NULL;
      do
	{
	  tmppara->linelist = addListLine(tmp, tmppara->linelist);
	  updateBoxCoordParagraph(tmppara, tmp);
	  next = tmp->next;
	  tmp->next = NULL;
	  tmp = next;
	}
      while ((tmp != NULL) && (isInParagraph(tmp, tmppara)));
      ret = addListParagraph(tmppara, ret);
    }
  return(ret);
}
