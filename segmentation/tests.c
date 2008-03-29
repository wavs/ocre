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
#include <stdlib.h>
#include "tests.h"
#include "projections.h"
#include "free.h"
#include "tools.h"
#include "wrappers.h"
#include "print.h"

t_matrix *initializeEnv()
{
  unsigned int i, j;
  t_matrix *ret;

  ret = wmalloc(sizeof(t_matrix));
  ret->nbrows = 10;
  ret->nbcols = 10;
  ret->data = NULL;
  ret->data = (int **)wmalloc(ret->nbrows * sizeof(int *));
  for (i=0; i < ret->nbrows; ++i)
    ret->data[i] = (int *)wcalloc(ret->nbcols, sizeof(int));

  for (i=0; i < ret->nbrows; ++i)
    for(j=0; j < ret->nbcols; ++j)
      ret->data[i][j] = 0;
  
  return(ret);
}

void testInit()
{
  unsigned int i;
  t_matrix *matrix;

  /* Initialization of the matrix */
  matrix = NULL;
  matrix = initializeEnv();
  
  /* Print of the matrix */
  if (matrix != NULL && matrix->data != NULL)
    {
      print_matrix(matrix);
      /* Free memory */
      for (i=0; i < matrix->nbrows; i++)
	free(matrix->data[i]);
      free(matrix->data);
      free(matrix);
    }
  else
    {
      printf("testInit() aborted\n");
      exit(EXIT_FAILURE);
    }
}

void testProjections()
{
  t_binary_image *pic;

  /* Initialization of t_binary_image */
  pic = wcalloc(1, sizeof(t_binary_image));
  pic->name = "test";
  pic->width = 10;
  pic->height = 10;
  pic->matrix = initializeEnv();
  pic->hproj = NULL;
  pic->vproj = NULL;
  if (pic->matrix != NULL && pic->matrix->data != NULL)
    {
      print_matrix(pic->matrix); 
      /* Computation of projections */
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
      /* Free memory */
      free_pic(pic);
    }
  else
    {
      printf("testProjections() aborted");
      exit(EXIT_FAILURE);
    }
}

void testInitMarkMatrix()
{
  char **matrix;
  unsigned int i, j;

  /* Initialization of the matrix */
  matrix = initMarkMatrix(10, 10);
  
  /* Print of the matrix */
  printf("Mark matrix\n");
  if (matrix != NULL)
    {      
      printf("-- Matrix display --\n");
      printf("  height: %d\n", 10);
      printf("  width: %d\n\n", 10);
      for (i=0; i < 10; i++)
	{
	  printf("\n");
	  for(j=0; j < 10; j++)
	    printf(" %c",matrix[i][j]);
	}
      printf("\n\n");
      /* Free memory */
      for (i=0; i < 10; i++)
	free(matrix[i]);
      free(matrix);
    }
  else
    {
      printf("testInitMarkMatrix() aborted");
      exit(EXIT_FAILURE);
    }
}

void testCheckIfUnderLimits()
{
  int xtest, ytest;
  int xlimit, ylimit;
  
  /* Initialization of values */
  xtest = 100;
  ytest = 437;
  xlimit = 300;
  ylimit = 1000;

  printf("Test (1)\n");
  /* Checking */
  if (checkIfUnderLimits(xtest, ytest, xlimit, ylimit))
    printf("(x = %d, y = %d is between the limits ( 0->%d, 0-)%d )\n", xtest, ytest, xlimit, ylimit);
  else
    printf("(x = %d, y = %d isn't between the limits ( 0->%d, 0->%d )\n", xtest, ytest, xlimit, ylimit);

/* Test (2)*/
  xtest = 8;
  ytest = 299;
  xlimit = 9;
  ylimit = 300;

  printf("Test (2)\n");
  /* Checking */
  if (checkIfUnderLimits(xtest, ytest, xlimit, ylimit))
    printf("(x = %d, y = %d is between the limits ( 0->%d, 0-)%d )\n", xtest, ytest, xlimit, ylimit);
  else
    printf("(x = %d, y = %d isn't between the limits ( 0->%d, 0->%d )\n", xtest, ytest, xlimit, ylimit);
}

void testIsBmp()
{
  char *filename;

  /* Test (1) */
  printf("Test (1)\n");
  filename = "hello";
  if (is_bmp(filename))
    printf("'%s' is a bmp file extension.\n", filename);
  else
    printf("'%s' isn't a bmp file extension.\n", filename);

  /* Test (2) */
  printf("Test (2)\n");
  filename = "test.bmp";
  if (is_bmp(filename))
    printf("'%s' is a bmp file extension.\n", filename);
  else
    printf("'%s' isn't a bmp file extension.\n", filename);

  /* Test (3) */
  printf("Test (3)\n");
  filename = " ";
  if (is_bmp(filename))
    printf("'%s' is a bmp file extension.\n", filename);
  else
    printf("'%s' isn't a bmp file extension.\n\n", filename);
}

void testAddListCC()
{
  t_cc_list *cc_list;
  t_cc_elt elt1, elt2, elt3;

  
  printf("- Test List CC -\n\n");
  /* Creation of element (1) */
  elt1.id = 1;
  elt1.nbpix = 24;
  elt1.coord.xmin = 78;
  elt1.coord.ymin = 90;
  elt1.coord.xmin = 100;
  elt1.coord.ymin = 400;
  elt1.chr = 0;
  elt1.next = NULL;
  /* Creation of element (2) */
  elt2.id = 2;
  elt2.nbpix = 1;
  elt2.coord.xmin = 0;
  elt2.coord.ymin = 100;
  elt2.coord.xmin = 500;
  elt2.coord.ymin = 200;
  elt2.chr = 0;
  elt2.next = NULL;
  /* Creation of element (3) */
  elt3.id = 3;
  elt3.nbpix = 100;
  elt3.coord.xmin = 894;
  elt3.coord.ymin = 235;
  elt3.coord.xmax = 1000;
  elt3.coord.ymax = 2000;
  elt3.chr = 1;
  elt3.next = NULL;
  /* add elements to the list */
  addListCC(&elt1, cc_list);
  addListCC(&elt2, cc_list);
  addListCC(&elt3, cc_list);
  /* Print the list */
  print_listCC(cc_list);
  /* Free memory */
  free_listCC(cc_list);
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
