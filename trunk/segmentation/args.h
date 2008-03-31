/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/args.h
 *   This is the header of "args.c".
 */

#ifndef ARGS_H
#define ARGS_H

/**
 * This function checks arguements and returns filenames of
 * I/O files and options which are activate.
 * @param argc Number of arguements.
 * @param argv Array of strings passed in arguements.
 */
t_launch_infos *apply_args(int argc, char *argv[]);

#endif /* ARGS_H */
