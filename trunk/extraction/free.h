/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /extraction
 *   OCRec is the character extraction part of OCRe.
 * About this file: /extraction/free.h
 *   This is the header of "free.c".
 */

#ifndef FREE_H
#define FREE_H

#endif /* FREE_H */

/**
 * This function frees the structure of binary image.
 * @param pic Binary image.
 */
void free_pic(t_binary_image *pic);

/**
 * This function frees the structure of the extraction result.
 * @param result Result structure with lines set.
 */
void free_result(t_result_extraction *result);

/**
 * This function frees all structures from the extraction part.
 * @param pic Binary image.
 * @param result Result structure with lines set.
 */
void free_all(t_binary_image *pic, t_result_extraction *result);
