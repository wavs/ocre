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
let main () =
  Sdl.init [`VIDEO;`EVENTTHREAD;`TIMER];
  Sdlkey.enable_unicode true;
  Sdlkey.enable_key_repeat ();
(*   Arg.parse (Arg.align Argument.speclist) (fun _ -> ()) Argument.usage ; *)
  try
    Event.run ()
  with
      Event.Quit_input ->  Sdl.quit ()
    | Event.Quit_onmouse -> Sdl.quit ()

let _ = main ()
