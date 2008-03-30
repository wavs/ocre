
class neuron =
object (self)

  val mutable id = -666
  method get_id() = id
  method set_id id0 = id <- id0
  method id_print() =
    print_int(id);
    print_newline()

  val mutable layer = -42
  method get_layer() = layer
  method set_layer layer0 = layer <- layer0
  method layer_print() =
    print_int(layer);
    print_newline()
  
  val mutable wanted_output = 0.
  method get_wanted_output() = wanted_output
  method set_wanted_output w_out0= wanted_output <- w_out0
  method wanted_output_print() =
    print_float(wanted_output);
    print_newline()
      
  val mutable observed_output = 0.
  method get_observed_output() = observed_output
  method set_observed_output o_out0= observed_output <- o_out0
  method observed_output_print() =
    print_float(observed_output);
    print_newline()
        
  val mutable error = 1337. 
  method get_error() = error
  method set_error err0= error <- err0
  method calc_error() = error <- wanted_output -. observed_output
  method error_print() =
    print_float(error);
    print_newline()

  val mutable weight_sum = 42.
  method get_weight_sum() = weight_sum
  method set_weight_sum weight_sum0 = weight_sum <- weight_sum0
  method weight_sum_print() =
    print_float(weight_sum);
    print_newline()

  val mutable beta = 0.5;
    (*para de la fct d'activ ; prendre 0,5, 1 ou 5 par ex*)
  method get_beta() = beta;
  method set_beta beta0 = beta <- beta0;
  method beta_print() =
    print_float(beta);
    print_newline()

  method activate()=
    self#set_observed_output (1./.(1.+.(exp((-.beta)
                           *.(weight_sum))))); 
    (*calcule la valeur d'activation d'un neurone*)
      
  method neuron_print() =
    print_string("id : ");
    self#id_print();
    print_string("couche : ");
    self#layer_print();
    print_string("valeur desiree : ");
    self#wanted_output_print();
    print_string("valeur observee : ");
    self#observed_output_print()
end
