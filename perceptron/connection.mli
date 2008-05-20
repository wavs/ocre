class connection :
  object
    val mutable n1 : int
    val mutable n2 : int
    val mutable weight : float
    method getn1 : unit -> int
    method getn2 : unit -> int
    method getw : unit -> float
    method print : unit -> unit
    method setn1 : int -> unit
    method setn2 : int -> unit
    method setw : float -> unit
  end
