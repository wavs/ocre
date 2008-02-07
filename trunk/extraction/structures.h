/*
** OCRe - The ultimate OCR - HUGE Software
** OCRe is a project developed by 2nd year EPITA students
** - website: http://huge.ocre.free.fr/
** - svn repository: http://code.google.com/p/ocre
**
** About this folder: /extraction
**   OCRec is the character extraction part of OCRe.
** About this file: /extraction/structures.h
**   This file contains declarations of all structures
**   about the extraction.
*/


/*
** This structure represents a binary image.
*/
struct s_binary_image
{
  char *name;
  int width;
  int height;
  int **data;  /* Matrix of binary integer */
  int *hproj;  /* Horizontal projection vector */
};

typedef struct s_binary_image t_binary_image;

/*
** This linked list represents the set of extracted characters.
*/
struct s_character_set
{
  int id;
  int id_line;
  int pos;
  int width;
  struct s_character_set *next;
};

typedef struct s_character_set t_character_set;

/*
** This linked list represents the set of extracted lines.
*/
struct s_line_set
{
  int id;
  int pos;
  int height;
  struct s_character_set *charlist;
  struct s_line_set *next;
};

typedef struct s_line_set t_line_set;

/*
** This structure is the result which will transmit to the
** recognition part. It contains the name of original image
** and the pointer to the linked list of lines.
*/
struct s_result_extraction
{
  char *name;
  t_line_set *linelist;
};

typedef struct s_result_extraction t_result_extraction;

/*
** This structure contains some informations about how
** the program begin and with which files. 
*/
struct s_launch_infos
{
  int display;
  char *inFile;
  char *outFile;
};

typedef struct s_launch_infos t_launch_infos;
