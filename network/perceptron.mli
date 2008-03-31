class perceptron :
  object
    val mutable bias : float
    val mutable connections : Connection.connection array
    val mutable delta : float
    val mutable delta_sum : float
    val mutable error_sum : float
    val mutable eta : float
    val mutable learning_data : Data.data array
    val mutable nb_layers : int
    val mutable nb_n_by_l : int
    val mutable nb_neurons : int
    val mutable neurons : Neuron.neuron array
    val mutable treshold : int
    val mutable v_obs_out : float array
    val mutable v_want_out : float array
    method activation : unit -> unit
    method adjust_weights : unit -> unit
    method calc_delta : Connection.connection -> unit
    method calc_delta_sum : Connection.connection -> float
    method calc_error_sum : unit
    method calc_nb_neurons : unit -> int
    method connections_print : unit -> unit
    method error_sum_print : unit -> unit
    method eta_print : unit -> unit
    method find_neuron : int -> Neuron.neuron
    method get_bias : unit -> float
    method get_connections : unit -> Connection.connection array
    method get_delta : unit -> float
    method get_delta_sum : unit -> float
    method get_error_sum : unit -> float
    method get_eta : unit -> float
    method get_learning_data : unit -> Data.data array
    method get_nb_layers : unit -> int
    method get_nb_n_by_l : unit -> int
    method get_nb_neurons : unit -> int
    method get_neurons : unit -> Neuron.neuron array
    method get_obs_out : unit -> float array
    method get_treshold : unit -> int
    method get_want_out : unit -> float array
    method init : unit -> unit
    method init_connections : unit -> unit
    method init_neurons : unit -> unit
    method init_weights : unit -> unit
    method learning_data_print : unit -> unit
    method load : unit -> unit
    method nb_connections : unit -> int
    method nb_layers_print : unit -> unit
    method nb_n_by_l_print : unit -> unit
    method nb_neurons_print : unit -> unit
    method neurons_print : unit -> unit
    method obs_out_print : int -> unit
    method permute_data : unit -> unit
    method run : int -> unit
    method save : unit -> unit
    method set_bias : float -> unit
    method set_connection : int -> int -> float -> unit
    method set_connection1 : int -> Connection.connection -> unit
    method set_connections : Connection.connection array -> unit
    method set_delta : float -> unit
    method set_delta_sum : float -> unit
    method set_error_sum : float -> unit
    method set_eta : float -> unit
    method set_learning_data : Data.data array -> unit
    method set_nb_layers : int -> unit
    method set_nb_n_by_l : int -> unit
    method set_nb_neurons : int -> unit
    method set_neuron : int -> Neuron.neuron -> unit
    method set_neurons : Neuron.neuron array -> unit
    method set_obs_out : int -> float -> unit
    method set_treshold : int -> unit
    method set_v_obs_out : float array -> unit
    method set_v_obs_out2 : unit -> unit
    method set_v_want_out : float array -> unit
    method set_v_want_out2 : unit -> unit
    method set_want_out : int -> float -> unit
    method train : unit -> unit
    method treshold_print : unit -> unit
    method update_v_obs_out : unit -> unit
    method update_v_want_out : int -> unit
    method v_obs_out_print : unit -> unit
  end
