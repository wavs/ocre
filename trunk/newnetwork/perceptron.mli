class perceptron :
  int ->
  int ->
  int ->
  int ->
object
  val mutable nblayers : int
  val mutable layers : Layer.layer array
  val mutable learning_rate : float
  val mutable patterns : Data.tab_xor
  val mutable quad_error : float
  method print_layer : unit -> unit
  method print_layer_and_weight : unit -> unit
  method set_nblayers : int -> unit
  method get_nblayers : unit -> int
  method init : unit -> unit
  method learn : unit -> unit

  method set_input_pattern : int -> unit
end
