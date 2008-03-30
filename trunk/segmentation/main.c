/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/main.c
 *   This is the main file. The program begins here.
 */

#include <stdlib.h>
#include "main.h"
#include "tests.h"

/**
 * This is the main function.
 *
 * @param argc Number of arguements
 * @param argv Array of string arguements
 *
 * @return Integer 0 if succeed, -1 if error
 */
int main()
{
  /* testInit();
    testProjections();
    testInitMarkMatrix();
    testCheckIfUnderLimits();
    testIsBmp();
    testAddListCC();
    testQueue();
    testUpdateMinMax();
  */
  testCC();

  return(EXIT_SUCCESS);
}
