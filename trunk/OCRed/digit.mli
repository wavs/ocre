(*
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre

	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe.
	About this file:	OCRed/digit.mli
		This is the digit.mli file.
*)

val filtremed :
  (int32, 'a, 'b) Bigarray.Array2.t ->
  (int32, Bigarray.int32_elt, Bigarray.c_layout) Bigarray.Array2.t
val main : unit -> unit
