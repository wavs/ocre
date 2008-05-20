class neuron :
  object
    val mutable error : float
    val mutable id : int
    val mutable layer : int
    val mutable th : float
    val mutable value : float
    method gete : unit -> float
    method geth : unit -> float
    method geti : unit -> int
    method getl : unit -> int
    method getv : unit -> float
    method print : unit -> unit
    method sete : float -> unit
    method seth : float -> unit
    method seti : int -> unit
    method setl : int -> unit
    method setv : float -> unit
  end
