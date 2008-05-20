class layer =
object(self)

  val mutable nbneurons = 42
  val mutable neurons = Array.make nbneurons (new Neuron.neuron)
  val mutable bias = new Neuron.neuron

end
