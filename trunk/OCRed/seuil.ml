(* 
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre
	
	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe. 
	About this file:	OCRed/seuil.ml
		This is the seuil.ml file.
*)

(*****************************************************)
(*SEUIL*)
(*****************************************************)

(*****************************************************)
(**)
let seuil = ref 0

let seuillage s =
  let (w,h,p) = Sdlvideo.surface_dims s in
    for i = 0 to w do
      for j = 0 to h do
	let (r,g,b) = Sdlvideo.get_pixel_color s i j in
	  (* Seuil à déterminer *)
	  if ((r+g+b) < !seuil) then
	    Sdlvideo.put_pixel_color s i j (0,0,0)
	  else
	    Sdlvideo.put_pixel_color s i j (255,255,255)
      done
    done

let main()=
  if (!Path.output <> "") then
    begin
      seuillage !Surface.image;
      Sdlvideo.save_BMP !Surface.image !Path.output;
    end
  else
    begin
      seuillage !Surface.image;
      Sdlvideo.save_BMP !Surface.image "tresholded.bmp";
    end
    
    
    
