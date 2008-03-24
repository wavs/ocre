/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /extraction
 *   This folder contains the character extraction part of OCRe.
 * About this file: /extraction/extraction.c
 *   This file contains functions about the extraction of lines
 *   and characters.
 */

#include <stdlib.h>
#include "structures.h"
#include "wrappers.h"

/**
 * This function extracts the lines of the picture.
 * It returns the set of lines in a linked list.
 * @param pic Binary image.
 * @return Set of extracted lines.
 */
t_result_extraction *extract_line(t_binary_image *pic)
{
  int i, i_tmp, index, height_tmp;
  t_line_set *tmp, *father;
  t_result_extraction *result;

  result = NULL;
  result = wmalloc(sizeof(t_result_extraction));
  result->linelist = NULL;
  result->name = pic->name;
  index = 0;
  i = 0;
  while (i < pic->height) {
    if (pic->hproj[i] > 0) {
      i_tmp = i;
      height_tmp = 0;
      while ((pic->hproj[i] != 0) && (i < pic->height)) {
	height_tmp++;
	i++; }
      if (height_tmp > 8) {
	index++;
	tmp = wmalloc(sizeof(t_line_set));
	tmp->id = index;
	tmp->pos = i_tmp;
	tmp->charlist = NULL;
	tmp->next = NULL;
	tmp->height = height_tmp;
	if (index == 1) {
	  result->linelist = tmp;
	} else {
	  father->next = tmp; }
	father = tmp;
      }
    }
    i++;
  }
  tmp = NULL;
  father = NULL;
  return (result);
}
