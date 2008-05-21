class data :
  int ->
  int ->
  object
    val mutable inputs : int array
    val mutable nbinputs : int
    val mutable nboutputs : int
    val mutable outputs : int array
      method get_input : int -> int
      method get_inputs : unit -> int array
      method get_nbinputs : int
      method get_nboutputs : unit -> int
      method get_output : int -> int
      method get_outputs : unit -> int array
      method init_bool_op : int -> int -> int -> unit
      method set_input : int -> int -> unit
      method set_inputs : int array -> unit
      method set_nbinputs : int -> unit
      method set_nboutputs : int -> unit
      method set_output : int -> int -> unit
      method set_outputs : int array -> unit
  end

class tab_xor :
object
  val mutable tab : data array
  method get_tab : unit -> data array
  method set_tab : data array -> unit
  method init_tab : unit -> unit
  method get_pos_tab : int -> data
end
