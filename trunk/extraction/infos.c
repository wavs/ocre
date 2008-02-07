/*
** OCRe - The ultimate OCR - HUGE Software
** OCRe is a project developed by 2nd year EPITA students
** - website: http://huge.ocre.free.fr/
** - svn repository: http://code.google.com/p/ocre
**
** About this folder: /extraction
**   OCRec is the character extraction part of OCRe.
** About this file: /extraction/infos.c
**   This file contains some functions which show messages for user.
*/

#include <stdio.h>

/*
** This function shows an error message when the user types
** a wrong command line.
*/
void unknown_command_line(char *exe)
{
  printf("Unknown command line option...\n");
  printf("Try: %s [-i input file] [-o output file]\n", exe);
  printf("For more informations, type: %s -h\n", exe);
}

/*
** This function shows the short help of the program.
*/
void help(char *exe)
{
  printf("\nOCRe - HUGE Software - Extraction Part\n\n");
  printf("Command line: %s [-i input file] [-o output file]\n\n", exe);
  printf("This program extracts the printed lines of a bitmap image.\n");
  printf("It saves the extraction result in an ouput bitmap file.\n\n");
  printf("Arguements:\n");
  printf("   -i file: this is the bitmap image in which you want to extract line.\n");
  printf("   -o file: this is the output bitmap image in which you'll see the preview of extraction.\n");
  printf("   -h : this is the help of the program.\n");
  printf("   -d : this option activates the display window.\n\n");
}
