(*
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre

	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe.
	About this file:	OCRed/surface.mli
		This is the surface.mli file.
*)
val image : Sdlvideo.surface ref
val screen : Sdlvideo.surface ref
val set_image : string -> unit
val set_screen : int -> int -> Sdlvideo.surface
val dim : Sdlvideo.surface -> int * int * int
