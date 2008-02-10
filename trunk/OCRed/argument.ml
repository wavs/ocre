(*
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre

	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe.
	About this file:	OCRed/argument.ml
		This is the argument.ml file.
*)

(** {2 definition of functions for arguments} *)
let display = ref false
let seuil = ref false
let rotate = ref false

let set_path_image s =
  Path.create_image s;
  Surface.set_image !Path.image

let set_path_output s =
  Path.output := s

let set_seuil i =
  Seuil.seuil := i;
  seuil := true


let set_angle a =
  Rotation.create_angle a;
    rotate := true

let speclist = [
  ("-o",
   Arg.String (fun s -> set_path_output s),
   "output path of your ouput image");
  ("-i",
   Arg.String (fun s -> set_path_image s),
   "input path of your input image");
  ("-a",
   Arg.Int (fun i -> set_angle i),
   "integer Angle in degree");
  ("-d",
   Arg.Set display,
   " allows to see your image being transformed");
  ("-s",
   Arg.Int (fun i -> set_seuil i),
   "integer  Treshold : Color to Black&White");
  ("--output",
   Arg.String (fun s -> set_path_output s),
   "output path of your ouput image");
  ("--image",
   Arg.String (fun s -> set_path_image s),
   "input path of your input image");
  ("--angle",
   Arg.Int (fun i -> set_angle i),
   "Angle in degree");
  ("--display",
   Arg.Set display,
   " Useless option")
]

let usage = "Usage: -image [path] -angle [float]"
