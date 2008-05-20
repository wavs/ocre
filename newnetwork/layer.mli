class layer :
  int ->
  object
    val mutable bias : Neuron.neuron
    val mutable nbneurons : int
    val mutable neurons : Neuron.neuron array
  end
