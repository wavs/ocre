OCAMLC=ocamlc
OCAMLOPT=ocamlopt
.SUFFIXES: .ml .mli .cmo .cmi .cmx

BINARY=checkdapr0n
FILES=pornhub.ml
MLI=${FILES:.ml=.mli} #auto generation of .mli files (if not exist)
CMI=${FILES:.ml=.cmi}
CMO=${FILES:.ml=.cmo}

NATIVE=${BINARY}.opt
CMX=${FILES:.ml=.cmx} #Native files

############################################
########   Interface compilation   #########
############################################
#.ml.mli:
#	${OCAMLC} -i $< > $@
.mli.cmi: ${MLI}
	${OCAMLC} -c $<
############################################
#########   Bytecode compilation   #########
############################################
.ml.cmo:
	${OCAMLC} -c $<

all:${BINARY}

${BINARY}: ${CMI} ${CMO}
	${OCAMLC} -o $@ ${CMO}
############################################
##########   Native compilation   ##########
###########################################
.ml.cmx:
	${OCAMLOPT} -c $<

${NATIVE}: ${CMI} ${CMX}
	${OCAMLOPT} -o $@ ${CMX}
############################################
##############    Checking   ###############
############################################
#check:
	#${OCAMLC} -i ${FILES}
#
############################################
##############    Cleaning   ###############
############################################

clean:
	rm -rf *.cmo *.cmi *~

mrclean: clean
	rm -rf ${BINARY}
	rm -rf ${NATIVE}


#   (\_/)   #
 #  ('.')  #
  # ()_() #
   # EOF #
  # (\_/) #
 #  ('.')  #
#   ()_()   #
