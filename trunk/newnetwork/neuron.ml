class neuron =
object(self)

  val mutable value = 1.
  val mutable error = 0.
  val mutable nextweights = Array.make 1 1.

  method print_value () = print_string(string_of_float(value))
  method print_error () = print_string(string_of_float(error))
  method print_weight() =
    print_string("il ya "^string_of_int(Array.length nextweights)^" poids\n");
    for i = 0 to Array.length nextweights - 1 do
      print_string(
        "this is the weight between this neuron and "^string_of_int(i)^" :");
      print_string(string_of_float(nextweights.(i)));
      print_string("\n");
    done;
  method print_neuron () =
    print_string("this is the neurone value: ");
    self#print_value ();
    print_string(" ; this is its error! : ");
    self#print_error ();
    print_string("\n")
  method print_neuron_and_weight () =
    print_string("this is the neurone value: ");
    self#print_value ();
    print_string(" ; this is its error! : ");
    self#print_error ();
    print_string("\n");
    self#print_weight()

  method get_error () = error
  method set_error x = error <- x

  method get_value () = value
  method set_value x = value <- x

  method init_nextweights taille =
    let tab = ref (Array.make taille 1.) in
      for i = 0 to Array.length !tab - 1 do
      let alea = Random.float 1. in
        if alea > 0.5 then
            Array.set !tab i (Random.float 0.5)
        else
          Array.set !tab i (Random.float (-. 0.5))
    done;
   nextweights <- !tab

  method set_nextweight pos value = Array.set nextweights pos value
  method get_nextweight pos = Array.get nextweights pos
  method set_nextweights x = nextweights <- x
  method get_nextweights ()= nextweights

end
