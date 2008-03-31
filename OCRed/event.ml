(*
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre

	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe.
	About this file:	OCRed/eventhandler.ml
		This is the eventhandler.ml file.
*)
exception Error_windows
exception Quit_onmouse
exception Nothing_to_be_done
exception Quit_input

let dev () =
 try
   let f = Detection.detect_angle () in
     print_string(string_of_float(f));
   if (!Path.output <> "") then
     begin
       Sdlvideo.save_BMP !Surface.image !Path.output;
       Detection.histo_to_file (!Path.output^".csv");
     end
   else
     Sdlvideo.save_BMP !Surface.image "../projection.bmp"
 with
   | Sdlvideo.Video_exn s -> print_endline
       (s^ "--> you may have forgotten an option"^
          ": try --help option; for example --resize")

let rotate () =
(*   print_endline "please wait while processing..."; *)
  try
  (*
   * FIXME for passing variable angle
   * We have to export different image type jpg, bmp, tiff and more
   *)
  let img_rot = Rotation.optimized2 !Surface.image !Rotation.angle in
    if (!Path.output <> "") then
      begin
        Sdlvideo.save_BMP img_rot !Path.output;
        Surface.image := img_rot;
      end
    else
      begin
        Sdlvideo.save_BMP img_rot "rotation.bmp";
        Surface.image := img_rot;
      end
with
  | Sdlvideo.Video_exn s -> print_endline
      (s^" --> you may have forgotten an option : try --help option")

let action () =
(* print_endline "please wait while processing..."; *)
try
  if (!Argument.resize) then
    begin
      Surface.image := (Interpolation.resize
                          !Surface.image
                          !Argument.resize_of_x
                          !Argument.resize_of_y);
      if (!Path.output <> "") then
        begin
          Sdlvideo.save_BMP !Surface.image !Path.output;
        end
      else
        begin
          Sdlvideo.save_BMP !Surface.image "../resize.bmp";
        end
    end;

  if (!Argument.percent) then
    begin
            Surface.image := (Interpolation.resize_percent
                                !Surface.image
                                !Argument.percent_res);
      if (!Path.output <> "") then
              begin
                Sdlvideo.save_BMP !Surface.image !Path.output;
              end
      else
        begin
          Sdlvideo.save_BMP !Surface.image "../resize.bmp"
        end;
          end
  else
    begin
      Sdlvideo.save_BMP !Surface.image "../noaction.bmp"
    end
with
  | Sdlvideo.Video_exn s -> print_endline
      (s^" --> you may have forgotten an option : try --help option")

let rec run () =
  try
    Sdlvideo.flip !Surface.screen;
    Sdlvideo.blit_surface
      ~src:!Surface.image
      ~dst:!Surface.screen ();
    match
      Sdlevent.wait_event ()
    with
      | Sdlevent.KEYDOWN {Sdlevent.keysym=Sdlkey.KEY_F1} ->
        raise Quit_input
      | Sdlevent.KEYDOWN {Sdlevent.keysym=Sdlkey.KEY_F4} ->
          print_endline "Median Filter";
          Digit.main ();
          run()
      | Sdlevent.KEYDOWN {Sdlevent.keysym=Sdlkey.KEY_F3} ->
          print_endline "Treshold";
          Seuil.main ();
          run()
      | Sdlevent.KEYDOWN {Sdlevent.keysym=Sdlkey.KEY_F2} ->
          rotate();
          run()
      | Sdlevent.QUIT -> raise Quit_onmouse
          (* User-requested quit *)
      | Sdlevent.SYSWM ->
          print_endline (Sdlevent.string_of_event Sdlevent.SYSWM);
          run()
      | _ -> run ()
  with
      Quit_input -> raise Quit_input
    | Quit_onmouse -> raise Quit_onmouse

