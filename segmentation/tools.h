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

/**
 * This function determines if the extension of a
 * filename is ".bmp".
 *
 * @param filename Name of the bitmap file
 */
int is_bmp(char *filename);

/**
 * This function initializes a matrix of marks.
 *
 * @param height Height of the matrix
 * @param width Width of the matrix
 * 
 * @return Matrix filled with the value 0
 */
short int **initMarkMatrix(int height, int width);

/**
 * This function adds a connected component in
 * a list.
 * 
 * @param elt Connected component
 * @param cc_list List of connected components
 */
void addListCC(t_cc_elt *elt, t_cc_list *cc_list);

/**
 * This function creates an emtpy queue.
 *
 * @return Queue
 */
t_queue *qNew();

/**
 * This function adds an element to
 * the queue.
 *
 * @param pp Queue
 * @param data Data stored in the queue
 */
void qPost (t_queue **pp, void *data);

/**
 * This function extracts an element of
 * the queue.
 *
 * @param pp Queue
 */
void *qGet (t_queue **pp);

/**
 * This function deletes the queue.
 *
 * @param pp Queue
 */
void qDelete (t_queue **pp);
