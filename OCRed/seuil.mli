(* 
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre
	
	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe. 
	About this file:	OCRed/seuil.mli
		This is the seuil.mli file.
*)


val seuil : int ref
val seuillage : Sdlvideo.surface -> unit
val main : unit -> unit
