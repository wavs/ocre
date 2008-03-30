

let main() = 
  let alexandre = new Data.data in
    print_string "La taille du sexe d'Alex est : \n";
    print_string (alexandre#get_t());
    print_string "\n";
    print_string "L'andurance d'Alex est de : \n";
    print_string (alexandre#get_a());
    print_string "\n"

let _ = main()

