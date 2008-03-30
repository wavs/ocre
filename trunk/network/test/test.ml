

let main() = 
  let alexandre = new Data.data in
    print_string "La taille du sexe d'Alex est : \n";
    print_string (alexandre#get_t());
    print_string "\n";
    print_string "L'endurance d'Alex est de : \n";
    print_string (alexandre#get_e());
    print_string "\n"

let _ = main()

