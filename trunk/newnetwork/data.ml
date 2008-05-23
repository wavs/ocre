class data x y =
object(self)

  val mutable nbinputs = x
  val mutable nboutputs = y
  val mutable inputs = Array.make x 1
  val mutable outputs = Array.make y 1

  method print_input () =
    for i = 0 to Array.length inputs -1 do
      print_string("Ceci est la "^string_of_int(i+1)^" valeur de inputs: ");
      print_string(string_of_int(inputs.(i))^"\n");
    done;

  method init_bool_op e1 e2 s1 =
    if (x == 2) && (y == 1) then
      begin
        inputs.(0) <- e1;
        inputs.(1) <- e2;
        outputs.(0) <- s1;
      end


  method get_nbinputs = nbinputs
  method set_nbinputs x = nbinputs <- x
  method set_nboutputs x = nboutputs <- x
  method get_nboutputs ()= nboutputs

  method set_input pos value = Array.set inputs pos value
  method get_input pos = Array.get inputs pos
  method set_inputs x  = inputs <- x
  method get_inputs () = inputs

  method set_output pos value = Array.set outputs pos value
  method get_output pos = Array.get outputs pos
  method set_outputs x  = outputs <- x
  method get_outputs () = outputs

end


(** tabdata pour le xor*)

class tab_xor =
object (self)
  val mutable tab = Array.make 4 (new data 2 1)
  method get_tab() = tab
  method set_tab x = tab <- x
  method init_tab () =
    let pattern1 = new data 2 1 in
      pattern1#init_bool_op 0 0 0;
    let pattern2 = new data 2 1 in
      pattern2#init_bool_op 0 1 1;
    let pattern3 = new data 2 1 in
      pattern3#init_bool_op 1 0 1;
    let pattern4 = new data 2 1 in
      pattern4#init_bool_op 1 1 0;
      tab <- [|pattern1;pattern2;pattern3;pattern4|]
  method get_pos_tab pos = Array.get tab pos
end


class data_alpha =
object (self)
  val mutable char = 0
  val mutable output = 0
  val mutable tab_input = Array.make 100 1
(*   method init_from_file num_charactere file_path = *)
(*     let filed = Unix.openfile file_path in *)
  method get_char () = char
  method set_char x  = char <- x

  method get_output = output
  method set_output x = output <-x

  method get_tab () = tab_input
  method set_tab x  =  tab_input <- x
  method get_tabpos pos = tab_input.(pos)
  method set_tabpos pos x =  tab_input.(pos) <- x
  method zero_or_one int =
    if (int == 48) then
      0
    else
      1
  method init_tab string =
    for i = 0 to 99 do
      let char = String.get string i in
        Array.set (self#get_tab()) i (self#zero_or_one (Char.code char))
    done
(*       Unix.close filed *)
end


class alphabet =
object (self)
  (* Le principe est le suivant : on va avoir N pattern un reseau de
     neurones devra reconnaitre un pattern => que l'on aura N reseau de
     neurones. La reponse a ce probleme est le suivant. On aura Un
     tableau de reseau de neuronne chaque case correspondant a une
     valeur de l'alphabet "a b ou c par exemple". donc on aurra une
     boucle qui pour chaque valeur de l'alphabet "n" apprendra a
     reconnaitre cette valeur au reseau de neurone "n" du tableau de
     reseau de neurones. Cette boucle sera au courrant que la valeur de
     sortie du reseau de neuronnes sera vrai pour la valeur rechercher
     et fausse pour tout les valeurs de l'alphabet. Ce qui nous amene a
     la structure de la classe alphabet:  L'alphabet contien N valeur
     correspondant aux symboles reconnnu. Pour chaque valeur on aurra
     un tableau d'entree!!! donc on utilise une class data qui possede
     une structure differente*)
  val mutable tab = Array.make 26 (new data_alpha)
  val mutable tab_string =
    [|
      "0111111000"^
        "1110011100"^
        "1100001100"^
        "0000011100"^
        "0111111100"^
        "1110001100"^
        "1100001100"^
        "1100001100"^
        "1110011110"^
        "0111100110";
      "1000000000"^
        "1000000000"^
        "1011000000"^
        "1100100000"^
        "1000100000"^
        "1000100000"^
        "1000100000"^
        "1100100000"^
        "1011000000"^
        "0000000000";
      "0011111000"^
        "0111111100"^
        "0110001100"^
        "1100000000"^
        "1100000000"^
        "1100000000"^
        "1100000000"^
        "0110001100"^
        "0111111100"^
        "0011111000";
      "0000000000"^
        "0000100000"^
        "0000100000"^
        "0110100000"^
        "1001100000"^
        "1000100000"^
        "1000100000"^
        "1000100000"^
        "1001100000"^
        "0110100000";
      "0011110000"^
        "0111111000"^
        "1100001100"^
        "1100001100"^
        "1111111100"^
        "1100000000"^
        "1100000000"^
        "1110001100"^
        "0111111100"^
        "0011110000";
      "0110000000"^
        "1000000000"^
        "1100000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "000000000";
      "0110100000"^
        "1001100000"^
        "1000100000"^
        "1000100000"^
        "1000100000"^
        "1001100000"^
        "0110100000"^
        "0000100000"^
        "1000100000"^
        "0111000000";
      "1000000000"^
        "1000000000"^
        "1011000000"^
        "1100100000"^
        "1000100000"^
        "1000100000"^
        "1000100000"^
        "1000100000"^
        "1000100000"^
        "0000000000";
      "1000000000"^
        "0000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "0000000000";
      "0100000000"^
        "0000000000"^
        "0100000000"^
        "0100000000"^
        "0100000000"^
        "0100000000"^
        "0100000000"^
        "0100000000"^
        "0100000000"^
        "1000000000";
      "1000000000"^
        "1000000000"^
        "1001000000"^
        "1010000000"^
        "1100000000"^
        "1100000000"^
        "1010000000"^
        "1001000000"^
        "1000100000"^
        "0000000000";
      "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "0000000000";
      "1011001100"^
        "1100110010"^
        "1000100010"^
        "1000100010"^
        "1000100010"^
        "1000100010"^
        "1000100010"^
        "1000100010"^
        "0000000000"^
        "0000000000";
      "1100111000"^
        "1101111100"^
        "1110001100"^
        "1100001100"^
        "1100001100"^
        "1100001100"^
        "1100001100"^
        "1100001100"^
        "1100001100"^
        "1100001100"^
        "0011111000"^
        "0111111100"^
        "0110001100"^
        "1100000110"^
        "1100000110"^
        "1100000110"^
        "1100000110"^
        "0110001100"^
        "0111111100"^
        "0011111000";
      "1011000000"^
        "1100100000"^
        "1000100000"^
        "1000100000"^
        "1000100000"^
        "1100100000"^
        "1011000000"^
        "1000000000"^
        "1000000000"^
        "1000000000";
      "0110100000"^
        "1001100000"^
        "1000100000"^
        "1000100000"^
        "1000100000"^
        "1001100000"^
        "0110100000"^
        "0000100000"^
        "0000100000"^
        "0000100000";
      "1011000000"^
        "1100000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "1000000000"^
        "0000000000";
      "0011110000"^
        "0111111000"^
        "1100011000"^
        "1100000000"^
        "1111110000"^
        "0011111000"^
        "0000011000"^
        "1100011000"^
        "1111110000"^
        "0111100000";
      "0100000000"^
        "0100000000"^
        "1111000000"^
        "0100000000"^
        "0100000000"^
        "0100000000"^
        "0100000000"^
        "0100000000"^
        "0100000000"^
        "0011000000";
      "1100001100"^
        "1100001100"^
        "1100001100"^
        "1100001100"^
        "1100001100"^
        "1100001100"^
        "1100001100"^
        "1100011100"^
        "1111101100"^
        "0111001100";
      "1100001100"^
        "1100001100"^
        "1100001100"^
        "0110011000"^
        "0110011000"^
        "0110011000"^
        "0010010000"^
        "0011110000"^
        "0001100000"^
        "0001100000";
      "1000100010"^
        "1000100010"^
        "1000100010"^
        "0100100100"^
        "0100100100"^
        "0101010100"^
        "0010001000"^
        "0010001000"^
        "0000000000"^
        "0000000000";
      "1100001100"^
        "1110011100"^
        "0110011000"^
        "0011110000"^
        "0001100000"^
        "0001100000"^
        "0011110000"^
        "0110011000"^
        "1110011100"^
        "1100001100";
      "1000100000"^
        "1000100000"^
        "1000100000"^
        "1001000000"^
        "0101000000"^
        "0101000000"^
        "0010000000"^
        "0010000000"^
        "0100000000"^
        "1000000000";
      "1111111000"^
        "1111111000"^
        "0000011000"^
        "0000110000"^
        "0001100000"^
        "0011000000"^
        "0110000000"^
        "1100000000"^
        "1111111000"^
        "1111111000"
    |]

  method get_tab() = tab
  method set_tab x = tab <- x

  method get_tabpos pos = tab.(pos)
  method set_tabpos pos x =  tab.(pos) <- x
  method get_string_tab pos = tab_string.(pos)

  method init_tab_alpha () =
    for i = 0 to 25 do
      let a = new data_alpha in
        a#set_char i;
        a#init_tab (self#get_string_tab i);
        self#set_tabpos i a;
    done

end
