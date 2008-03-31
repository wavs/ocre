
 (* 2 Normaliser les donnees d'entrainement                                 FAIT ! *)

(*Données pour afficheur sept segments*)


(*  _                _        _
   | | -> 0  | -> 1  _| -> 2  _| -> 3 etc...
   |_|       |      |_        _|
*)


class data x y =
object (self)

  val mutable inputs = Array.make x 0.
  method get_inputs() = inputs
  method set_inputs inputs0 = inputs <- inputs0
  method set_input i x = inputs.(i) <- x
  method in_print i =
    print_float(inputs.(i));
    print_newline()
  method inputs_print() = 
    print_newline();
    for i = 0 to Array.length inputs - 1 do
      self#in_print i
    done;
    print_newline()
        
  val mutable outputs = Array.make y 0.
  method get_outputs() = outputs
  method set_outputs outputs0 = outputs <- outputs0
  method set_output i x = outputs.(i) <- x
  method out_print i =
    print_float(outputs.(i));
    print_newline()
  method outputs_print() = 
    print_newline();
    for i = 0 to Array.length outputs - 1 do
      self#out_print i
    done;
    print_newline()
end


(****************************************************)

class tabdata = (*XOR*)
object (self)
  val mutable tab = Array.make 4 (new data 2 4)
  method get_tab() = tab
  method set_tab tab0 = tab <- tab0
  method get_tab2() = 
  let n0 = new data 2 4 in
    n0#set_input 0 0.;
    n0#set_input 1 0.;

    n0#set_output 0 1.; (*0*)
    n0#set_output 1 0.; (*1*)
    n0#set_output 2 0.; (*1*)
    n0#set_output 3 0.; (*0*)

  let n1 = new data 2 4 in
    n1#set_input 0 0.;
    n1#set_input 1 1.;

    n1#set_output 0 0.; (*0*)
    n1#set_output 1 1.; (*1*)
    n1#set_output 2 0.; (*1*)
    n1#set_output 3 0.; (*0*)

  let n2 = new data 2 4 in
    n2#set_input 0 1.;
    n2#set_input 1 0.;

    n2#set_output 0 0.; (*0*)
    n2#set_output 1 0.; (*1*)
    n2#set_output 2 1.; (*1*)
    n2#set_output 3 0.; (*0*)

  let n3 = new data 2 4 in
    n3#set_input 0 1.;
    n3#set_input 1 1.;

    n3#set_output 0 0.; (*0*)
    n3#set_output 1 0.; (*1*)
    n3#set_output 2 0.; (*1*)
    n3#set_output 3 1.; (*0*) 

    [|n0;n1;n2;n3|]
end

class tabdata2 = (*7segaff*)
object (self)
  val mutable tab = Array.make 10 (new data 7 10)
  method get_tab() = tab
  method set_tab tab0 = tab <- tab0
  method get_tab2() = 
  let number0 = new data 7 10 in
    (*Données d'entrée*)
    number0#set_input 0 1.;
    number0#set_input 1 1.;
    number0#set_input 2 1.;
    number0#set_input 3 1.;
    number0#set_input 4 1.;
    number0#set_input 5 1.;
    number0#set_input 6 0.;
    
    (*Données de sortie*)
    number0#set_output 0 1.;
    number0#set_output 1 0.;
    number0#set_output 2 0.;
    number0#set_output 3 0.;
    number0#set_output 4 0.;
    number0#set_output 5 0.;
    number0#set_output 6 0.;
    number0#set_output 7 0.;
    number0#set_output 8 0.;
    number0#set_output 9 0.;
    
    let number1 = new data 7 10 in
      (*Données d'entrée*)
      number1#set_input 0 0.;
      number1#set_input 1 1.;
      number1#set_input 2 1.;
      number1#set_input 3 0.;
      number1#set_input 4 0.;
      number1#set_input 5 0.;
      number1#set_input 6 0.;
      
      (*Données de sortie*)  
      number1#set_output 0 0.;
      number1#set_output 1 1.;
      number1#set_output 2 0.;
      number1#set_output 3 0.;
      number1#set_output 4 0.;
      number1#set_output 5 0.;
      number1#set_output 6 0.;
      number1#set_output 7 0.;
      number1#set_output 8 0.;
      number1#set_output 9 0.;
      
      let number2 = new data 7 10 in
        (*Données d'entrée*)
        number2#set_input 0 1.;
        number2#set_input 1 1.;
        number2#set_input 2 0.;
        number2#set_input 3 1.;
        number2#set_input 4 1.;
        number2#set_input 5 0.;
        number2#set_input 6 1.;
        
        (*Données de sortie*)
        number2#set_output 0 0.;
        number2#set_output 1 0.;
        number2#set_output 2 1.;
        number2#set_output 3 0.;
        number2#set_output 4 0.;
        number2#set_output 5 0.;
        number2#set_output 6 0.;
        number2#set_output 7 0.;
        number2#set_output 8 0.;
        number2#set_output 9 0.;
        
        let number3 = new data 7 10 in
          (*Données d'entrée*)
          number3#set_input 0 1.;
          number3#set_input 1 1.;
          number3#set_input 2 1.;
          number3#set_input 3 1.;
          number3#set_input 4 0.;
          number3#set_input 5 0.;
          number3#set_input 6 1.;
          
          (*Données de sortie*)
          number3#set_output 0 0.;
          number3#set_output 1 0.;
          number3#set_output 2 0.;
          number3#set_output 3 1.;
          number3#set_output 4 0.;
          number3#set_output 5 0.;
          number3#set_output 6 0.;
          number3#set_output 7 0.;
          number3#set_output 8 0.;
          number3#set_output 9 0.;
          
          let number4 = new data 7 10 in
            (*Données d'entrée*)
            number4#set_input 0 0.;
            number4#set_input 1 1.;
            number4#set_input 2 1.;
            number4#set_input 3 0.;
            number4#set_input 4 0.;
            number4#set_input 5 1.;
            number4#set_input 6 1.;
            
            (*Données de sortie*)
            number4#set_output 0 0.;
            number4#set_output 1 0.;
            number4#set_output 2 0.;
            number4#set_output 3 0.;
            number4#set_output 4 1.;
            number4#set_output 5 0.;
            number4#set_output 6 0.;
            number4#set_output 7 0.;
            number4#set_output 8 0.;
            number4#set_output 9 0.;
            
            let number5 = new data 7 10 in
              (*Données d'entrée*)
              number5#set_input 0 1.;
              number5#set_input 1 0.;
              number5#set_input 2 1.;
              number5#set_input 3 1.;
              number5#set_input 4 0.;
              number5#set_input 5 1.;
              number5#set_input 6 1.;
              
              (*Données de sortie*)
              number5#set_output 0 0.;
              number5#set_output 1 0.;
              number5#set_output 2 0.;
              number5#set_output 3 0.;
              number5#set_output 4 0.;
              number5#set_output 5 1.;
              number5#set_output 6 0.;
              number5#set_output 7 0.;
              number5#set_output 8 0.;
              number5#set_output 9 0.;
              
              let number6 = new data 7 10 in
                (*Données d'entrée*)
                number6#set_input 0 1.;
                number6#set_input 1 0.;
                number6#set_input 2 1.;
                number6#set_input 3 1.;
                number6#set_input 4 1.;
                number6#set_input 5 1.;
                number6#set_input 6 1.;
                
                (*Données de sortie*)
                number6#set_output 0 0.;
                number6#set_output 1 0.;
                number6#set_output 2 0.;
                number6#set_output 3 0.;
                number6#set_output 4 0.;
                number6#set_output 5 0.;
                number6#set_output 6 1.;
                number6#set_output 7 0.;
                number6#set_output 8 0.;
                number6#set_output 9 0.;
                
                let number7 = new data 7 10 in
                  (*Données d'entrée*)
                  number7#set_input 0 1.;
                  number7#set_input 1 1.;
                  number7#set_input 2 1.;
                  number7#set_input 3 0.;
                  number7#set_input 4 0.;
                  number7#set_input 5 0.;
                  number7#set_input 6 0.;
                  
                  (*Données de sortie*)
                  number7#set_output 0 0.;
                  number7#set_output 1 0.;
                  number7#set_output 2 0.;
                  number7#set_output 3 0.;
                  number7#set_output 4 0.;
                  number7#set_output 5 0.;
                  number7#set_output 6 0.;
                  number7#set_output 7 1.;
                  number7#set_output 8 0.;
                  number7#set_output 9 0.;
                  
                  let number8 = new data 7 10 in
                    (*Données d'entrée*)
                    number8#set_input 0 1.;
                    number8#set_input 1 1.;
                    number8#set_input 2 1.;
                    number8#set_input 3 1.;
                    number8#set_input 4 1.;
                    number8#set_input 5 1.;
                    number8#set_input 6 1.;
                    
                    (*Données de sortie*)
                    number8#set_output 0 0.;
                    number8#set_output 1 0.;
                    number8#set_output 2 0.;
                    number8#set_output 3 0.;
                    number8#set_output 4 0.;
                    number8#set_output 5 0.;
                    number8#set_output 6 0.;
                    number8#set_output 7 0.;
                    number8#set_output 8 1.;
                    number8#set_output 9 0.;
                    
                    let number9 = new data 7 10 in
                      (*Données d'entrée*)
                      number9#set_input 0 1.;
                      number9#set_input 1 1.;
                      number9#set_input 2 1.;
                      number9#set_input 3 1.;
                      number9#set_input 4 0.;
                      number9#set_input 5 1.;
                      number9#set_input 6 1.;
                      
                      (*Données de sortie*)
                      number9#set_output 0 0.;
                      number9#set_output 1 0.;
                      number9#set_output 2 0.;
                      number9#set_output 3 0.;
                      number9#set_output 4 0.;
                      number9#set_output 5 0.;
                      number9#set_output 6 0.;
                      number9#set_output 7 0.;
                      number9#set_output 8 0.;
                      number9#set_output 9 1.;
                      
                      [|number0;number1;number2;
                        number3;number4;number5;
                        number6;number7;number8;
                        number9|]
end

