(*
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre

	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe.
	About this file:	OCRed/detection.ml
		This is the detection.ml file.
*)
let proj_h_table = ref (Transforme.bigarray1 1)
let average = ref 0

let projection_h tableau =
  let x = Bigarray.Array2.dim1 tableau in
  let y = Bigarray.Array2.dim2 tableau in
    proj_h_table := Transforme.bigarray1 y;
    for i = 0 to (y - 1) do
      begin
        let j = ref 0 in
        while (!j < x) && (
          (Bigarray.Array2.get tableau !j i) >=
            (Int32.of_int 255)) do
            begin
              j := !j + 1;
            end
          done;
        Bigarray.Array1.set
          !proj_h_table
          (i)
          (Int32.of_int(!j));
      end
    done

let proj_and_average tableau =
  let x = Bigarray.Array2.dim1 tableau in
  let y = Bigarray.Array2.dim2 tableau in
    proj_h_table := Transforme.bigarray1 y;
    for i = 0 to (y - 1) do
      begin
        let j = ref 0 in
        while (!j < x) && (
          (Bigarray.Array2.get tableau !j i) >=
            (Int32.of_int 255)) do
            begin
              j := !j + 1;
            end
          done;
        Bigarray.Array1.set
          !proj_h_table
          (i)
          (Int32.of_int(!j));
        average := !average + !j;
      end
    done;
    average := (!average / y)

(* let take_coef () = *)
(*   let dim = Bigarray.Array1.dim !proj_h_table in *)
(*   let i         = ref 0 in *)
(*     while (!i < *)
  (*
      let sommet_of_h tab =
  let i         = ref 0 in
  let count     = ref 0 in
  let monte     = ref false in
  let descendre = ref false in
  let get x i   = Bigarray.Array1.get x i in
  let dim x     = Bigarray.Array1.dim x in
    while ((!i + 1) <= (dim tab -1)) &&
      ((get tab !i) = (get tab (!i + 1))) do
      i := !i + 1
    done;
    if ((!i + 1) <= (dim tab -1)) &&
      ((get tab !i) < (get tab (!i+1))) then
      begin
        monte           := true;
        descendre       := false;
        count           := 0;
      end
    else
      begin
        monte           := false;
        descendre       := true;
        count           := 1;
      end;
    i := !i + 1;
    while (!i < (dim tab)) do
      begin
        if(!descendre) then
          begin
            while (!i < ((dim tab) - 1))
              && ((get tab !i) >= (get tab (!i + 1))) do
                i       := !i + 1
            done;
            monte       := true;
            descendre   := false;
          end
        else
          begin
            while (!i < ((dim tab) - 1))
              && ((get tab !i) >= (get tab (!i + 1))) do
                i       := !i + 1
            done;
            monte       := false;
            descendre   := true;
            count       := !count + 1;
          end;
        i := !i + 1
      end
    done;
    print_string((soi !count)^" une fois j'ai fait une projection"^"\n");
    !count
    *)

let histo_to_file file =
  let chan = (open_out file) in
    for i = 0 to ((Bigarray.Array1.dim !proj_h_table) -1) do
      begin
        let str = (
          Int32.to_string(Bigarray.Array1.get !proj_h_table i)^
            " \n\n"
        ) in
          output chan (str) 0 ((String.length str) -1);
      end
    done;
    close_out chan

