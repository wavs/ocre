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
