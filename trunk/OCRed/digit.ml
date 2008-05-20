(*
	OCRe - The ultimate OCR - HUGE Software
	OCRe is a project developed by 2nd year EPITA students
	- website: http://huge.ocre.free.fr/
	- svn repository: http://code.google.com/p/ocre

	About this folder:	OCRed
		OCRed is the preprocessing part of OCRe.
	About this file:	OCRed/digitization.ml
		This is the digitization.ml file.
*)
(*****************************************************)
(*FILTRE MEDIAN*)
(*****************************************************)

let filtremed matrix =
  let mediane t = t.(4) in
  let width = Bigarray.Array2.dim1 matrix in
  let height = Bigarray.Array2.dim2 matrix in
  let matrix2 = Transforme.bigarray2 width height in
  let k = ref 0 in
    for i = 0 to ((width) - 1) do
      for j = 0 to ((height) - 1) do
        let tab = Array.make 9 0 in
        k := 0;
        for l = i - 1 to i + 1 do
          for m = j - 1 to j + 1 do
            if ((l >= 0) && (l <= (width - 1))) && ((m >= 0) && (m <= (height - 1)))
            then
              begin tab.(!k) <- Int32.to_int(Bigarray.Array2.get matrix l m);
                k := !k + 1 end
          done;
        done;
        let cmp a b =
          if a > b then 42 else begin if a = b then 0 else -42 end in
          Array.fast_sort cmp tab;
          Bigarray.Array2.set matrix2 i j (Int32.of_int(mediane tab))
      done;
    done;
    matrix2

let main() =
  if (!Path.output <> "") then
    begin
      let original_matrix = Transforme.surf_to_matrix !Surface.image in
      let filtered_matrix = filtremed original_matrix in
        Surface.image := Transforme.matrix_to_surf filtered_matrix;
        Sdlvideo.save_BMP !Surface.image !Path.output
    end
  else
    begin
      let original_matrix = Transforme.surf_to_matrix !Surface.image in
      let filtered_matrix = filtremed original_matrix in
        Surface.image := Transforme.matrix_to_surf filtered_matrix;
        Sdlvideo.save_BMP !Surface.image "filtered.BMP"
    end

(*****************************************************)
(*/FILTRE MEDIAN*)
(*****************************************************)
