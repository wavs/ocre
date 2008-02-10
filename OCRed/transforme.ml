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

let bigarray2 width height = (Bigarray.Array2.create
                                Bigarray.int32
                                Bigarray.c_layout
                                width
                                height)
(**we create this function to avoid lines of more than 72 characters*)

let shift_pixel input output ax ay bx by =
   Bigarray.Array2.set output bx by (Bigarray.Array2.get input ax ay)

let surf_to_matrix surf =
 let (width,height,pitch) = Sdlvideo.surface_dims surf
 in let my_matrix =
   (Bigarray.Array2.create
      Bigarray.int32
      Bigarray.c_layout
      width
      height) in
  for j=0 to (height - 1) do
   for i=0 to (width - 1) do
    Bigarray.Array2.set my_matrix i j (Sdlvideo.get_pixel surf i j)
 done;
 done;
my_matrix


let matrix_to_surf matrix =
  let width = Bigarray.Array2.dim1 matrix in
  let height = Bigarray.Array2.dim2 matrix in
  let rm = Int32.of_int(255) in
  let gm = Int32.of_int(255) in
  let bm = Int32.of_int(255) in
  let am = Int32.of_int(255) in
  let my_surf = Sdlvideo.create_RGB_surface
    [`SWSURFACE;`SRCCOLORKEY;`SRCALPHA]
    ~w:width
    ~h:height
    ~bpp:32
    ~rmask:rm
    ~gmask:gm
    ~bmask:bm
    ~amask:am in
for j=0 to (height - 1) do
for i=0 to (width - 1) do
  Sdlvideo.put_pixel my_surf i j (Bigarray.Array2.get matrix i j)
done;
done;
my_surf

(*FIXME for color probleme*)
(* let matrix2tomatrix1 matrix = *)
