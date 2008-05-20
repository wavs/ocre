(*

  matrice de depart
  
  0123
  0123
  0123
  
  
  processing
  
  0-0-0-0-0-0-0-1-1 -> 0 0-0-0-0-0-1-1-2-2 -> 0 0-0-0-1-1-2-2-3-3 -> 1 0-0-0-0-0-2-2-3-3 -> 0
  0-0-0-0-0-0-1-1-1 -> 0 0-0-0-1-1-1-2-2-2 -> 1 1-1-1-2-2-2-3-3-3 -> 2 0-0-0-2-2-2-3-3-3 -> 2
  0-0-0-0-0-0-0-1-1 -> 0 0-0-0-0-0-1-1-2-2 -> 0 0-0-0-1-1-2-2-3-3 -> 1 0-0-0-0-0-2-2-3-3 -> 1
  
  matrice d'arrivee
  
  0010
  0122
  0011
  
  methode
  
  pour chaque colonne je calcule le median sur 1 petite colonne de 3
  elts
  
  principe

  on calcule le median colonne sur trois elements

  on remplace le median du pixel de gauche par le median 

  on remplace la valeur du pixel courant par le median de ce median et
  du median du pixel de gauche s'il existe
  
  ET (TRES IMPORTANT)

  on remplace la valeur du pixel de gauche par le median 
  
*)

(*traiter le cas des bordures independamment*)
let medianfilter matrice =
  (*on parcourt la matrice principale*)
  let tab = Array.make 3 0 in
    for i = 0 to Array.largeur matrice - 1 do
      for j = 0 to Array.hauteur matrice - 1 do
        (*on pacourt les petites colonnes de trois elements*)
        let cpt = ref 0 in
          for k = j - 1 to j + 1 do
            tab.(!cpt) <- matrice.(i)(k);
            cpt := !cpt + 1
          done;
          matrice.(i)(j)<- mediane (Array.sort tab)      
      done
    done
 done

(*****************************************************)
(*FILTRE MEDIAN*)
(*****************************************************)

let filtremed matrix =
  let mediane t = t.(4) in
  let width = Bigarray.Array2.dim1 matrix in
  let height = Bigarray.Array2.dim2 matrix in
  let matrix2 = Transforme.bigarray2 width height in
  let k = ref 0 in
    for i = 0 to ((height) - 1) do
      for j = 0 to ((width) - 1) do
        let tab = Array.make 3 0 in
        k := 0;
          for m = i - 1 to i + 1 do
            if ((m >= 0) && (m <= (height - 1)))
            then
              begin tab.(!k) <- Int32.to_int(Bigarray.Array2.get matrix j m);
                k := !k + 1 end
          done;
        done;
        let cmp a b =
          if a > b then 42 else begin if a = b then 0 else -42 end in
          Array.fast_sort cmp tab;
          Bigarray.Array2.set matrix2 j i (Int32.of_int(mediane tab));
          Bigarray.Array2.set matrix2 j i (Int32.of_int(mediane tab));
          Bigarray.Array2.set matrix2 j i (Int32.of_int(mediane tab))
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
