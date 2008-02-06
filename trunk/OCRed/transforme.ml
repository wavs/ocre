(* 
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre
	
	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe. 
	About this file:	OCRed/main.ml
		This is the main.ml file.
*)

(**{3 fonction de transformation } *)

let surf_to_matrix surf =
 let (width,height,pitch) = Sdlvideo.surface_dims surf
 in let my_matrix =
   (Bigarray.Array2.create Bigarray.int32 Bigarray.c_layout width height) in
  for j=0 to (height - 1) do
   for i=0 to (width - 1) do
    Bigarray.Array2.set my_matrix i j (Sdlvideo.get_pixel surf i j)
 done;
 done;
my_matrix


let matrix_to_surf matrix =
  let width = Bigarray.Array2.dim1 matrix in
  let height = Bigarray.Array2.dim2 matrix in 
  let my_surf = Sdlvideo.create_RGB_surface []  ~w:width 
                                                ~h:height 
                                                ~bpp:24
                                                ~bmask:Int32.zero
                                                ~rmask:Int32.zero
                                                ~gmask:Int32.zero
                                                ~amask:Int32.zero in
for j=0 to (height - 1) do
for i=0 to (width - 1) do
  Sdlvideo.put_pixel my_surf i j (Bigarray.Array2.get matrix i j)
done;
done;
my_surf
