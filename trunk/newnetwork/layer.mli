class layer :
  int ->
  object
    val mutable bias : Neuron.neuron
    val mutable nbneurons : int
    val mutable neurons : Neuron.neuron array
    method print_neurons : unit -> unit
    method print_weight_and_neuron : unit -> unit

    method init_neurons : int -> unit
    method set_bias : Neuron.neuron -> unit
    method get_bias : unit -> Neuron.neuron

    method get_tabneurons : unit -> Neuron.neuron array
    method set_tabneurons : Neuron.neuron array -> unit

    method set_nbneurons : int -> unit
    method get_nbneurons : unit -> int

    method set_neurons : int -> Neuron.neuron -> unit
    method get_neurons : int -> Neuron.neuron
    method set_neurons_value : int -> float -> unit

  end
