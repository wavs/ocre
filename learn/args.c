/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/args.c
 *   This file contains a function which checks the arguements.
 */

#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "wrappers.h"
#include "getopt.h"
#include "infos.h"

/**
 * This function checks arguements and returns filenames of
 * I/O files and options which are activate.
 *
 * @param argc Number of arguements.
 * @param argv Array of strings passed in arguements.
 *
 * @return Informations about arguements
 */
t_launch_infos *apply_args(int argc, char *argv[])
{
  int optchar;
  t_launch_infos *res;

  res = NULL;
  res = wmalloc(sizeof(t_launch_infos));
  res->inFile = NULL;
  res->outFile = NULL;
  res->textfile = 0;
  res->verbose = 0;
  if (argc > 1)
    { while ((optchar = getopt(argc, argv, "i:o:h:t:v")) != -1)
	{ switch (optchar)
	    {  case 'i':
		res->inFile = strdup(optarg);
		break;
	    case 'o':
	      res->outFile = strdup(optarg);
	      break;
	    case 't':
	      res->textfile = 1;
	      break;
	    case 'v':
	      res->verbose = 1;
	      break;
	    case 'h':
	      help(argv[0]);
	      wfree(res);
	      exit(EXIT_SUCCESS);
	    default:
	    case '?':
	      unknown_command_line(argv[0]);
	      wfree(res);
	      exit(EXIT_SUCCESS); }
	}
    } else { help(argv[0]);
    wfree(res);
    exit(EXIT_SUCCESS);
    }
  return (res);
}
