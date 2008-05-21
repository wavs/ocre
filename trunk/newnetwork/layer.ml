class layer nbn =
object(self)

  val mutable nbneurons = nbn
  val mutable neurons = Array.make nbn (new Neuron.neuron)
  val mutable bias = new Neuron.neuron
  method print_neurons () =
    print_string(string_of_int(nbneurons));
    for i = 0 to nbneurons -1 do
      print_int(i);
      print_string(" this was the neuron number : ");
      neurons.(i)#print_neuron();
      print_string("\n");
    done;
    print_string("this is the bias: ");
    bias#print_neuron();
    print_string("\n\n")

  method print_weight_and_neuron() =
   
    for i = 0 to nbneurons -1 do
      begin
        print_int(i);
        print_string(" this was the neuron number : ");
        neurons.(i)#print_neuron_and_weight();
        print_string("\n");
      end
    done;
    print_string("this is the bias: ");
    bias#print_neuron_and_weight();
    print_string("\n\n")

  method init_neurons nb_arc_avt =
    for i = 0 to Array.length  neurons - 1 do
      print_string("neuronne numero :"^string_of_int(i)^" : ");
      (neurons.(i))#init_nextweights nb_arc_avt;
    done;
    print_string("im a biais\n");
    bias#init_nextweights nb_arc_avt;
    self#print_weight_and_neuron()


  method set_nbneurons x  = nbneurons <- x
  method get_nbneurons () = nbneurons

  method set_bias x  = bias <- x
  method get_bias () = bias

  method get_tabneurons () = neurons
  method set_tabneurons x = neurons <- x

end
