/*
** OCRe - The ultimate OCR - HUGE Software
** OCRe is a project developep by 2nd year EPITA students
** - website: http://huge.ocre.free.fr/
** - svn repository: http://code.google.com/p/ocre
**
** About this folder: /extraction
**   This folder contains the character extraction part of OCRe.
** About this file: /extraction/projections.c
**   This file contains functions about the projection of pixels.
*/

#include <stdlib.h>
#include "structures.h"

/*
** This function returns a pointer on an int vector which
** contains the horizontal projection of the picture.
** Prerequired: Allocation of the t_binary_image pointed by pic.
*/
void horizontal_projection(t_binary_image *pic)
{
  int i;
  int j;
  
  pic->hproj = malloc(pic->height * sizeof(int));
  /* Gestion d'erreurs de mémoire */
  for (i=0; i < pic->height; i++)
    {
      pic->hproj[i] = 0;
      for (j=0; j < pic->width; j++)
	{
	  pic->hproj[i] = pic->hproj[i] + pic->data[j][i];
	}
    }
}

/*
** This function returns a pointer on an int vector which
** contains the vertical projection of the picture.
** Prequired: Allocation of the t_binary_image pointed by pic.
*/
/*
void vertical_projection(t_binary_image *pic)
{
  int i;
  int j;

  pic->vproj = malloc(pic->width * sizeof(int));
  // Gestion d'erreurs de mémoire
  for (i=0; i < pic->width; i++)
    {
      pic->vproj[i] = 0;
      for (j=0; j < pic->height; j++)
	{
	  pic->vproj[i] = pic->vproj[i] + pic->data[i][j];
	}
    }
}
*/
