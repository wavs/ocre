/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /extraction
 *   OCRec is the character extraction part of OCRe.
 * About this file: /extraction/launch.h
 *   This is the header of "launch.c".
 */

#ifndef LAUNCH_H
#define LAUNCH_H

#endif /* LAUNCH_H */

/**
 * This function starts the extraction process with
 * the display option.
 * @param infos Informations about the launch process.
 */
void launchProgramWithDisplay(t_launch_infos *infos);

/**
 * This function starts the extraction process without
 * the display option.
 * @param infos Informations about the launch process.
 */
void launchProgramWithoutDisplay(t_launch_infos *infos);
