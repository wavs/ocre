/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developep by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   This folder contains the character extraction part of OCRe.
 * About this file: /segmentation/projections.h
 *   This is the header of "projections.c".
 */

#ifndef PROJECTIONS_H
#define PROJECTIONS_H

#endif /* PROJECTIONS_H */

/**
 * This function computes the horizontal projection
 *  of a binary matrix.
 *
 * @param pic Binary image
 */
void horizontal_projection(t_binary_image *pic);

/**
 * This function computes the vertical projection
 * of a binary matrix.
 *
 * @param pic Binary image
 */
void vertical_projection(t_binary_image *pic);
