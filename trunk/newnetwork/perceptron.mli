class perceptron :
  int ->
  int ->
  int ->
  int ->
object
  val mutable layers : Layer.layer array ref
  val mutable learning_rate : float
  val mutable nblayers : int
  val mutable pattern_alpha : Data.alphabet
  val mutable pattern_input : Data.data_alpha
  val mutable pattern_output : int
  val mutable patterns : Data.tab_xor
  val mutable quad_error : float
  method back_propagation : unit -> unit
  method backpropagation_weight : int -> unit
  method boucle_learn : int -> unit
  method boucle_learn_alpha : int -> unit
  method foi : int -> float
  method get_nblayers : unit -> int
  method get_pattern_alpha : Data.alphabet
  method get_pattern_input : Data.data_alpha
  method get_pattern_output : int
  method get_quad : unit -> float
  method init : unit -> unit
  method learn : unit -> unit
  method learn_pattern : int -> unit
  method learn_pattern_alpha : unit -> unit
  method print_layer : unit -> unit
  method print_layer_and_weight : unit -> unit
  method refresh_hidden_neurons_value : int -> unit
  method set_err_quad : int -> unit
  method set_err_quad_alpha : unit -> unit
  method set_error_for_ouput_neurons : int -> unit
  method set_error_for_ouput_neurons_alpha : unit -> unit
  method set_forward_propagate : unit -> unit
  method set_input_pattern : int -> unit
  method set_input_pattern_alpha : unit -> unit
  method set_nblayers : int -> unit
  method set_pattern_alpha : Data.alphabet -> unit
  method set_pattern_input : Data.data_alpha -> unit
  method set_pattern_output : int -> unit
  method set_quad : float -> unit
  method test_pattern : unit -> unit
  method test_pattern_alpha : unit -> unit
  method train_for_noob : int -> unit
end
