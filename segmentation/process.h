/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/process.h
 *   This is the header of "process.c".
 */

#ifndef PROCESS_H
#define PROCESS_H

/**
 * This function executes the extraction process.
 * @param infos Informations about the launch process.
 */
void processAll(t_launch_infos *infos);

#endif /* PROCESS_H */
