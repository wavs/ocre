class perceptron :
  int ->
  int ->
  int ->
  < get_patterns : unit ->
                   (< get_inputs : unit -> float array;
                      get_outputs : unit -> float array; .. >
                    as 'a)
                   array;
    .. > ->
  object
    val mutable hidd_errors : float array
    val mutable hidd_out_weights_v : float array array
    val mutable hiddenlayer : float array
    val mutable in_hidd_weights_v : float array array
    val mutable inputs : float array
    val mutable learning_rate : float
    val mutable out_errors : float array
    val mutable outputs : float array
    val mutable pattern : 'a
    val mutable patterns : 'a array
    val mutable quad : float
    method activation : float -> float
    method error_hidd : unit -> unit
    method error_out : unit -> unit
    method forward : unit -> unit
    method get_hidd_error : int -> float
    method get_hidd_errors : unit -> float array
    method get_hidd_out_weight : int -> int -> float
    method get_hidd_out_weights : int -> float array
    method get_hidd_out_weights_v : unit -> float array array
    method get_hiddenlayer : unit -> float array
    method get_hiddenlayern : int -> float
    method get_in_hidd_weight : int -> int -> float
    method get_in_hidd_weights : int -> float array
    method get_in_hidd_weights_v : unit -> float array array
    method get_input : int -> float
    method get_inputs : unit -> float array
    method get_leaning_rate : unit -> float
    method get_out_error : int -> float
    method get_out_errors : unit -> float array
    method get_output : int -> float
    method get_outputs : unit -> float array
    method get_quad : unit -> float
    method learn : unit -> unit
    method netsum1 : unit -> unit
    method netsum2 : unit -> unit
    method permute_patterns : unit -> unit
    method pretty_print : unit -> unit
    method print_hidd_errors : unit -> unit
    method print_hidd_out_weights_v : unit -> unit
    method print_hiddenlayer : unit -> unit
    method print_in_hidd_weights_v : unit -> unit
    method print_inputs : unit -> unit
    method print_learning_rate : unit -> unit
    method print_out_errors : unit -> unit
    method print_outputs : unit -> unit
    method print_quad : unit -> unit
    method quaderror : unit -> unit
    method set_hidd_error : int -> float -> unit
    method set_hidd_errors : float array -> unit
    method set_hidd_out_weight : int -> int -> float -> unit
    method set_hidd_out_weights : int -> float array -> unit
    method set_hidd_out_weights_v : float array array -> unit
    method set_hiddenlayer : float array -> unit
    method set_hiddenlayern : int -> float -> unit
    method set_in_hidd_weight : int -> int -> float -> unit
    method set_in_hidd_weights : int -> float array -> unit
    method set_in_hidd_weights_v : float array array -> unit
    method set_input : int -> float -> unit
    method set_inputs : float array -> unit
    method set_learning_rate : float -> unit
    method set_out_error : int -> float -> unit
    method set_out_errors : float array -> unit
    method set_output : int -> float -> unit
    method set_outputs : float array -> unit
    method set_quad : float -> unit
    method weight_up_hidd : unit -> unit
    method weight_up_out : unit -> unit
  end
