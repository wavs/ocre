class perceptron :
  int ->
  int ->
  int ->
  int ->
object
  val mutable layers : Layer.layer array
  val mutable learning_rate : float
  val mutable nblayers : int
  val mutable patterns : Data.tab_xor
  val mutable quad_error : float
  method get_nblayers : unit -> int
  method init : unit -> unit
  method learn : unit -> unit
  method print_layer : unit -> unit
  method print_layer_and_weight : unit -> unit
  method set_forward_propagate : unit -> unit
  method set_input_pattern : int -> unit
  method set_nblayers : int -> unit
  method set_error_for_ouput_neurons : int -> unit
end
