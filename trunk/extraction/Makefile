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
CFLAGS= -W -Wall -pedantic -Werror -g

# Target
TARGET= extract

# Source files
CSOURCES= args launch process init infos tools pixel binarization projections extraction graphics event free

# Set of source files and object files
SOURCEFILES = $(CSOURCES:=.c)
OBJECTFILES = $(CSOURCES:=.o)

# Compiling files
$(TARGET): $(OBJECTFILES)
	@echo "\n=== Linking files ==="
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTFILES)

.c.o:
	@echo "\n---" $@ "---"
	$(CC) $(CFLAGS) `sdl-config --cflags --libs` -c -o $@ $<

depend:
	makedepend -I $(SOURCEFILES)

clean:
	rm -f *~ *.o core

bak:
	cp *.[ch] Makefile Backup/

# DO NOT DELETE
