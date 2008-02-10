install:
	gcc -Wall -g -o gui main.c -export-dynamic `pkg-config gtk+-2.0 libglade-2.0 --cflags --libs`
clean:
	rm -f gui
	rm -f *~ # emacs temp files
	rm -f *#
