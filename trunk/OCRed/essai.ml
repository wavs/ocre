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
            tab.(cpt) <- matrice.(i)(k);
            cpt := cpt + 1
          done;
          matrice.(i)(j)<- mediane (Array.sort tab)      
      done
    done
 done
