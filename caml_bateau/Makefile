FILES= main.ml
PROG=Bateau
CAMLFIND=ocamlfind
CAMLC=ocamlc
CAMLOPT=ocamlopt
CAMLDEP = ocamldep

all: main

main: $(FILES:.ml=.mli)
	$(CAMLC) -g -o $(PROG) $(FILES:.ml=.mli)
	$(CAMLC) -g -o $(PROG) $(FILES)

# Common rules


.SUFFIXES: .ml .mli .cmo .cmi .cmx

.ml.cmo:
	$(CAMLC) -g -o -c $<
.mli.cmi:
	$(CAMLFIND) ${CAMLC} -g -o-c $<
.ml.cmx:
	$(CAMLOPT) -c $<

depend:
	$(CAMLDEP) *.mli *.ml > .depend
clean:
	rm -f *~
	rm -f *.cm? *.o
	rm -f *#