/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /extraction
 *   This folder contains the character extraction part of OCRe.
 * About this file: /extraction/extraction.h
 *   This is the header of "extraction.c".
 */

#ifndef EXTRACTION_H
#define EXTRACTION_H

#endif /* EXTRACTION_H */

/**
 * This function extracts the lines of the picture.
 * It returns the set of lines in a linked list.
 * @param pic Binary image.
 * @return Set of extracted lines.
 */
t_result_extraction *extract_line(t_binary_image *pic);
