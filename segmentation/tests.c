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

#include <stdio.h>
#include "structures.h"
#include "projections.h"
#include "tests.h"
#include "tools.h"
#include "wrappers.h"

int **initializeEnv()
{
  int i, j;
  int **ret;

  ret = NULL;
  ret = wcalloc(10, sizeof(int));
  for (i=0; i < 10; i++)
    ret[i] = wcalloc(10, sizeof(int));

  for (i=0; i < 10; i++)
    for(j=0; j < 10; j++)
      ret[i][j] = 0;

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

void print_matrix(int **matrix, int height, int width)
{
  int i, j;

  printf("-- Matrix display --\n");
  printf("  height: %d\n", height);
  printf("  width: %d\n\n", width);
  for (i=0; i < height; i++)
    {
      printf("\n");
      for(j=0; j < width; j++)
	printf(" %d",matrix[i][j]);
    }
  printf("\n\n");
}

void testInit()
{
  int **matrix;

  /* Initialization of the matrix */
  matrix = initializeEnv();
  
  /* Print of the matrix */
  if (matrix != NULL)
    print_matrix(matrix, 10, 10);
}

void testProjections()
{
  t_binary_image *pic;

  /* Initialization of t_binary_image */
  pic = wmalloc(sizeof(t_binary_image));
  pic->name = "test";
  pic->width = 10;
  pic->height = 10;
  pic->data = initializeEnv();
  pic->hproj = NULL;
  pic->vproj = NULL;

  pic->data[2][3] = 1;
  pic->data[2][5] = 1;

  pic->data[7][1] = 1;
  pic->data[2][1] = 1;
  pic->data[4][1] = 1;
  pic->data[9][1] = 1;
  pic->data[0][1] = 1;

  print_matrix(pic->data, 10, 10);

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
  short int **matrix;
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
	    printf(" %d",matrix[i][j]);
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
