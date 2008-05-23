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
	     char **mark);

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
 * This function checks if the connected components
 * represent a character.
 *
 * @param cc_list Linked list of connected components
 */
void checkIfCharacter(t_cc_list *cc_list, int height, int width);

/**
 * This function traces all the words with boxes
 * in an output image.
 *
 * @param image SDL surface
 * @param cc_list Linked list of connected components
 */
void traceCC(SDL_Surface *image, t_cc_list *cc_list);

/**
 * This function updates the coordinates of the
 * connected components 
 */
void updateCC(t_cc_list *cc_list);

/**
 * This function resizes a matrix.
 */
t_matrix *resizeMatrix(t_matrix *mat, t_cc_elt *cc, t_binary_image *pic);

/**
 * This function returns a resized matrix (10x10)  for the cc.
 *
 * @param cc Connected component
 * @param pic Binary image
 *
 * @return Matrix 10x10
 */
t_matrix *resizeCC(t_cc_elt *cc, t_binary_image *pic);

/**
 * This function writes a txt file with the list of cc.
 *
 * @param cc_list Linked list of connected component
 */
void exportCC(t_cc_list *cc_list, t_binary_image *pic);

#endif /* SEGMENTATION_H */
