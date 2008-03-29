#include <unistd.h>
#include "main.h"
#include <pthread.h>
#include <glib.h>



/*
** opens an "About" dialog
*/
void on_about_show (gpointer user_data)
{
  GtkWidget* about;
  GtkWidget* label;
  /* so there is no unused parameter... */
  (void)user_data;
  /* create adn About dialog */
  about = gtk_dialog_new_with_buttons("About",
				      NULL,
				      GTK_DIALOG_MODAL |
				      GTK_DIALOG_DESTROY_WITH_PARENT,
				      GTK_STOCK_OK,
				      GTK_RESPONSE_ACCEPT,
				      NULL);
  /* text shown in the about box */
  label = gtk_label_new("OCRe - HUGE Software - 2008");
  /* destroy the widget when clicking on the cross */
  g_signal_connect_swapped (about,
			    "response",
			    G_CALLBACK (gtk_widget_destroy),
			    about);
  
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox),
		     label);
  
  gtk_widget_show_all(about);
  
  /* destroy the widget if clicks on OK */
  if (gtk_dialog_run(GTK_DIALOG (about)) ==
      GTK_RESPONSE_ACCEPT)
    {
      gtk_widget_destroy (about);
    }
}


/* fct qui balance du texte dans l'editeur */
void on_text_show (GtkImageMenuItem* test, gpointer user_data)
{
  GUI_* guisex;
  GtkTextBuffer *txtbuffer;
  
  /* so there's no unused parameter... */
  (void)test;
  guisex = (GUI_ *)user_data;
  
  txtbuffer = gtk_text_view_get_buffer
    (GTK_TEXT_VIEW(guisex->textview));

  gtk_text_buffer_set_text 
       (
	txtbuffer,
	"Hello\n",
	-1
	);
}


void save_as (char *text, char *filename)
{
  FILE *fp;

  fp = fopen(filename, "w");
  if(!fp)
    fprintf(stderr, "Can't open file\n");
  else
    fprintf(fp, text);
  fclose(fp);
}

void on_save_show (GtkImageMenuItem* test, gpointer user_data)
{
  GtkWidget* save;
  GUI_* guisex;
  GtkTextBuffer *txtbuffer;
  char *filename, *text;

  /* so there's no unused parameter... */
  (void)test;
  guisex = (GUI_ *)user_data;
  /* guisex->textview = gtk_text_view_new (); */
  txtbuffer = gtk_text_view_get_buffer(
	      GTK_TEXT_VIEW(guisex->textview));
  /* create a 'save file' dialog */
  save = gtk_file_chooser_dialog_new (NULL,
				      NULL,
				      GTK_FILE_CHOOSER_ACTION_SAVE,
				      GTK_STOCK_SAVE,
				      GTK_RESPONSE_ACCEPT,
				      GTK_STOCK_CANCEL,
				      GTK_RESPONSE_CANCEL,
				      NULL);
  gtk_file_chooser_set_do_overwrite_confirmation 
    (
     GTK_FILE_CHOOSER(save), 
     TRUE
     );

  /*if (!gtk_text_buffer_get_modified (txtbuffer))
    {*/
    gtk_file_chooser_set_current_folder 
      (
       GTK_FILE_CHOOSER (save), 
       "/"
       );
    gtk_file_chooser_set_current_name 
      (
       GTK_FILE_CHOOSER (save), 
       "Untitled"
       );
    gtk_text_buffer_set_modified (txtbuffer, FALSE);
  

 if (gtk_dialog_run (GTK_DIALOG (save)) == GTK_RESPONSE_ACCEPT)
   {
     GtkTextIter iStart, iEnd;
     
     filename = gtk_file_chooser_get_filename 
       (
	GTK_FILE_CHOOSER (save)
	);
     
     gtk_text_buffer_get_start_iter(txtbuffer, &iStart);
     gtk_text_buffer_get_end_iter(txtbuffer, &iEnd);

     text = gtk_text_buffer_get_text
       (
	GTK_TEXT_BUFFER(txtbuffer), 
	&iStart, 
	&iEnd, 
	FALSE
	);
     save_as(text, filename);
     g_free (filename);
   }  
 gtk_widget_destroy (save);

}

/*
** opens an "Open File" dialog
*/
void on_open_show (GtkImageMenuItem* test, gpointer user_data)
{
  GtkWidget* open;
  GUI_* guisex;
  /* so there's no unused parameter... */
  (void)test;
  guisex = (GUI_ *)user_data;

  
  /* create an open file dialog */
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
      /* get the filename */
      filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER
						(open));
      /* preprocessing */
      if (fork())
	execl("../bin/OCRed", "-i", filename, "-dev", NULL);
      /* open the file */
      gtk_image_set_from_file(GTK_IMAGE(guisex->image),filename);
    }

  gtk_widget_destroy (open);
}

/*
** the main function
*/
int main (int argc, char *argv[])
{
  GUI_* gui;
  
  gtk_init (&argc, &argv);
 
  gui = g_slice_new(GUI_);

  gui->gxml   = glade_xml_new ("../gui/gui.glade", NULL, NULL);
  gui->window = glade_xml_get_widget (gui->gxml, "window");
  gui->image  = glade_xml_get_widget (gui->gxml, "image");
  gui->textview = glade_xml_get_widget (gui->gxml, "textview");

  /* signal to quit the app */
  glade_xml_signal_connect (gui->gxml, "on_window_destroy",
			    G_CALLBACK (gtk_main_quit));
  /* signal to open the "Open File" dialog */
  glade_xml_signal_connect_data (gui->gxml, "on_open_show",
				 G_CALLBACK (on_open_show),
				 gui);
  glade_xml_signal_connect_data (gui->gxml, "on_save_show",
				 G_CALLBACK (on_save_show),
				 gui);
  glade_xml_signal_connect_data (gui->gxml, "on_text_show",
				 G_CALLBACK (on_text_show),
				 gui);
  /* signal to open the "about" dialog */
  glade_xml_signal_connect (gui->gxml, "on_about_show",
			    G_CALLBACK (on_about_show));

  gtk_widget_show (gui->window);
  gtk_main ();

  return 0;
}
