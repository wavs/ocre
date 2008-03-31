class connection :
  object
    val mutable v1 : int
    val mutable v2 : int
    val mutable weight : float
    method connection_print : unit -> unit
    method couple_print : unit -> unit
    method get_v1 : unit -> int
    method get_v2 : unit -> int
    method get_weight : unit -> float
    method set_v1 : int -> unit
    method set_v2 : int -> unit
    method set_weight : float -> unit
    method weight_print : unit -> unit
  end
