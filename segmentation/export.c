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

void exportLetter (FILE* f, t_letter_elt)
{
    int mot, xmin, xmax, ymin, ymax;
    
    xmin = lettre->coord->xmin;
    xmax = lettre->coord->xmax;
    ymin = lettre->coord->ymin;
    ymax = lettre->coord->ymax;
    
    mot = fprintf(f, "<letter:%i x[%i,%i] y[%i,%i] />\n",
        lettre->id, xmin, xmax, ymin, ymax);
}

void exportWord (FILE* f, t_word_elt word)
{
    int mot, xmin, xmax, ymin, ymax;
    t_letter_elt lettre;
    
    xmin = word->coord->xmin;
    xmax = word->coord->xmax;
    ymin = word->coord->ymin;
    ymax = word->coord->ymax;
    
    mot = fprintf(f, "<word:%i x[%i,%i] y[%i,%i]>\n", 
        word->id, xmin, xmax, ymin, ymax);
    lettre = word->letter;
    
    while (lettre)
    {
        exportLetter (f, lettre);
        lettre = lettre->next;
    }
    
    mot = fprintf(f, "</word:%i>\n", word->id);
}

void exportParagraph (FILE* f, t_paragraph_elt paragraph)
{
    int para, xmin, xmax, ymin, ymax;
    t_word_elt mot;
    
    xmin = paragraph->coord->xmin;
    xmax = paragraph->coord->xmax;
    ymin = paragraph->coord->ymin;
    ymax = paragraph->coord->ymax;
    
    para = fprintf(f, "<paragraph:%i x[%i,%i] y[%i,%i]>\n", 
        word->id, xmin, xmax, ymin, ymax);
    mot = paragraph->word;
    
    while (mot)
    {
        exportLetter (f, mot);
        mot = mot->next;
    }
    
    para = fprintf(f, "</paragraph:%i>\n", word->id);
}

int exportCC (t_cc_list cc)
{
    FILE *fp;
    char* doc;
    int doc, xmin, xmax, ymin, ymax;
    fp = fopen(filename, "w");
    
    if(!fp)
      fprintf(stderr, "Can't open file\n");
    else
    {
        xmin = document->coord->xmin;
        xmax = document->coord->xmax;
        ymin = document->coord->ymin;
        ymax = document->coord->ymax;

        doc = fprintf(f, "<document x[%i,%i] y[%i,%i]>\n", 
            xmin, xmax, ymin, ymax);
        para = document->paragraph;

        while (para)
        {
            exportLetter (f, mot);
            mot = mot->next;
        }

        para = fprintf(f, "</document>%s\n", "");
    }
    fclose(fp);
    return 0;
}