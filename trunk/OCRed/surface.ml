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
let image = Sdlloader.load_image Path.image
let (width,height,pitch) = Sdlvideo.surface_dims image
let screen = Sdlvideo.set_video_mode width height [`ANYFORMAT;
                                                   `RESIZABLE;
                                                   `DOUBLEBUF]
