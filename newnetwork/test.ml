let input = ref 0
let output = ref 0
let nbhlayers = ref 0
let nbn = ref 0


let options =
    "?     : options\n"^
    "init  : initialise le reseau\n"^
    "train : entraine le reseau\n"^
    "run   : reconnait la donnee voulue\n"^
    "dispc : affiche les connexions\n"^
    "dispn : affiche les neurones\n"^
    "save  : enregistre l'etat du reseau\n"^
    "load  : charge l'etat du reseau\n"^
    "exit  : quitter\n$";;
  
let p = ref (new Perceptron.perceptron 2 1 1 3);;

let rec init1_() =
  print_string "Nombre de couches cachees :\nc = ";
  let nbc = read_int() in
    (match nbc with
       |x when x > 0 -> nbhlayers := x
       |_            -> (print_string ("Entrez un entier"^
                          " superieur a 0\n"); init1_()));;

let rec init2_() =
  print_string "Nombre de neurones par couche cachee :\nn = ";
  let nbn1 = read_int() in
    (match nbn1 with
       |x when x > 0 -> nbn :=  x
       |_            -> (print_string ("Entrez un entier"^
                          " superieur a 0\n"); init2_()));;

let rec init3_() =
  print_string "Nombre d'entrees :\nn = ";
  let nbn1 = read_int() in
    (match nbn1 with
       |x when x > 0 -> input :=  x
       |_            -> (print_string ("Entrez un entier"^
                          " superieur a 0\n"); init2_()));;


let rec init4_() =
  print_string "Nombre de sorties :\nn = ";
  let nbn1 = read_int() in
    (match nbn1 with
       |x when x > 0 -> output :=  x
       |_            -> (print_string ("Entrez un entier"^
                          " superieur a 0\n"); init2_()));;

let init_() =
  init1_();
  init2_();
  init3_();
  init4_();
  p := new Perceptron.perceptron
    !input !output !nbhlayers !nbn

(* let rec run_() = *)
(*   print_string "Indice de la donnee a reconnaitre :\ni = "; *)
(*   let dlength = (p#getld()).(0)#geto() - 1 in *)
(*   let id = read_int() in *)
(*   let c = ((id >= 0) && (id <= dlength)) in *)
(*     (match id with *)
(*        |x when c -> p#run x *)
(*        |_        -> (print_string ("Entrez un entier"^ *)
(*                      " compris entre 0 et "); *)
(*                      print_int((p#getld()).(0)#geto() - 1); *)
(*                      print_string("\n"); *)
(*                      run_()));; *)

(* let rec learn_() = *)
(*   print_string "Nombre d'iterations :\nnb = "; *)
(*   let nb = read_int() in *)
(*     (match nb with *)
(*        |x when x > 0 -> (p#setit x; p#learn()) *)
(*        |_            -> (print_string ("Entrez un entier"^ *)
(*                           " superieur a 0\n"); learn_()));; *)


let main() =
  let str = ref "" in
    print_string "$";
    while !str <> "exit" do
      if !str <> "" then
        begin
           match !str with
            |"?"    -> print_string options
            |"init" -> (init_(); print_string "init done\n$")
            (* |"train"-> (learn_(); print_string "done\n$") *)
(*             |"run"  -> (run_(); print_string "done\n$") *)
            |"displ"-> (!p#lprint(); print_string "\n$")
(*             |"dispn"-> (p#nprint(); print_string "\n$") *)
(*             |"save" -> print_string "xpldr\n$" *)
(*             |"load" -> print_string "omg\n$" *)
            |_  -> print_string "taper \"?\" pour afficher les options\n$"
        end;
      str :=read_line();
    done
      
let _ = main()
  
