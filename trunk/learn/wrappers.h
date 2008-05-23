/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   This folder contains the character extraction part of OCRe.
 * About this file: /segmentation/wrappers.c
 *   This file contains wrappers functions about commons functions
 *   like malloc(), free(), ...
 */

#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <unistd.h>

/**
 * Wrapper function of malloc().
 *
 * @param size Size to allocate
 *
 * @return Pointer to the allocated block, if succeed
 */
void *wmalloc(size_t size);

/**
 * Wrapper function of calloc().
 *
 * @param nelements Number of elements to allocate
 * @param bytes Number of bytes per elements
 *
 * @return Pointer to the allocated block, if succeed
 */
void *wcalloc(size_t nelements, size_t bytes);

/**
 * Wrapper function of realloc().
 *
 * @param block Block to reallocate
 * @param size Size to allocate
 *
 * @return Pointer to the allocated block, if succeed
 */
void *wrealloc(void *block, size_t size);

/**
 * Wrapper function of free().
 *
 * @param pointer Pointer to the allocated block
 */
void wfree(void *pointer);

#endif /* WRAPPERS_H */
