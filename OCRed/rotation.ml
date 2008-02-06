(* 
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre
	
	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe. 
	About this file:	OCRed/rotation.ml
		This is the rotation.ml file.
*)
let rotate x y theta=
  let x' =    x*.cos(theta) -. y*.sin(theta) in
  let y' =    x*.sin(theta) +. y*.cos(theta) in
    (abs_float x',abs_float y')

let surf_to_surf=
