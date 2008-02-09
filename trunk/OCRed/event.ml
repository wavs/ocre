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
let pi = 3.141592654
let pisur3 = pi /. 3.

 let rec run () =
  try
    Sdlvideo.flip Surface.screen;
    Sdlvideo.blit_surface
      ~src:Surface.image
      ~dst:Surface.screen ();
  match
    Sdlevent.wait_event ()
  with
    | Sdlevent.KEYDOWN {Sdlevent.keysym=Sdlkey.KEY_F1} ->
        raise Quit_input
    | Sdlevent.KEYDOWN {Sdlevent.keysym=Sdlkey.KEY_F2} ->
        print_endline "test_of_surf";
        (*FIXME for passing variable angle*)
        let img_rot = Rotation.hard_of_surf Surface.image  pisur3 in
          Sdlvideo.save_BMP img_rot "test.bmp";
        run();
    | Sdlevent.QUIT -> raise Quit_onmouse
        (* User-requested quit *)
    | Sdlevent.SYSWM ->
        print_endline (Sdlevent.string_of_event Sdlevent.SYSWM);
        run()
    | _ -> run ()
with
    Quit_input -> raise Quit_input
  | Quit_onmouse -> raise Quit_onmouse


(* System specific event need to be enable with event_state*)
(* needed for copy/past application*)
(* | VIDEORESIZE of (int * int) *)
(*FIXME FOR RECT IN MIDDLE SIZE*)
(* User resized video mode *)

(* | VIDEOEXPOSE *)
(* Screen needs to be redrawn *)
(* | USER of int *)
(* for your use ! but you need to use push event *)
          (*  | Sdlevent.ACTIVE {Sdlevent.gain = true} -> *)
          (*         print_endline "est active" *)
          (*         (\* Application loses/gains visibility *\) *)
          (*     | Sdlevent.ACTIVE {Sdlevent.gain=false} -> *)
          (*         print_endline "n'est plus active" *)

(* Keys pressed *)
(*     | KEYUP of Sdlevent.keyboard_event *)
(*     | MOUSEMOTION of Sdlevent.mousemotion_event *)
(*      (\* Mouse moved *\) *)
(*     | MOUSEBUTTONDOWN of Sdlevent.mousebutton_event *)
(*      (\* Mouse button pressed *\) *)
(*     | MOUSEBUTTONUP of Sdlevent.mousebutton_event *)
(*      (\* Mouse button released *\) *)
(*     | JOYAXISMOTION of Sdlevent.joyaxis_event *)
(*      (\* Joystick axis motion *\) *)
(*     | JOYBALLMOTION of Sdlevent.joyball_event *)
(*      (\* Joystick trackball motion *\) *)
(*     | JOYHATMOTION of Sdlevent.joyhat_event *)
(*      (\* Joystick hat position change *\) *)
(*     | JOYBUTTONDOWN of Sdlevent.joybutton_event *)
(*      (\* Joystick button pressed *\) *)
(*     | JOYBUTTONUP of Sdlevent.joybutton_event *)
(* Joystick button released *)
(* Keys released *)
