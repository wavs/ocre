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
  int i, j;
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
      ret->data[i][j] = 0;

      ret->data[3][0] = 1;
      ret->data[3][1] = 1;
      ret->data[3][2] = 1;
      ret->data[3][3] = 1;

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
void updateMinMax(t_box_coordinate *minmax, int x, int y)
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

/**
 * This function determines if a connected component is in
 * a word.
 *
 * @param cc Connected component
 * @param word Word
 *
 * @return True if >0
 */
int isInWord(t_cc_elt *cc, t_word_elt *word)
{
  int ymed_word, ymed_cc, deltav, deltah;
  int word_height, cc_width;

  if (cc == NULL || word == NULL)
    return(0);

  word_height = word->coord.ymax - word->coord.ymin;
  cc_width = cc->coord.xmax - cc->coord.xmin;

  ymed_word = (word->coord.ymin + word->coord.ymax) / 2;
  ymed_cc = (cc->coord.ymin + cc->coord.ymax) / 2;
 
  deltav = abs(ymed_cc - ymed_word);
  deltah = abs(cc->coord.xmin - word->coord.xmax);

  if ((deltav < (word_height)) && (deltah < word_height / 2))    /* cc_width */
    return(1);
  return(0);
}

/**
 * This function determines if a word is in
 * a line.
 *
 * @param word Word
 * @param line Line
 *
 * @return True if >0
 */
int isInLine(t_word_elt *word, t_line_elt *line)
{
  int ymed_word, ymed_line, deltav, deltah;
  int line_height;

  if (word == NULL || line == NULL)
    return(0);

  line_height = line->coord.ymax - line->coord.ymin;

  ymed_word = (word->coord.ymin + word->coord.ymax) / 2;
  ymed_line = (line->coord.ymin + line->coord.ymax) / 2;
 
  deltav = abs(ymed_word - ymed_line);
  deltah = abs(word->coord.xmin - line->coord.xmax);

  if ((deltav) < (line_height)) /* && (deltah < line_height)) */
    return(1);
  return(0);
}

/**
 * This function determines if a line is in
 * a paragraph.
 *
 * @param line Line
 * @param para Paragraph
 *
 * @return True if >0
 */
int isInParagraph(t_line_elt *line, t_paragraph_elt *para)
{
  int deltav, line_height;

  if (line == NULL || para == NULL)
    return(0);

  line_height = line->coord.ymax - line->coord.ymin;
  deltav = abs(line->coord.ymin - para->coord.ymax);

  if (deltav < line_height)
    return(1);
  return(0);
}

/**
 * This function updates the minimum and the maximum
 * values of the coodinates.
 *
 * @param word Word
 * @param cc Connected component
 */
void updateBoxCoord(t_word_elt *word, t_cc_elt *cc)
{
  /* Update of minimum */
  /* printf("Avant: %d", word->coord.xmin); */
  if (cc->coord.xmin < word->coord.xmin)
    word->coord.xmin = cc->coord.xmin;
  /*printf("Apres: %d", word->coord.xmin); */

  if (cc->coord.ymin < word->coord.ymin)
    word->coord.ymin = cc->coord.ymin;

  if (cc->coord.xmax > word->coord.xmax)
    word->coord.xmax = cc->coord.xmax;

  if (cc->coord.ymax > word->coord.ymax)
    word->coord.ymax = cc->coord.ymax;
}

/**
 * This function updates the minimum and the maximum
 * values of the coodinates for a line.
 *
 * @param line Line
 * @param word Word
 */
void updateBoxCoordLine(t_line_elt *line, t_word_elt *word)
{
  if (word->coord.xmin < line->coord.xmin)
    line->coord.xmin = word->coord.xmin;

  if (word->coord.ymin < line->coord.ymin)
    line->coord.ymin = word->coord.ymin;

  if (word->coord.xmax > line->coord.xmax)
    line->coord.xmax = word->coord.xmax;

  if (word->coord.ymax > line->coord.ymax)
    line->coord.ymax = word->coord.ymax;
}

/**
 * This function updates the minimum and the maximum
 * values of the coodinates for a paragraph.
 *
 * @param para Paragraph
 * @param line Line
 */
void updateBoxCoordParagraph(t_paragraph_elt *para, t_line_elt *line)
{
  if (line->coord.xmin < para->coord.xmin)
    para->coord.xmin = line->coord.xmin;

  if (line->coord.ymin < para->coord.ymin)
    para->coord.ymin = line->coord.ymin;

  if (line->coord.xmax > para->coord.xmax)
    para->coord.xmax = line->coord.xmax;

  if (line->coord.ymax > para->coord.ymax)
    para->coord.ymax = line->coord.ymax;
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
	  res = wmalloc(sizeof(t_cc_list));
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
 * This function adds a connected component in
 * a list.
 *
 * @param elt Connected component
 * @param cc_list List of connected components
 */
t_cc_list *addListCCsort(t_cc_elt *elt, t_cc_list *cc_list)
{
  t_cc_list *res;
  t_cc_elt *tmp, *father;
  int som;

  if (elt != NULL)
    {
      if (cc_list == NULL)
	{
	  res = wmalloc(sizeof(t_cc_list));
	  res->head = elt;
	  res->tail = elt;
	  res->nbcc = 1;
	  return(res);
	}
      else
	{
	  cc_list->nbcc++;
	  
	  som = elt->coord.xmin + elt->coord.ymin;
	  tmp = cc_list->head;
	  father = tmp;
	  while (tmp != NULL)
	    {
	      if (elt->coord.xmin < tmp->coord.xmin)
		if (!(elt->coord.ymin > tmp->coord.ymax))
		  break;
	      father = tmp;
	      tmp = tmp->next;
	    }
	  
	  /* Element en fin de liste */
	  if (tmp == NULL)
	    {
	      cc_list->tail->next = elt;
	      cc_list->tail = elt;
	      return(cc_list);
	    }
	  
	  /* Element en tete de liste */
	  if (cc_list->head == tmp)
	    {
	      cc_list->head = elt;
	      cc_list->head->next = tmp;
	      return(cc_list);
	    }

	  elt->next = tmp;
	  father->next = elt;
	  if (elt->next == NULL)
	    cc_list->tail = elt;
	  
	  return(cc_list);
	}
    }
  return(NULL);
}

/**
 * This function adds a word in
 * a list.
 *
 * @param elt Word
 * @param word_list List of words
 */
t_word_list *addListWord(t_word_elt *elt, t_word_list *word_list)
{
  t_word_list *res;

  if (elt != NULL)
    {
      if (word_list == NULL)
	{
	  res = wmalloc(sizeof(t_word_list));
	  res->head = elt;
	  res->tail = elt;
	  res->nbword = 1;
	  return(res);
	}
      else
	{
	  word_list->nbword++;
	  word_list->tail->next = elt;
	  word_list->tail = elt;
	  return(word_list);
	}
    }
  return(NULL);
}

/**
 * This function adds a line in a list.
 *
 * @param elt Line
 * @param line_list List of lines
 */
t_line_list *addListLine(t_line_elt *elt, t_line_list *line_list)
{
  t_line_list *res;

  if (elt != NULL)
    {
      if (line_list == NULL)
	{
	  res = wmalloc(sizeof(t_line_list));
	  res->head = elt;
	  res->tail = elt;
	  res->nbline = 1;
	  return(res);
	}
      else
	{
	  line_list->nbline++;
	  line_list->tail->next = elt;
	  line_list->tail = elt;
	  return(line_list);
	}
    }
  return(NULL);
}


/**
 * This function adds a paragraph in a list.
 *
 * @param elt Line
 * @param paragraph_list List of paragraphes
 */
t_paragraph_list *addListParagraph(t_paragraph_elt *elt, t_paragraph_list *paragraph_list)
{
  t_paragraph_list *res;

  if (elt != NULL)
    {
      if (paragraph_list == NULL)
	{
	  res = wmalloc(sizeof(t_paragraph_list));
	  res->head = elt;
	  res->tail = elt;
	  res->nbparagraph = 1;
	  return(res);
	}
      else
	{
	  paragraph_list->nbparagraph++;
	  paragraph_list->tail->next = elt;
	  paragraph_list->tail = elt;
	  return(paragraph_list);
	}
    }
  return(NULL);
}
