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
val proj_h_table        : (int32, Bigarray.int32_elt,
                           Bigarray.c_layout) Bigarray.Array1.t ref
val roundf              : float -> int
val inverse_resize      : int -> int -> float -> float -> int * int
val is_in_rect          : int -> int -> int -> int -> bool
val resize              : Sdlvideo.surface -> int -> int -> Sdlvideo.surface
val resize_percent      : Sdlvideo.surface -> int -> Sdlvideo.surface
val resize_percent_unit : Sdlvideo.surface -> int -> unit
val sommet_of_h         : (int32, Bigarray.int32_elt,
                           Bigarray.c_layout) Bigarray.Array1.t -> int
val projection_h        : (int32, Bigarray.int32_elt,
                           Bigarray.c_layout) Bigarray.Array2.t -> unit
val print_tabh          : unit -> unit
val histo_to_file       : string -> unit
