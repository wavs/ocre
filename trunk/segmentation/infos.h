/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/infos.h
 *   This is the header of "infos.c".
 */

#ifndef INFOS_H
#define INFOS_H

/**
 * This function shows an error message when the user types
 * a wrong command line.
 * @param exe Name of the executable.
 */
void unknown_command_line(char *exe);

/**
 * This function shows the short help of the program.
 * @param exe Name of the executable.
 */
void help(char *exe);

#endif /* INFOS_H */
