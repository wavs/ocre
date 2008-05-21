class data x y =
object(self)

  val mutable nbinputs = x
  val mutable nboutputs = y
  val mutable inputs = Array.make x 1
  val mutable outputs = Array.make y 1

  method get_nbinputs = nbinputs
  method set_nbinputs x = nbinputs <- x
  method set_nboutputs x = nboutputs <- x
  method get_nboutputs ()= nboutputs

  method set_input pos value = Array.set inputs pos value
  method get_input pos = Array.get inputs pos
  method set_inputs x  = inputs <- x
  method get_inputs () = inputs

  method set_output pos value = Array.set outputs pos value
  method get_output pos = Array.get outputs pos
  method set_outputs x  = outputs <- x
  method get_outputs () = outputs

end
