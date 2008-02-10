(*
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre

	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe.
	About this file:	OCRed/surface.ml
		This is the surface.ml file.
*)
let image = ref (Sdlvideo.create_RGB_surface
                   []
                   ~w:600
                   ~h:600
                   ~bpp:32
                   ~rmask:Int32.zero
                   ~gmask:Int32.zero
                   ~bmask:Int32.zero
                   ~amask:Int32.zero)


let screen =ref (Sdlvideo.create_RGB_surface
                   []
                   ~w:600
                   ~h:600
                   ~bpp:32
                   ~rmask:Int32.zero
                   ~gmask:Int32.zero
                   ~bmask:Int32.zero
                   ~amask:Int32.zero)

(*  ref (Sdlvideo.set_video_mode *)
(*                     600 *)
(*                     600 *)
(*                     []) *)

let set_image path = image := Sdlloader.load_image path


let set_screen w h = screen := Sdlvideo.set_video_mode
  w
  h
  [`ANYFORMAT;
   `RESIZABLE;
   `DOUBLEBUF]


let dim surface =
  Sdlvideo.surface_dims surface

let taille surf =
  let (width,height,pitch) = Sdlvideo.surface_dims surf in
    (width,height)
