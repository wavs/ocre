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
#include "segmentation.h"
#include "free.h"
#include "tools.h"
#include "wrappers.h"
#include "print.h"

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

  cc_list = NULL;
  printf("- Test List CC -\n\n");
  /* Creation of element (1) */
  elt1.id = 1;
  elt1.nbpix = 24;
  elt1.coord.xmin = 78;
  elt1.coord.ymin = 90;
  elt1.coord.xmax = 100;
  elt1.coord.ymax = 400;
  elt1.chr = 0;
  elt1.next = NULL;
  /* Creation of element (2) */
  elt2.id = 2;
  elt2.nbpix = 1;
  elt2.coord.xmin = 0;
  elt2.coord.ymin = 100;
  elt2.coord.xmax = 500;
  elt2.coord.ymax = 200;
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
  cc_list = addListCC(&elt1, cc_list);
  cc_list = addListCC(&elt2, cc_list);
  cc_list = addListCC(&elt3, cc_list);
  /* Print the list */
  print_listCC(cc_list);
  /* Free memory */
  wfree(cc_list);
}

void testQueue()
{
  t_queue **q;
  t_coordinate *coord1, *coord2, *coord3;
  t_coordinate *res1, *res2, *res3;
  
  printf(" - Test Queue -\n");
  q = NULL;
  q = (t_queue **)wcalloc(1, sizeof(t_queue *));
  /* Coordinates (1) */
  coord1 = wmalloc(sizeof(t_coordinate));
  coord1->x = 23;
  coord1->y = 45;
  qEnqueue(q,coord1);
  printf(">> Element (1)\n x: %d\n y: %d\n\n", coord1->x, coord1->y);
  
  /* Coordinates (2) */
  coord2 = wmalloc(sizeof(t_coordinate));
  coord2->x = 9085;
  coord2->y = 894;
  qEnqueue(q,coord2);
  printf(">> Element (2)\n x: %d\n y: %d\n\n", coord2->x, coord2->y);
  
  /* Coordinates (3) */
  coord3 = wmalloc(sizeof(t_coordinate));
  coord3->x = 0;
  coord3->y = 56;
  qEnqueue(q,coord3);
  printf(">> Element (3)\n x: %d\n y: %d\n\n", coord3->x, coord3->y);
  
  res1 = qDequeue(q);
  if (res1 != NULL)
    printf("Element (1) >>\n x: %d\n y: %d\n\n", res1->x, res1->y);
  res2 = qDequeue(q);
  if (res2 != NULL)
    printf("Element (2) >>\n x: %d\n y: %d\n\n", res2->x, res2->y);
  res3 = qDequeue(q);
  if (res3 != NULL)
    printf("Element (3) >>\n x: %d\n y: %d\n\n", res3->x, res3->y);
  
  /* Free memory */
  qDelete(q);
  wfree(res1);
  free(res2);
  wfree(res3);
  wfree(q);
}

void testUpdateMinMax()
{
  int x1,x2,x3;
  int y1,y2,y3;
  t_cc_coordinate *minmax;

  /* Initialization of values */
  x1 = 34;
  x2 = 657;
  x3 = 90;
  y1 = 0;
  y2 = 74;
  y3 = 7800;
  minmax = wmalloc(sizeof(t_cc_coordinate));
  minmax->xmin = 50;
  minmax->xmax = 100;
  minmax->ymin = 20;
  minmax->ymax = 78;

  printf(" - Test updateMinMax() -\n");
  printf("\n Values (1)\n");
  printf(" x: %d ",x1);
  printf(" y: %d ",y1);
  printf(" xmin: %d ",minmax->xmin);
  printf(" ymin: %d ",minmax->ymin);
  printf(" xmax: %d ",minmax->xmax);
  printf(" ymax: %d ",minmax->ymax);
  printf("\nUpdate values\n");
  updateMinMax(minmax, x1, y1);
  printf(" > xmin: %d \n",minmax->xmin);
  printf(" > ymin: %d \n",minmax->ymin);
  printf(" > xmax: %d \n",minmax->xmax);
  printf(" > ymax: %d \n",minmax->ymax);

  printf("\n Values (2)\n");
  printf(" x: %d ",x2);
  printf(" y: %d ",y2);
  printf("\nUpdate values\n");
  updateMinMax(minmax, x2, y2);
  printf(" > xmin: %d \n",minmax->xmin);
  printf(" > ymin: %d \n",minmax->ymin);
  printf(" > xmax: %d \n",minmax->xmax);
  printf(" > ymax: %d \n",minmax->ymax);

  printf("\n Values (3)\n");
  printf(" x: %d ",x3);
  printf(" y: %d ",y3);
  printf("\nUpdate values\n");
  updateMinMax(minmax, x3, y3);
  printf(" > xmin: %d \n",minmax->xmin);
  printf(" > ymin: %d \n",minmax->ymin);
  printf(" > xmax: %d \n",minmax->xmax);
  printf(" > ymax: %d \n",minmax->ymax);

  /* Free memory */
  wfree(minmax);
}

void testCC()
{
  unsigned int i;
  t_matrix *matrix;
  t_cc_list *cc_list;

  printf(" - Test List CC -\n\n");

  /* Creation of the matrix */
  matrix= NULL;
  matrix = initializeEnv();
  print_matrix(matrix);

  if (matrix != NULL)
    {
      /* Creation of the CC list */
      cc_list = NULL;
      cc_list = findCC(matrix);
      print_listCC(cc_list);
      
      /* Free memory */
      /*free_listCC(cc_list);*/
      for (i=0; i < matrix->nbrows; i++)
	free(matrix->data[i]);
	free(matrix->data);
    }
    free(matrix);
}
