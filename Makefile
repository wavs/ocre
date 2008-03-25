#
# OCRe - The ultimate OCR - HUGE Software
# OCRe is a project developed by 2nd year EPITA students
# - website: http://huge.ocre.free.fr/
# - svn repository: http://code.google.com/p/ocre
#   
# About this file: General Makefile of the OCRe project.
#

all: red ext graph

red:
	rm -rf bin && mkdir bin && cd OCRed && make && mv OCRed ../bin && cd ../ 

ext:
	cd extraction && make && mv extract ../bin && cd ../ 

graph:
	cd gui && make && mv gui ../bin && cd ../ 



clean:
	cd OCRed/ && make clean && cd ../extraction/ && make clean && cd ../gui/ && make clean && cd ../

cleanc:
	rm -rf bin
