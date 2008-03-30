(*
  spec : 
  * possède au minimum 3 couches, soit une couche cachée minimum
  * en mode shell, faire d'abord init puis les autres fonctions
*)                                                
let main() =
  
  let shell = 0 in 
    if shell = 1 then (*0 = execution*)
      begin
        let p = new Perceptron.perceptron in
          p#set_nb_layers 3;
          p#set_nb_n_by_l 4;
          p#init();
          print_int (p#nb_connections());
          p#connections_print();
      end
    else (*1 = shell*)
      begin 
        print_string("\nBanc de test perceptron/afficheur 7 segments\n\n");
        let p = new Perceptron.perceptron in
        (*valeurs par defaut*)
         p#set_nb_layers 3;
         p#set_nb_n_by_l 4;
         p#init();
        (*/valeurs par defaut*)
        let str = ref "" in
          print_string "$";
          while !str <> "exit" do
            if !str <> "" then
              begin
                match !str with
                  | "?"      -> print_string (
                      "Options :\n"^ 
                        "?       : Options\n"^
                        "init    : Initialise le reseau\n"^
                        "train   : Entraine le reseau\n"^
                        "run     : Retourne la vecteur de sorties "^
                        "du reseau pour la donnee entree\n"^
                        "disp_c  : affiche les infos des connexions\n"^
                        "disp_n  : affiche les infos des neurones\n"^
                        "disp_o  : affiche la valeur des sorties\n"^
                        "exit    : Quitter\n$"
                      )
                  | "init"   -> (print_string "Nombre de couches cachees ?\nc = " ;
                                 let c = ref 0 in
                                   c := read_int();
                                   (match !c with
                                        e when e > 0 -> p#set_nb_layers (e + 2);
                                          print_string "\n"
                                      | e            -> print_string "n doit etre superieur a zero\n");
                                   print_string "Nombre de neurones par couche cachee ?\nn = " ;
                                   let n = ref 0 in
                                     n := read_int();
                                     (match !n with
                                          e when e > 0 -> p#set_nb_n_by_l e;
                                            print_string "\n$"
                                        | e            -> print_string "n doit etre superieur a zero\n$");
                                     p#init())
                  | "train"  -> (p#train(); 
                                 print_string "\n$")
                  | "run"    -> (p#update_v_obs_out();
                                 print_string "\n$")
                  | "disp_c" -> (print_string "nombre de connexions : ";
                                 print_int (p#nb_connections());
                                 print_string "\nliste des connexions :";
                                 p#connections_print();
                                 print_string "\n$")
                  | "disp_n" -> (print_string "nombre de neurones : ";
                                 print_int (p#get_nb_neurons());
                                 print_string "\nliste des neurones :";
                                 p#neurons_print();
                                 print_string "\n$")
                  | "disp_o" -> (print_string "valeur des sorties : ";
                                 p#v_obs_out_print();
                                 print_string "\n$")
                  | _        -> print_string "Taper \"?\" pour afficher les options\n$"
              end;
              str := read_line()
            done
      end
        
let _ = main()
  

(*
DEROULEMENT DES EVENEMENTS

PHASE D'INIT

on crée un perceptron                                 *
on renseigne son nombre de couches                    * 
on renseigne son nombre de neurones par couche cachée *
on charge les donnees dans le réseau                  *
on permute les donnees                                *
on calcule le nombre total de neurones                *
on initialise le vecteur de neurones                  *
on initialise le vecteur de connexions                *

PHASE D'APPRENTISSAGE



*)

