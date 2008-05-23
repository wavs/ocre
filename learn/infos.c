/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/infos.c
 *   This file contains some functions which show messages for user.
 */

#include <stdio.h>

/**
 * This function shows an error message when the user types
 * a wrong command line.
 *
 * @param exe Name of the executable.
 */
void unknown_command_line(char *exe)
{
  printf("Unknown command line option...\n");
  printf("Try: %s [-i input file] [-o output file]\n", exe);
  printf("For more informations, type: %s -help\n", exe);
}

/**
 * This function shows the short help of the program.
 *
 * @param exe Name of the executable.
 */
void help(char *exe)
{
 printf("Usage: %s -i inputfile -o output file\n\n", exe);
 printf("This program extracts the connected ");
 printf("components of a bitmap image\n");
 printf("It saves the character extraction in a txt file\n\n");
 printf("Arguements:\n");
 printf("   -i file: path of your input file\n");
 printf("   -o file: path of your output file\n");
 printf("   -v     : verbose\n");
 printf("   -h     : display the help\n\n");
}
