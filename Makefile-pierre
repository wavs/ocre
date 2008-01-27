# OCRe Project - HUGE Software - EPITA SPE
# Makefile made by guilbe_p@epita.fr
# 2008/01/17 6:09 pm
#!/usr/bin/sh

SHELL= /bin/sh


CC=gcc
CFLAGS= -W -Wall -Werror -ansi -pedantic -g -pipe
GTKFLAGS= `gtk-config --cflags` `gtk-config --libs`

CAMLC=ocamlc.opt
CAMLOPT=ocamlopt.opt
CAMLDEP = ocamldep
CAMLLEX = ocamllex
CAMLYACC = ocamlyacc
CAMLFLAGS= -o
CAMLOPTFLAGS= -o

PROJECT=OCRe
srcC= main.c
srcO= main.ml
FILES= ${srcO} ${srcC}
H=${FILES:.c=.h}
OBJ=${FILES:.c=.o}
CMO=${FILES:.ml=.cmo}
CMX=${FILES:.ml=.cmx}

PROGC=OCReg OCRec 
# Reg is the gui
# Rec is the edge character detection
PROGO=OCRed OCRen
# Red is the preprocessing image software 
# Ren is the learning program
# fixme pour un progocaml et une var PROG general
PROG=OCRe

INSTALL = /usr/bin/install -c
INSTALLDATA = /usr/bin/install -c -m 644
prefix= /usr/local
binprefix=
bindir= ${prefix}/bin
infodir=${prefix}/info

.PHONY: all
all: ${PROGC} ${PROGO} ${PROG}.info #fixme pour un progocaml

${PROGC}: ${OBJ} ${H} ${} 

${PROGO}: ${CMO}
	${CAMLC} ${CAMLFLAGS} ${PROGO} ${CMO}

${PROGO}.OPT: ${CMX}
	${CAMLOPT} ${CAMLOPTFLAGS} ${PROGO}.opt ${CMX}
${PROG}.info: ${PROG}.texinfo
	makeinfo ${PROG}.texinfo

.PHONY: install
install: all
	${INSTALL} ${PROGC} ${bindir}/${binprefix}

# Common Rules
.SUFFIXES: .ml .mli .cmo .cmi .cmx

.ml.cmo:
	${CAMLC} ${CAMLFLAGS} -c $<s
.mli.cmi:
	${CAMLC} ${CAMLFLAGS} -c $<
.ml.cmx:
	${CAMLOPT} ${CAMLOPTFLAGS} -c $<
.mll.cmo:
	$(CAMLLEX) $<
	$(CAMLC) -c $*.ml
.mll.cmx:
	$(CAMLLEX) $<
	$(CAMLOPT) -c $*.ml
.mly.cmo:
	$(CAMLYACC) $<
	$(CAMLC) -c $*.mli
	$(CAMLC) -c $*.ml

.mly.cmx:
	$(CAMLYACC) $<
	$(CAMLOPT) -c $*.mli
	$(CAMLOPT) -c $*.ml

.mly.cmi:
	$(CAMLYACC) $<
	$(CAMLC) -c $*.mli

.mll.ml:
	$(CAMLLEX) $<

.mly.ml:
	$(CAMLYACC) $<

depend:
	$(CAMLDEP) *.mli *.ml > .depend
clean:
	rm -f *~ .*~ #*#
	rm -f *.cm? *.o
	rm -f ${PROGC}
	rm -f ${PROCO}
	rm -f ${PROC0}.opt

include .makedep
#
# END
#