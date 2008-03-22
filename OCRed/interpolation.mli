(*
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre

	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe.
	About this file:	OCRed/interpolation.mli
		This is the interpolation.mli file.
*)
val roundf              : float -> int
val inverse_resize      : int -> int -> float -> float -> int * int
val is_in_rect          : int -> int -> int -> int -> bool
val resize              : Sdlvideo.surface -> int -> int -> Sdlvideo.surface
val resize_percent      : Sdlvideo.surface -> int -> Sdlvideo.surface
