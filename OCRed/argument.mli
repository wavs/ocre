(*
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre

	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe.
	About this file:	OCRed/argument.mli
		This is the argument.mli file.
*)
val display             : bool ref
val seuil               : bool ref
val rotate              : bool ref
val resize              : bool ref
val percent             : bool ref
val dev                 : bool ref
val percent_res         : int ref
val resize_of_x         : int ref
val resize_of_y         : int ref
val speclist            : (string * Arg.spec * string) list
val usage               : string
