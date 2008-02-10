(*
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre

	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe.
	About this file:	OCRed/loader.ml
		This is the loader.ml file.
*)

(** This module contains functions for basic rotations of matrices
 but also for surfaces of Sdlvideo.surface type.*)

(** {3 Main functions} *)
val pi : float
val rad : float
val degree_to_rad : int -> float
val angle : float ref
val create_angle : int -> unit

val direct_float : float -> float -> float -> int * int
(** process rotation of point (float) needed by simple_surg *)

val direct_int : int -> int -> float -> int * int
val inverse_float : float -> float -> float -> int * int
val inverse_int : int -> int -> float -> int * int
val hypotenuse : Sdlvideo.surface -> int
val center : Sdlvideo.surface -> int * int
val mean_of_float : float -> int
val simple_surf : Sdlvideo.surface -> float -> Sdlvideo.surface
val hard_of_surf : Sdlvideo.surface -> float -> Sdlvideo.surface
