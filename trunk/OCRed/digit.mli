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
                 
val division : 'a list -> 'a list * 'a list
val fusion : 'a list -> 'a list -> 'a list
val tri_fusion : 'a list -> 'a list
val tabtolist : 'a array -> 'a list
val mediane : 'a list -> 'a
val filtremed :
  (int32, 'a, 'b) Bigarray.Array2.t ->
  (int32, Bigarray.int32_elt, Bigarray.c_layout) Bigarray.Array2.t                                             
val lectureliste : int list -> unit
val lecturebigarray : (int32, 'a, 'b) Bigarray.Array2.t 
-> unit                                                
val main2 : unit -> unit
val main3 : unit -> unit
val main4 : unit -> unit
val main : unit -> unit
