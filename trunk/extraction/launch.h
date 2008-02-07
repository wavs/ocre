/*
** OCRe - The ultimate OCR - HUGE Software
** OCRe is a project developed by 2nd year EPITA students
** - website: http://huge.ocre.free.fr/
** - svn repository: http://code.google.com/p/ocre
**
** About this folder: /extraction
**   OCRec is the character extraction part of OCRe.
** About this file: /extraction/launch.h
**   This is the header of "launch.c".
*/


/*
** This function starts the extraction process with
** the display option.
*/
void launchProgramWithDisplay(t_launch_infos *infos);

/*
** This function starts the extraction process without
** the display option.
*/
void launchProgramWithoutDisplay(t_launch_infos *infos);
