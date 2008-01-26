/*
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre

	About this folder:	OCReg
		OCRed is the GUI part of OCRe. 
	About this file:	OCReg/main.c
		This is the main file.
*/

#include "main.h"

int     main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *label;
  
  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_border_width (GTK_CONTAINER (window), 10);
  
  label = gtk_label_new ("Hello World");
  gtk_container_add (GTK_CONTAINER (window), label);
  gtk_widget_show (label);

  gtk_widget_show (window);

  gtk_main ();

  return 0;
}
