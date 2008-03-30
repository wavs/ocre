(*
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre

	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe.
	About this file:	OCRed/detection.mli
		This is the detection.mli file.
*)
val proj_h_table        : (int32, Bigarray.int32_elt,
                           Bigarray.c_layout) Bigarray.Array1.t ref
val average             : int ref
val projection_h        : (int32, Bigarray.int32_elt,
                           Bigarray.c_layout) Bigarray.Array2.t ->
  unit
val proj_and_average    : (int32, Bigarray.int32_elt,
                           Bigarray.c_layout) Bigarray.Array2.t ->
  unit
val histo_to_file       : string -> unit
