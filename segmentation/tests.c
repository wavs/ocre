/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/structures.h
 *   This file contains some test functions.
 */

#include "structures.h"
#include <stdio.h>
#include "tests.h"
#include "projections.h"
#include "tools.h"
#include "wrappers.h"

t_matrix *initializeEnv()
{
  unsigned int i, j;
  t_matrix *ret;

  ret->nbrows = 10;
  ret->nbcols = 10;
  ret->data = NULL;
  ret->data = (int **)wcalloc(ret->nbrows, sizeof(int *));
  for (i=0; i < ret->nbrows; ++i)
    ret->data[i] = (int *)wcalloc(ret->nbcols, sizeof(int));

  for (i=0; i < ret->nbrows; ++i)
    for(j=0; j < ret->nbcols; ++j)
      ret->data[i][j] = 0;

  return(ret);
}

void print_vector(int *vector, int length)
{
  int i;
  
  printf("-- Vector display --\n");
  printf("  length: %d\n", length);
  for (i=0; i < length; i++)
    printf(" %d",vector[i]);
  printf("\n\n");
}

void print_matrix(t_matrix *matrix)
{
  unsigned int i,j;

  printf("-- Matrix display --\n");
  printf("  rows: %d\n", matrix->nbrows);
  printf("  colums: %d\n\n", matrix->nbcols);
  for (i=0; i < matrix->nbrows; ++i)
    {
      printf("\n");
      for(j=0; j < matrix->nbcols; ++j)
	printf(" %d",matrix->data[i][j]);
    }
  printf("\n\n");
}

void testInit()
{
  t_matrix *matrix;

  /* Initialization of the matrix */
  matrix = initializeEnv();
  
  /* Print of the matrix */
  if (matrix != NULL)
    print_matrix(matrix);
}

void testProjections()
{
  t_binary_image *pic;

  /* Initialization of t_binary_image */
  pic = wmalloc(sizeof(t_binary_image));
  pic->name = "test";
  pic->width = 10;
  pic->height = 10;
  pic->matrix = initializeEnv();
  pic->hproj = NULL;
  pic->vproj = NULL;

  print_matrix(pic->matrix);

  /* Computation of projections*/
  horizontal_projection(pic);
  vertical_projection(pic);

  /* Print of the vectors */
  if (pic->hproj != NULL)
    {
      printf("Horizontal projection\n");
      print_vector(pic->hproj, 10);
    }
  if (pic->vproj != NULL)
    {
      printf("Vertical projection\n");
      print_vector(pic->vproj, 10);
    }
}

void testInitMarkMatrix()
{
  char **matrix;
  int i, j;

  /* Initialization of the matrix */
  matrix = initMarkMatrix(5, 5);
  
  /* Print of the matrix */
  printf("Mark matrix\n");
  if (matrix != NULL)
    {      
      printf("-- Matrix display --\n");
      printf("  height: %d\n", 5);
      printf("  width: %d\n\n", 5);
      for (i=0; i < 5; i++)
	{
	  printf("\n");
	  for(j=0; j < 5; j++)
	    printf(" %c",matrix[i][j]);
	}
      printf("\n\n");
    }
}

void testAddListCC()
{
  return; 
}

void testQueue()
{
  t_queue **q;
  int i,k;
  int *ptr_i;
  
  if (q == NULL)
    {
      printf("Queue empty\n");
      i = 0;
      ptr_i = &i;
      printf("Queue post()\n");
      for (k=0; k < 10; k++)
	{
	  qPost(q,ptr_i);
	  printf("%d >>\n",i);
	  i++;
	}
      printf("Queue get()\n");
      for (k=0; k < 10; k++)
	{
	  ptr_i = qGet(q);
	  printf(">> %d\n", *ptr_i);
	}
      qDelete(q);
      if (q == NULL)
	printf("Queue deleted\n");
    }
  else
    printf("Queue error");
}
