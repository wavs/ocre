#include "main.h"

void on_about_show (gpointer user_data)
{
  GtkWidget* about;
  GtkWidget* label;

  about = gtk_dialog_new_with_buttons("About",
				      NULL,
				      GTK_DIALOG_MODAL | 
				      GTK_DIALOG_DESTROY_WITH_PARENT,
				      GTK_STOCK_OK,
				      GTK_RESPONSE_ACCEPT,
				      NULL);
  label = gtk_label_new("OCRe - HUGE Software - 2008");

  g_signal_connect_swapped (about,
			    "response",
			    G_CALLBACK (gtk_widget_destroy),
			    about);

  gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox),
		     label);

  gtk_widget_show_all(about);

  if (gtk_dialog_run(GTK_DIALOG (about)) == 
      GTK_RESPONSE_ACCEPT)
    {
      gtk_widget_destroy (about);
    }
}

/* opens an "Open File" dialog */
void on_open_show (GtkImageMenuItem* test, gpointer user_data)
{
  GtkWidget* open;
  GUI_* guisex;

  guisex = (GUI_ *)user_data;
  
  open = gtk_file_chooser_dialog_new (NULL,
				      NULL,
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_OPEN,
				      GTK_RESPONSE_ACCEPT,
				      GTK_STOCK_CANCEL,
				      GTK_RESPONSE_CANCEL,
				      NULL);
  gtk_widget_show(open);

  if (gtk_dialog_run (GTK_DIALOG (open)) == GTK_RESPONSE_ACCEPT)
    {
      char* filename;
      // get the filename
      filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER 
						(open));
      // open the file
      gtk_image_set_from_file(GTK_IMAGE(guisex->image),filename);
    }
  
  gtk_widget_destroy (open);
}

int main (int argc, char *argv[])
{
  GUI_* gui;

  gtk_init (&argc, &argv);

  gui = g_slice_new(GUI_);

  gui->gxml   = glade_xml_new ("gui.glade", NULL, NULL);
  gui->window = glade_xml_get_widget (gui->gxml, "window");
  gui->image  = glade_xml_get_widget (gui->gxml, "image");

  // signal to quit the app
  glade_xml_signal_connect (gui->gxml, "on_window_destroy",
			    G_CALLBACK (gtk_main_quit));
  // signal to open the "Open File" dialog
  glade_xml_signal_connect_data (gui->gxml, "on_open_show",
				 G_CALLBACK (on_open_show),
				 gui);
  // signal to open the "about" dialog
  glade_xml_signal_connect (gui->gxml, "on_about_show",
			    G_CALLBACK (on_about_show));

  gtk_widget_show (gui->window);                
  gtk_main ();

  return 0;
}
