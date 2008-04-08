class neuron =
object (self)
  val mutable value = 0.

  val mutable id = 0

  val mutable layer = 0

  val mutable error = 0.

  val mutable th = 0.

  method getv() = value
  method setv v0 = value <- v0

  method geti() = id
  method seti i0 = id <- i0

  method getl() = layer
  method setl l0 = layer <- l0

  method gete() = error
  method sete e0 = error <- e0

  method geth() = th
  method seth th0 = th <- th0

  method print() =
    print_string ("id : "^(string_of_int id)^
                  " value : "^(string_of_float value)^
                  " layer : "^(string_of_int layer)^
                  " error : "^(string_of_float error)^
                  "\n")
end

