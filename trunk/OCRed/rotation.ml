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

let mean_of_float x = match (modf x) with
  | (x,y) when (x >= 0.5)-> int_of_float(floor(y +. 1.))
  | (_,y) -> int_of_float(floor(y))

let direct_float x y theta=
  let x' =    x*.cos(theta) -. y*.sin(theta) in
  let y' =    x*.sin(theta) +. y*.cos(theta) in
    (mean_of_float x', mean_of_float y')

let direct_int i j theta=
  let x = float_of_int i in
  let y = float_of_int j in
  let x' =    x*.cos(theta) -. y*.sin(theta) in
  let y' =    x*.sin(theta) +. y*.cos(theta) in
    (mean_of_float x', mean_of_float y')

let inverse_float x y theta=
  let x' =    x*.cos(~-.theta) +. y*.sin(~-.theta) in
  let y' =    x*.sin(~-.theta) -. y*.cos(~-.theta) in
    (mean_of_float x',mean_of_float y')

let inverse_int i j theta=
  let x = float_of_int i in
  let y = float_of_int j in
  let x' =    x*.cos(~-.theta) +. y*.sin(~-.theta) in
  let y' =    x*.sin(~-.theta) -. y*.cos(~-.theta) in
    (mean_of_float x',mean_of_float y')

let hypotenuse surface =
  let (width,height,pitch) = Sdlvideo.surface_dims surface in
  let  hyp = sqrt(float_of_int(height*height + width*width)) in
   mean_of_float hyp

let center surface =
  let (width,height,pitch) = Surface.dim surface in
    match (width,height) with
      |(_,_) -> (x / 2,y / 2)


let is_in_rect x y width height =
  if (x > 0) && (x < width) && (y > 0) && (y <height) then
    true
  else
    false

let simple_surf surf angle=
  let (width,height,pitch) = Surface.dim surf in
  let (cy,cx) = center surf in
  let cote_hypot = hypotenuse surf  in
  let demi_hypot = cote_hypot / 2 in
  let my_output = Transforme.bigarray2 cote_hypot cote_hypot in
(** my output come from bigarray2 function in Transforme module*)
  let my_input = Transforme.surf_to_matrix surf in
    for i=0 to (width - 1) do
      for j=0 to (height - 1) do
        let (x,y) = direct_int (i - cx) (j - cy) angle in
            Bigarray.Array2.set
                my_output
                (x + demi_hypot)
                (y + demi_hypot)
                (Bigarray.Array2.get
                   my_input
                   (i)
                   (j));
      done;
    done;
  Transforme.matrix_to_surf my_output
