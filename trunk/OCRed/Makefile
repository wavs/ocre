PKG=sdl,sdl.sdlimage,sdl.sdlmixer,sdl.sdlttf
FILES1=path.ml surface.ml transforme.ml rotation.ml argument.ml event.ml
FILES2= main.ml
LIBRARY= bigarray.cma sdlloader.cma
PROG=OCRed

CC=gcc
CFLAGS= -W -Wall -Werror -ansi -pedantic -g -pipe
GTKFLAGS= `gtk-config --cflags` `gtk-config --libs`

CAMLFIND=ocamlfind
CAMLC=ocamlc
CAMLOPT=ocamlopt
CAMLDEP = ocamldep
SDLFLAGS= -linkpkg -package ${PKG}

CAMLOPTFLAGS= -o

INSTALL = /usr/bin/install -c
INSTALLDATA = /usr/bin/install -c -m 644
prefix= /usr/local
binprefix=
bindir= ${prefix}/bin
infodir=${prefix}/info

all: main

main: $(FILES1:.ml=.mli) $(FILES2:.ml=.mli)
	$(CAMLFIND) $(CAMLC) -g -o $(PROG) $(SDLFLAGS) $(FILES1:.ml=.mli) $(FILES2:.ml=.mli)
	$(CAMLFIND) $(CAMLC) -g -o $(PROG) $(SDLFLAGS) $(FILES1) $(FILES2)

# Common rules
.SUFFIXES: .ml .mli .cmo .cmi .cmx

.ml.cmo:
	$(CAMLFIND) $(CAMLC) $(SDLFLAGS)-g -o -c $<

.mli.cmi:
	$(CAMLFIND) ${CAMLC} $(SDLFLAGS)-g -o-c $<

.ml.cmx:
	$(CAMLOPT) $(CAMLOPTFLAGS) -c $<


depend:
	$(CAMLDEP) *.mli *.ml > .depend
clean:
	rm -f *~
	rm -f *.cm? *.o
	rm -f $(PROG)
	rm -f *#