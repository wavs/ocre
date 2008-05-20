class data :
  int ->
  int ->
  object
    val mutable inputs : float array
    val mutable outputs : float array
    method get_inputs : unit -> float array
    method get_outputs : unit -> float array
    method geti : unit -> int
    method geto : unit -> int
    method in_print : int -> unit
    method inputs_print : unit -> unit
    method out_print : int -> unit
    method outputs_print : unit -> unit
    method set_input : int -> float -> unit
    method set_inputs : float array -> unit
    method set_output : int -> float -> unit
    method set_outputs : float array -> unit
  end
class tabdata :
  object
    val mutable tab : data array
    method get_tab : unit -> data array
    method get_tab2 : unit -> data array
    method set_tab : data array -> unit
  end
