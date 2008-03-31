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

let init () =
Sdl.init [`VIDEO;`EVENTTHREAD;`TIMER];
          Sdlkey.enable_unicode true;
          Sdlkey.enable_key_repeat ()

let submain() =
  if (!Argument.right) then
    begin
      init ();
      Argument.right := false;
      Sdlvideo.save_BMP
        (Transforme.matrix_to_surf(Rotation.simple_right
                                 (Transforme.surf_to_matrix
                                 !Surface.image)))
        !Path.output;
      Sdl.quit ()
    end;
  if (!Argument.left) then
    begin
      init ();
      Argument.left := false;
     ( Sdlvideo.save_BMP
        (Transforme.matrix_to_surf(Rotation.simple_left
                                 (Transforme.surf_to_matrix
                                 !Surface.image))))
        !Path.output;
      Sdl.quit ()
    end;
  if (!Argument.seuil) then
    begin
      init ();
      Argument.seuil := false;
      Seuil.main ();
      Sdl.quit ()
    end;
  if (!Argument.rotate)then
    begin
      init ();
      Argument.rotate := false;
      Event.rotate ();
      Sdl.quit ()
    end;
  if(!Argument.resize) ||
    (!Argument.percent) then
      begin
        init ();
        Event.action ();
        Sdl.quit ()
      end;
  if(!Argument.median) then
    begin
      init ();
      Digit.main ();
      Sdl.quit();
    end


let main () =
  Arg.parse
    (Arg.align Argument.speclist)
    (fun _ -> ())
    Argument.usage;
  if !Argument.display then
    begin
      try
        init ();
         let (w,h) = Surface.taille !Surface.image in
          Surface.set_screen w h;
          Event.run ()
      with
        | Event.Quit_input ->  Sdl.quit ()
        | Event.Quit_onmouse -> Sdl.quit ()
    end;
  if (!Argument.dev) then
    begin
      init ();
      Event.dev ();
      Sdl.quit ();
    end
  else
    submain ()


let _ = main ()
