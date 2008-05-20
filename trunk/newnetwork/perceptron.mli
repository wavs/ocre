class perceptron :
  int ->
  int ->
  int ->
  int ->
object
  val mutable nblayers : int
  val mutable layers : Layer.layer array
  val mutable learning_rate : float
  val mutable patterns : Data.data
  val mutable quad_error : float
  method set_nblayers : int -> unit 
  method get_nblayers : unit -> int
  method init : unit -> unit
  method learn : unit -> unit
end
