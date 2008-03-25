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

#include "segmentation.h"
#include "structures.h"
#include "wrappers.h"

/**
 * This functions finds all the connected components of
 * the matrix.
 *
 * @param matrix Binary matrix
 * @param height Height of the matrix
 * @param width Width of the matrix
 *
 * @return Linked list of connected components
 */
t_cc_list *findCC(int **matrix, int height, int width)
{
  //FIXME
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
  //FIXME
}

/**
 * This function checks if the connected components
 * represent a character.
 *
 * @param cc_list Linked list of connected components
 */
void checkIfCharacter(t_cc_list *cc_list)
{
  //FIXME
}

/**
 * This function detects the type of blocks
 * (text, image, ...)
 * 
 * @param block_list Linked list of blocks
 */
void detectTypeOfBlocks(t_block_list *block_list)
{
  //FIXME
}

/**
 * This function traces all the blocks with boxes
 * in an output image.
 *
 * @param block_list Linked list of blocks
 * @param limit Margins of the input image.
 */
void traceBlocks(t_block_list *block_list, t_limit *limit)
{
  //FIXME
}
