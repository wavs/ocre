#
# OCRe - The ultimate OCR - HUGE Software
# OCRe is a project developed by 2nd year EPITA students
# - website: http://huge.ocre.free.fr/
# - svn repository: http://code.google.com/p/ocre
#
# About this folder: /extraction
#   OCRec is the character extraction part of OCRe.
# About this file: /extraction/Makefile
#   This is the makefile of the extraction part.

# Compiler
CC=gcc

# Flags
CFLAGS= -W -Wall -pedantic -ansi -Werror -pipe -g

# Target
TARGET= extract

$(TARGET): main.c args.c tools.c launch.c process.c init.c infos.c pixel.c binarization.c projections.c extraction.c graphics.c event.c free.c
	gcc $(CFLAGS) `sdl-config --cflags --libs` main.c args.c tools.c launch.c process.c init.c infos.c pixel.c binarization.c projections.c extraction.c graphics.c event.c free.c -o $(TARGET)

clean:
	rm -f *~ *.o core
	rm -f extract

bak:
	cp *.[ch] Makefile Backup/

