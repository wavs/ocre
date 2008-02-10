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

(*****************************************************)
(*Tri Fusion*)
let rec division liste =
  match liste with
    |[] -> [],[]
    |a::[] -> liste,[]
    |a::b::c ->
       let (l1,l2) = division c in
         a::l1,b::l2

let rec fusion liste1 liste2 =
  match liste1,liste2 with
    |[],_ -> liste2;
    |_,[] -> liste1;
    |t1::q1,t2::q2 ->
       if t1 < t2 then
         t1::(fusion q1 liste2)
       else
         t2::(fusion liste1 q2)


let rec tri_fusion liste =
  match liste with
    |[] -> [];
    |a::[] -> liste;
    |_ ->
       begin
         let (liste1,liste2) = division liste in
           fusion (tri_fusion(liste1)) (tri_fusion(liste2));
       end
(*/Tri Fusion*)
(*****************************************************)

(*****************************************************)
(*Tabtolist*)
let tabtolist tab = 
  let i = ref 0 in
  let liste = ref [] in
    while (!i < Array.length tab) do 
      liste := tab.(!i)::!liste;
      i := !i + 1
    done;
    !liste
(*/Tabtolist*)
(*****************************************************)

(*****************************************************)
(*mediane*)
let mediane l = List.nth l 4
(*/mediane*)
(*****************************************************)

(*****************************************************)
(*filtre_median*)
let filtremed matrix =
  let width = Bigarray.Array2.dim1 matrix in
  let height = Bigarray.Array2.dim2 matrix in
  let matrix2 = Transforme.bigarray2 width height in
  let k = ref 0 in
 
    for i = 0 to ((width) - 1) do
      for j = 0 to ((height) - 1) do
        let tab = Array.make 9 (Int32.of_int 0) in
        k:=0;
        for l = i - 1 to i + 1 do
          for m = j - 1 to j + 1 do
            if ((l >= 0) 
                 && (l <= (width - 1)))
                 && ((m >= 0)
                 && (m <= (height - 1))) 
            then
              (tab.(!k) <- Bigarray.Array2.get matrix l m);    
            k:= !k + 1;
            
          done;
        done;
        Bigarray.Array2.set matrix2 i j (mediane (tri_fusion (tabtolist(tab))))
      done;
    done;
    matrix2
      
      
(*/filtre_median*)
(*****************************************************)
 
(*****************************************************)
(*Fonctions de test*)     
let rec lectureliste l = match l with
    []   -> print_int 666
  |e::l0 -> (print_int e ;
            print_string " ; ";
           lectureliste l0)

let rec lecturebigarray b = 
  for i = 0 to (Bigarray.Array2.dim1 b) - 1 do
    for j = 0 to (Bigarray.Array2.dim2 b) - 1 do
      print_int (Int32.to_int (Bigarray.Array2.get b i j));
      print_string " "
    done;
    print_newline()
  done

let main2() =
  let listemp = tabtolist (Array.make 5 42) in
    lectureliste listemp

let main3() = 
  let listemp2 = tri_fusion (tabtolist [|32;42;25;3;2;2;45;69;12;10;2;10|]) in
    lectureliste listemp2

let main4() = 
  let listemp3 = tri_fusion [5;3;4;1;6;4;7;3;10] in
    print_int (mediane listemp3);
    print_newline();
    lectureliste listemp3
      
let main() = 
    Seuil.seuillage !Surface.image;
  (*let original_matrix= Transforme.surf_to_matrix image in
  let filtered_matrix = filtremed original_matrix in
  let surf_of_filtered = Transforme.matrix_to_surf filtered_matrix in
  *)
 (* let grotablo = Transforme.bigarray2 3 3 in
    Bigarray.Array2.set grotablo 0 0 (Int32.of_int 1);
    Bigarray.Array2.set grotablo 0 1 (Int32.of_int 2);
    Bigarray.Array2.set grotablo 0 2 (Int32.of_int 3);
    Bigarray.Array2.set grotablo 1 0 (Int32.of_int 4);
    Bigarray.Array2.set grotablo 1 1 (Int32.of_int 5);
    Bigarray.Array2.set grotablo 1 2 (Int32.of_int 6);
    Bigarray.Array2.set grotablo 2 0 (Int32.of_int 7);
    Bigarray.Array2.set grotablo 2 1 (Int32.of_int 8);
    Bigarray.Array2.set grotablo 2 2 (Int32.of_int 9);*)
    (* for i = 0 to 2 do
       for j = 0 to 2 do
       Bigarray.Array2.set grotablo i j (Int32.of_int (1 + i))
       done;
       done;*)
    (*affichage du tableau initial*)
    (*lecturebigarray grotablo;
    (*application du filtre median*)
    print_newline();
    print_newline();
    (*affichage du tableau modifié*)
    lecturebigarray (filtremed grotablo)*)
       Sdlvideo.save_BMP !Surface.image (*surf_of_filtered*) "dtc.BMP"
       
      
   
(*/Fonctions de test*) 
(*****************************************************)

(*****************************************************)
(*/FILTRE MEDIAN*)
(*****************************************************)
