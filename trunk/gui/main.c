#include "main.h"

void on_about_show (GtkImageMenuItem* lol, gpointer user_data)
{
  GUI_* guisex;

  guisex = (GUI_ *)user_data;

  gtk_widget_show(guisex->aboutdialog);
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
  glade_xml_signal_connect_data (gui->gxml, "on_about_show",
				 G_CALLBACK (on_about_show),
				 gui);

  gtk_widget_show (gui->window);                
  gtk_main ();

  return 0;
}
