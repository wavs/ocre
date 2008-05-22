class pattern = 
object(self)

  val mutable inputs = Array.make 1 1.
  val mutable outputs = Array.make 1 1.

  method get_inputs() = inputs
  method set_inputs i = inputs <- i
  method print_inputs() =
    print_string "valeurs des entrées :\n";
    for i = 0 to Array.length inputs - 1 do
      print_float inputs.(i);
      print_newline()
    done

  method get_outputs() = outputs
  method set_outputs o = outputs <- o
  method print_outputs() =
    print_string "valeurs des sorties :\n";
    for i = 0 to Array.length outputs - 1 do
      print_float outputs.(i);
      print_newline()
    done
      
end
