/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /extraction
 *   OCRec is the character extraction part of OCRe.
 * About this file: /extraction/tools.h
 *   This is the header of tools.c
 */

#ifndef TOOLS_H
#define TOOLS_H

#endif /* TOOLS_H */

/**
 * This functions initiates a matrix;
 *
 * @return Matrix
 */
t_matrix *initializeEnv();

/**
 * This function determines if the extension of a
 * filename is ".bmp".
 *
 * @param filename Name of the bitmap file
 */
int is_bmp(char *filename);

/**
 * This function tests if we are under the limits.
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @param limit_x Limit of x coordinate
 * @param limit_y Limit of y coordinate
 *
 * @return 1 if under limits, 0 else
 */
int checkIfUnderLimits(int x, int y, int limit_x, int limit_y);

/**
 * This function updates the minimum and the maximum
 * values of the coodinates.
 *
 * @param minmax Structure which stores the min/max coordinates
 * @param x X coordinate
 * @param y Y coordinate
 */
void updateMinMax(t_cc_coordinate *minmax, int x, int y);

/**
 * This function initializes a matrix of marks.
 *
 * @param height Height of the matrix
 * @param width Width of the matrix
 * 
 * @return Matrix filled with the value 0
 */
char **initMarkMatrix(int height, int width);

/**
 * This function adds a connected component in
 * a list.
 * 
 * @param elt Connected component
 * @param cc_list List of connected components
 */
t_cc_list *addListCC(t_cc_elt *elt, t_cc_list *cc_list);

/**
 * This function adds an element to
 * the queue.
 *
 * @param p_queue Queue
 * @param coord Data stored in the queue
 */
void qEnqueue(t_queue **p_queue, t_coordinate *coord);


/**
 * This function extracts an element of
 * the queue.
 *
 * @param p_queue Queue
 *
 * @return Data stored in the first element of the queue
 */
t_coordinate *qDequeue(t_queue **p_queue);

/**
 * This function deletes the queue.
 *
 * @param p_queue Queue
 */
void qDelete(t_queue **p_queue);
/**
 * This function returns the value of the
 * first element of the queue. (without destroy).
 *
 * @param p_queue Queue
 *
 * @return Data stored in the first element of the queue
 */
t_coordinate *qQeek(t_queue *p_queue);
