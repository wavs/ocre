class layer nbn =
object(self)

  val mutable nbneurons = nbn
  val mutable neurons = Array.make nbn (new Neuron.neuron)
  val mutable bias = new Neuron.neuron
  method init_neurons nb_arc_avt =
    for i = 0 to Array.length  neurons - 1 do
      (neurons.(i))#init_nextweights nb_arc_avt
    done;
    bias#init_nextweights nb_arc_avt
  method set_nbneurons x  = nbneurons <- x
  method get_nbneurons () = nbneurons

  method set_bias x  = bias <- x
  method get_bias () = bias

  method get_tabneurons () = neurons
  method set_tabneurons x = neurons <- x

end
