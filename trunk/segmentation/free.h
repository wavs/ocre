/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/free.h
 *   This is the header of "free.c".
 */

#ifndef FREE_H
#define FREE_H

/**
 * This function frees the structure of binary image.
 * @param pic Binary image.
 */
void free_pic(t_binary_image *pic);

#endif /* FREE_H */
