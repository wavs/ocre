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
val display : bool ref
val set_path_image : string -> unit
val set_path_output : string -> unit
val set_angle : int -> unit
val speclist : (string * Arg.spec * string) list
val usage : string
