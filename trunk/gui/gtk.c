#include <stdlib.h>
#include "/opt/gtk/include/gtk-2.0/gtk/gtk.h"

int main (int argc, char *argv[])
{
    GladeXML        *gxml;
    GtkWidget       *window;

    gtk_init (&argc, &argv);

    gxml = glade_xml_new ("tutorial.glade", NULL, NULL);
    window = glade_xml_get_widget (gxml, "window");
    glade_xml_signal_connect (gxml, "on_window_destroy",
                              G_CALLBACK (gtk_main_quit));

    g_object_unref (G_OBJECT (gxml));

    gtk_widget_show (window);
    gtk_main ();

    return 0;
}
