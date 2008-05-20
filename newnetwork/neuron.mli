class neuron :
  object
    val mutable error : float
    val mutable nextweights : float array
    val mutable value : float
    method print_error : unit -> unit
    method print_value : unit -> unit
    method print_weight : unit -> unit
    method print_neuron : unit -> unit
    method print_neuron_and_weight : unit -> unit


    method get_error : unit -> float
    method get_nextweight : int -> float
      method get_nextweights : unit -> float array

    method get_value : unit -> float
    method init_nextweights : int -> unit
    method set_error : float -> unit
    method set_nextweight : int -> float -> unit
      method set_nextweights : float array -> unit

    method set_value : float -> unit
  end
