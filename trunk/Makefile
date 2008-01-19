# OCRe Project - HugeTeam - EPITA SPE
# Makefile made by guilbe_p@epita.fr
# 2008/01/17 6:09 pm
#!/usr/bin/sh

CC=gcc
OCAMLC=ocamlc.opt
OCAMLOPT=ocamlopt.opt
CFLAGS= -W -Wall -Werror -ansi -pedantic -g -pipe
GTKFLAGS= `gtk-config --cflags` `gtk-config --libs`

PROJECT=OCRe
FILES= main.c
H=${FILES:.c=.h}
CMO=${FILES:.ml=.cmo}
CMX=${FILES:.ml=.cmx}
PROGC=OCReGUI

#fixme pour un progocaml

all: ${PROGC} #fixme pour un progocaml

${PROG}: fichiers 

# Common Rules
.SUFFIXES: .ml .mli .cmo .cmi .cmx

.ml.cmo:
	${OCAMLC} ${OCAMLFLAGS} -c $<
.mli.cmi:
	${OCAMLC} ${OCAMLFLAGS} -c $<
.ml.cmx:
	${OCAMLOPT} ${OCAMLOPTFLAGS} -c $<

depend:
	ocamldep *.mli *.ml > .depend
clean:
	rm -f *~
	rm -f *.cm? *.o
	rm -f ${EXEC}

include .makedep
#
# END
#