(*
** Programme de test pour ait-taleb thomas epita 2011
** Prend en parametre un charactere et le print sur la sortie standard
** But: trouver pourquoi et comment marche les threads en C
** Authors: guilbep@gmail.com
*)

let main () =
  print_string((Array.get Sys.argv 1)^"\n")

let _ = main()
