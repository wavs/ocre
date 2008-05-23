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
let display     = ref false
let seuil       = ref false
let rotate      = ref false
let resize      = ref false
let percent     = ref false
let median      = ref false
let resize_of_x = ref 800
let resize_of_y = ref 600
let percent_res = ref 100
let dev         = ref false
let right       = ref false
let left        = ref false

let set_left() =
  left := true

let set_right() =
  right := true

let set_median ()=
  median := true

let set_dev () =
  dev := true

let set_percent_resize x =
  percent_res := x;
  percent := true

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

let set_anglef a =
  Rotation.create_anglef a;
    rotate := true

let set_resize_auto () =
  let surf = Transforme.surf_to_matrix !Surface.image in
  let width = Bigarray.Array2.dim1 surf in
  let percent = float_of_int(Bigarray.Array2.dim2 surf)/.400. in
  resize        := true;
  resize_of_x   := int_of_float(float_of_int(width)/.percent);
  resize_of_y   := 400

let set_width i =
  resize        := true;
  resize_of_x   := i

let set_height i =
  resize_of_y := i

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
  ("-af",
   Arg.Float (fun i -> set_anglef i),
   "float Angle in degree");
  ("-dev",
   Arg.Unit ( fun () -> set_dev()),
   "noparameter This option is for detecting the angle");
  ("--median",
   Arg.Unit ( fun () -> set_median()),
   "noparameter This option is for median filter");
  ("-right",
   Arg.Unit ( fun () -> set_right()),
   "noparameter This option is rotating right the image");
  ("-left",
   Arg.Unit ( fun () -> set_left()),
   "noparameter This option is rotating left the image");
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
  ("--resizepercent",
   Arg.Int (fun s -> set_percent_resize s),
  "percentage Value of the output image size");
  ("--resize-auto",
   Arg.Unit (fun () -> set_resize_auto()),
  "noargument Value auto for testu of the output image size");
  ("--resize",
   Arg.Tuple (
     [
       Arg.Int ( fun i -> set_width i);
       Arg.Int ( fun j -> set_height j)
     ]
   ),
   "height_width Size of the ouput image");
  ("--angle",
   Arg.Int (fun i -> set_angle i),
   "Angle in degree");
  ("--display",
   Arg.Set display,
   " Useless option")
]

let usage = "Usage: -image [path] -angle [float]"
