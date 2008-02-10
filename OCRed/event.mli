(*
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre

	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe.
	About this file:	OCRed/eventhandler.mli
		This is the eventhandler.mli file.
*)
exception Error_windows
exception Quit_onmouse
exception Nothing_to_be_done
exception Quit_input
val rotate : unit -> unit
val action : unit -> unit
val run : unit -> unit
