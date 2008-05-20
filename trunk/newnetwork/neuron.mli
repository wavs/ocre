class neuron :
  object
    val mutable error : float
    val mutable nextweights : float array
    val mutable value : float
    method get_error : unit -> float
    method get_nextweight : int -> float
    method get_value : unit -> float
    method init_nextweights : int -> unit
    method set_error : float -> unit
    method set_nextweight : int -> float -> unit
    method set_value : float -> unit
  end
