/* pour compiler :
gcc -Wall -g -o main main.c `pkg-config --cflags --libs gtk+-2.0 
libglade-2.0`
*/
#include "/usr/local/include/gtk-2.0/gtk/gtk.h"
#include "/usr/local/include/libglade-2.0/glade/glade.h"
#include <stdlib.h>

typedef struct {
  GladeXML*  gxml;
  GtkWidget* window;
  GtkWidget* image;
}GUI_;
void on_open_show (GtkImageMenuItem* test, gpointer user_data);

int main (int argc, char *argv[]);
