/*
** OCRe - The ultimate OCR - HUGE Software
** OCRe is a project developed by 2nd year EPITA students
** - website: http://huge.ocre.free.fr/
** - svn repository: http://code.google.com/p/ocre
**
** About this folder: /extraction
**   OCRec is the character extraction part of OCRe.
** About this file: /extraction/args.c
**   This file contains a function which checks the arguements.
*/

#include <stdlib.h>
#include "structures.h"
#include "getopt.h"
#include "infos.h"
#include <string.h>

/*
** This function checks arguements and returns filenames of
** input and output files and options which are activate.
*/
t_launch_infos *apply_args(int argc, char *argv[])
{
  int optchar;
  t_launch_infos *res;

  res = NULL;
  res = malloc(sizeof(t_launch_infos));
  res->display = 0;
  res->inFile = NULL;
  res->outFile = NULL;
  if (argc > 1)
    {
      while ((optchar = getopt(argc, argv, "i:o:h::d")) != -1)
	{
	  switch (optchar)
	    {
	    case 'i':
	      res->inFile = strdup(optarg);
	      break;
	    case 'o':
	      res->outFile = strdup(optarg);
	      break;
	    case 'h':
	      help(argv[0]);
	      free(res);
	      exit(EXIT_SUCCESS);
	    case 'd':
	      res->display = 1;
	      break;
	    default:
	    case '?':
	      unknown_command_line(argv[0]);
	      free(res);
	      exit(EXIT_SUCCESS);
	    }
	}
    }
  else
    {
      help(argv[0]);
      free(res);
      exit(EXIT_SUCCESS);
    }
  return (res);
}
