/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/structures.h
 *   This is the header of tests.c
 */

#ifndef TESTS_H
#define TESTS_H

#endif /* TESTS_H */

int **initializeEnv();

void print_matrix(int **matrix, int height, int width);

void testInit();

void testProjections();

void testInitMarkMatrix();

void testAddListCC();

void testQueue();
