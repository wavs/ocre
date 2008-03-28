/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: /segmentation
 *   OCRec is the character extraction part of OCRe.
 * About this file: /segmentation/structures.h
 *   This file contains declarations of all structures
 *   about the segmentation.
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

#define UNKNOW 0;
#define TEXT 1;
#define IMAGE 2;

#endif /* STRUCTURES_H */

/**
 * This structure represents a matrix with its
 * dimensions.
 */
struct s_matrix
{
  unsigned int nbrows;
  unsigned int nbcols;
  int **data;
};

typedef struct s_matrix t_matrix;

/**
 * This structure represents a binary image.
 */
struct s_binary_image
{
  char *name;
  int width;
  int height;
  struct s_matrix *matrix;  /* Matrix of binary integer */
  int *hproj;  /* Horizontal projection vector */
  int *vproj;  /* Vertical projection vector */
};

typedef struct s_binary_image t_binary_image;

/**
 * This linked list represents the set of extracted characters.
 */
struct s_character_set
{
  int id;
  int id_line;
  int posx;
  int posy;
  int width;
  struct s_character_set *next;
};

typedef struct s_character_set t_character_set;

/**
 * This linked list represents the set of extracted lines.
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

/**
 * This structure is the result which will transmit to the
 * recognition part. It contains the name of original image
 * and the pointer to the linked list of lines.
 *
 * DEPRECATED
 */
struct s_result_extraction
{
  char *name;
  t_line_set *linelist;
};

typedef struct s_result_extraction t_result_extraction;

/**
 * This structure contains some informations about how
 * the program begin and with which files.
 * 
 * DEPRECATED
 */
struct s_launch_infos
{
  int display;
  char *inFile;
  char *outFile;
};

typedef struct s_launch_infos t_launch_infos;

/**************************************
 *  STRUCTURES FOR SEGMENTATION       *
 **************************************
 */

/**
 * This structure stores a set of two
 * coordinates.
 */
struct s_coordinate
{
  int x;
  int y;
};

typedef struct s_coordinate t_coordinate;

/**
 * This structure stores the coordinates of a 
 * connected component.
 */
struct s_cc_coordinate
{
  int xmin;
  int xmax;
  int ymin;
  int ymax;
};

typedef struct s_cc_coordinate t_cc_coordinate;

/**
 * This structure represents a connected component.
 */
struct s_cc_elt
{
  int id;
  int nbpix; /* Optionnal */
  struct s_cc_coordinate coord;
  short int chr; /* if >0 then cc is a character */
  struct s_cc_elt *next;
};

typedef struct s_cc_elt t_cc_elt;

/**
 * This structure represents a linked list of
 * connected components. 
 */
struct s_cc_list
{
  struct s_cc_elt *head;
  struct s_cc_elt *tail;
  int nbcc;
};

typedef struct s_cc_list t_cc_list;

/**
 * This structure represents a block in the image
 * with (or not) connnected components.
 */
struct s_block_elt
{
  int id;
  struct s_cc_list *cclist;
  int nbcc;
  int posx; /* Left upper corner x coordinate */
  int posy; /* Left upper corner y coordinate */
  int height;
  int width;
  int type; /* UNKNOW (0), TEXT (1), IMAGE (2) */
};

typedef struct s_block_elt t_block_elt;

/**
 * This structure represents a linked list of
 * blocks.
 */
struct s_block
{
  struct s_block_elt *elt;
  struct s_block *next;
};

typedef struct s_block t_block_list;

/**
 * This structure stores the left/right margin
 * and the header/footpage margin.
 */
struct s_limit
{
  int left_margin;
  int right_margin;
  int header_margin;
  int foot_margin;
};

typedef struct s_limit t_limit;

/**
 * This structure represents a queue.
 */
struct s_queue
{
  struct s_queue *prev;
  struct s_queue *next;
  void *data;
};

typedef struct s_queue t_queue;
