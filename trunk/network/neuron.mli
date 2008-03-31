class neuron :
  object
    val mutable beta : float
    val mutable error : float
    val mutable id : int
    val mutable layer : int
    val mutable observed_output : float
    val mutable wanted_output : float
    val mutable weight_sum : float
    method activate : unit -> unit
    method beta_print : unit -> unit
    method calc_error : unit -> unit
    method calc_error2 : unit -> unit
    method error_print : unit -> unit
    method get_beta : unit -> float
    method get_error : unit -> float
    method get_id : unit -> int
    method get_layer : unit -> int
    method get_observed_output : unit -> float
    method get_wanted_output : unit -> float
    method get_weight_sum : unit -> float
    method id_print : unit -> unit
    method layer_print : unit -> unit
    method neuron_print : unit -> unit
    method observed_output_print : unit -> unit
    method set_beta : float -> unit
    method set_error : float -> unit
    method set_id : int -> unit
    method set_layer : int -> unit
    method set_observed_output : float -> unit
    method set_wanted_output : float -> unit
    method set_weight_sum : float -> unit
    method wanted_output_print : unit -> unit
    method weight_sum_print : unit -> unit
  end
