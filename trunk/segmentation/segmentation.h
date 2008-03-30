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

#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#endif /* SEGMENTATION_H */


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
void crossCC(int y, int x, t_cc_elt *elt, t_matrix *matrix, char **mark);

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
		  t_cc_list *cc_list);

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
t_cc_list *findCC(t_matrix *matrix);

/**
 * This function creates all the blocks according to
 * the list of connected components.
 *
 * @param cc_list Linked list of connected components
 * 
 * @return Linked list of blocks
 */
/*t_block_list *makeBlocks(t_cc_list *cc_list);*/

/**
 * This function checks if the connected components
 * represent a character.
 *
 * @param cc_list Linked list of connected components
 */
/*void checkIfCharacter(t_cc_list *cc_list);*/

/**
 * This function detects the type of blocks
 * (text, image, ...)
 * 
 * @param block_list Linked list of blocks
 */
/*void detectTypeOfBlocks(t_block_list *block_list);*/

/**
 * This function traces all the blocks with boxes
 * in an output image.
 *
 * @param block_list Linked list of blocks
 * @param limit Margins of the input image.
 */
/*void traceBlocks(t_block_list *block_list, t_limit *limit);*/
