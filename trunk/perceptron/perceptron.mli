class perceptron :
  object
    val mutable connections : Connection.connection array
    val mutable error : float
    val mutable iter : int
    val mutable lambda : float
    val mutable learningdata : Data.data array
    val mutable nblayers : int
    val mutable nbnbhl : int
    val mutable neurons : Neuron.neuron array
    val mutable treshold : float
    method cprint : unit -> unit
    method findc : int -> int -> Connection.connection
    method findn : int -> Neuron.neuron
    method getc : int -> Connection.connection
    method getcs : unit -> Connection.connection array
    method geter : unit -> float
    method getit : unit -> int
    method getl : unit -> float
    method getld : unit -> Data.data array
    method getn : int -> Neuron.neuron
    method getnbl : unit -> int
    method getnbn : unit -> int
    method getns : unit -> Neuron.neuron array
    method getsum : int -> float
    method gett : unit -> float
    method heaviside : float -> float
    method inerror : int -> unit
    method init : unit -> unit
    method initconnections : unit -> unit
    method initdata : unit -> unit
    method initneurons : unit -> unit
    method initweights : unit -> unit
    method learn : unit -> unit
    method learningdata_print : unit -> unit
    method load : unit -> unit
    method nbc : unit -> int
    method nbn : unit -> int
    method nprint : unit -> unit
    method outerror : int -> unit
    method permutedata : unit -> unit
    method run : int -> unit
    method save : unit -> unit
    method setc : int -> Connection.connection -> unit
    method setcs : Connection.connection array -> unit
    method seter : unit -> unit
    method setit : int -> unit
    method setl : float -> unit
    method setld : Data.data array -> unit
    method setn : int -> Neuron.neuron -> unit
    method setnbl : int -> unit
    method setnbn : int -> unit
    method setns : Neuron.neuron array -> unit
    method sett : float -> unit
    method sigmoid : float -> float
    method sigmoideriv : float -> float
    method wupdate : unit -> unit
  end
