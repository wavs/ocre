/**
 * OCRe - The ultimate OCR - HUGE Software
 * OCRe is a project developed by 2nd year EPITA students
 * - website: http://huge.ocre.free.fr/
 * - svn repository: http://code.google.com/p/ocre
 *
 * About this folder: segmentation/
 *   OCRec is the character extraction part of OCRe.
 * About this file: segmentation/export.c
 *   This file contains functions about the exportation.
 */

#include "export.h"

void exportLetter (FILE *f, t_cc_elt* letter)
{
    fprintf(f, "\t\t\t<c x[%i,%i] y[%i,%i] />\n",
            letter->coord.xmin,
            letter->coord.xmax,
            letter->coord.ymin,
            letter->coord.ymax);
}

void exportWord (FILE* f, t_word_elt* word)
{
    t_cc_elt* letter;

    fprintf(f, "\t\t<w x[%i,%i] y[%i,%i]>\n",
            word->coord.xmin,
            word->coord.xmax,
            word->coord.ymin,
            word->coord.ymax);

    letter = word->cclist->head;
    while (letter)
    {
        exportLetter (f, letter);
        letter = letter->next;
    }

    fprintf(f, "\t\t</w>\n");
}



void exportLine (FILE* f, t_line_elt* line)
{
    t_word_elt* word;

    fprintf(f, "\t<l x[%i,%i] y[%i,%i]>\n",
            line->coord.xmin,
            line->coord.xmax,
            line->coord.ymin,
            line->coord.ymax);

    word = line->wordlist->head;
    while (word)
    {
        exportWord (f, word);
        word = word->next;
    }

    fprintf(f, "\t</l>\n");
}



void exportParagraph (FILE* f, t_paragraph_elt* paragraph)
{
    t_line_elt* line;

    fprintf(f, "<p x[%i,%i] y[%i,%i]>\n",
            paragraph->coord.xmin,
            paragraph->coord.xmax,
            paragraph->coord.ymin,
            paragraph->coord.ymax);

    line = paragraph->linelist->head;
    while (line)
    {
        exportLine (f, line);
        line = line->next;
    }

    fprintf(f, "</p>\n");
}

int main (t_paragraph_list* document, char* filename)
{
    FILE *f;
    t_paragraph_elt* para;
    f = fopen(filename, "w");

    if(!f)
      fprintf(stderr, "Can't open file: %s\n", filename);
    else
    {
      para = document->head;
      while (para)
        {
          exportParagraph (f, para);
          para = para->next;
        }
    }

    fclose(f);
    return 0;
}
