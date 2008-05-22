class pattern :
  object
    val mutable inputs : float array
    val mutable outputs : float array
    method get_inputs : unit -> float array
    method get_outputs : unit -> float array
    method print_inputs : unit -> unit
    method print_outputs : unit -> unit
    method set_inputs : float array -> unit
    method set_outputs : float array -> unit
  end
