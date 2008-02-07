/*
** OCRe - The ultimate OCR - HUGE Software
** OCRe is a project developed by 2nd year EPITA students
** - website: http://huge.ocre.free.fr/
** - svn repository: http://code.google.com/p/ocre
**
** About this folder: /extraction
**   OCRec is the character extraction part of OCRe.
** About this file: /extraction/free.h
**   This is the header of "free.c".
*/


/*
** This function frees the structure of binary image.
*/
void free_pic(t_binary_image *pic);

/*
** This function frees the structure of the extraction result.
*/
void free_result(t_result_extraction *result);

/*
** This function frees all structures from the extraction part.
*/
void free_all(t_binary_image *pic, t_result_extraction *result);
