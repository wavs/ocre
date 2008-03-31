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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "wrappers.h"

/**
 * Wrapper function of malloc().
 *
 * @param size Size to allocate
 *
 * @return Pointer to the allocated block, if succeed
 */
void *wmalloc(size_t size)
{
  void *tmp;

  tmp = NULL;
  tmp = malloc(size);
  if (tmp == NULL)
    {
      fprintf(stderr, "Malloc() error: Out of memory.\n");
      exit(EXIT_FAILURE);
    }
  return(tmp);
}

/**
 * Wrapper function of calloc().
 *
 * @param nelements Number of elements to allocate
 * @param bytes Number of bytes per elements
 *
 * @return Pointer to the allocated block, if succeed
 */
void *wcalloc(size_t nelements, size_t bytes)
{
  void *tmp;

  tmp = NULL;
  tmp = calloc(nelements, bytes);
  if (tmp == NULL)
    {
      fprintf(stderr, "Calloc() error: Out of memory.\n");
      exit(EXIT_FAILURE);
    }
  return(tmp);
}

/**
 * Wrapper function of realloc().
 *
 * @param block Block to reallocate
 * @param size Size to allocate
 *
 * @return Pointer to the allocated block, if succeed
 */
void *wrealloc(void *block, size_t size)
{
  void *tmp;

  tmp = NULL;
  tmp = realloc(block, size);
  if (tmp == NULL)
    {
      fprintf(stderr, "Realloc() error: Out of memory.\n");
      exit(EXIT_FAILURE);
    }
  return(tmp);
}

/**
 * Wrapper function of free().
 *
 * @param pointer Pointer to the allocated block
 */
void wfree(void *pointer)
{
  free(pointer);
  pointer = NULL;
}
