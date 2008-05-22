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
 * This function creates all the blocks according to
 * the list of connected components.
 *
 * @param cc_list Linked list of connected components
 * 
 * @return Linked list of blocks
 */
t_block_list *makeBlocks(t_cc_list *cc_list);

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
 * This function traces all the words with boxes
 * in an output image.
 *
 * @param image SDL surface
 * @param word_list Linked list of words
 */
void traceWords(SDL_Surface *image, t_word_list *word_list);

/**
 * This function creates a list of words with the list of connected components.
 *
 * @param cc_list Linked list of connected components
 *
 * @return Linked list of words
 */
t_word_list *makeWords(t_cc_list *cc_list);

/**
 * This function traces all the lines with boxes
 * in an output image.
 *
 * @param image SDL surface
 * @param line_list Linked list of lines
 */
void traceLines(SDL_Surface *image, t_line_list *line_list);

/**
 * This function creates a list of lines with the list of connected components.
 *
 * @param cc_list Linked list of connected components
 *
 * @return t_line_list Linked list of lines
 */
t_line_list *makeLines(t_word_list *word_list);



/**
 * This function traces all the paragraphes with boxes
 * in an output image.
 *
 * @param image SDL surface
 * @param paragraph_list Linked list of paragraphes
 */
void traceParagraphes(SDL_Surface *image, t_paragraph_list *paragraph_list);

/**
 * This function creates a list of paragraphes with the list of lines.
 *
 * @param line_list Linked list of lines
 *
 * @return t_paragraph_list Linked list of paragraphes
 */
t_paragraph_list *makeParagraphes(t_line_list *line_list);


#endif /* SEGMENTATION_H */
