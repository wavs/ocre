/*
** OCRe - The ultimate OCR - HUGE Software
** OCRe is a project developed by 2nd year EPITA students
** - website: http://huge.ocre.free.fr/
** - svn repository: http://code.google.com/p/ocre
**
** About this folder: /extraction
**   OCRec is the character extraction part of OCRe.
** About this file: /extraction/tools.c
**   This file contains some useful functions.
*/

/*
** This function determines if the extension of a
** filename is ".bmp".
*/
int is_bmp(char *filename)
{
  int i;

  i = 0;
  while (filename[i] != '\0')
    {
      i++;
    }
  if (i >= 4)
    {
      i--;
      if ((filename[i] == 'p')
	  && (filename[i-1] == 'm')
	  && (filename[i-2] == 'b')
	  && (filename[i-3] == '.'))
	{
	  return 1;
	}
    }
  return 0;
}
