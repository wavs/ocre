/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developep by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /extraction
 *   This folder contains the character extraction part of OCRe.
 * About this file: /extraction/projections.h
 *   This is the header of "projections.c".
 */

#ifndef PROJECTIONS_H
#define PROJECTIONS_H

#endif /* PROJECTIONS_H */

/**
 * This function returns a pointer on an int vector which
 * contains the horizontal projection of the picture.
 * @param pic Binary image.
 */
void horizontal_projection(t_binary_image *pic);

/**
 * This function returns a pointer on an int vector which
 * contains the vertical projection of the picture.
 * @param linelist Set of extracted lines.
 */
void vertical_projection(t_line_set *linelist);
