class layer nbn =
object(self)

  val mutable nbneurons = nbn
  val mutable neurons = Array.make nbn (new Neuron.neuron)
  val mutable bias = new Neuron.neuron

end
