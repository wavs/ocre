class neuron =
object(self)

  val mutable value = 1.
  val mutable error = 0.
  val mutable nextweights = Array.make 1 1.
  method get_error () = error
  method set_error x = error <- x

  method get_value () = value
  method set_value x = value <- x

  method init_nextweights taille =
    let tab = Array.make taille 1. in
    for i = 0 to Array.length tab - 1 do
      let alea = Random.float 1. in
        if alea > 0.5 then
          Array.set tab i (Random.float 10.)
        else
          Array.set tab i (Random.float (-. 10.))
    done;
   nextweights <- tab

  method set_nextweight pos value = Array.set nextweights pos value
  method get_nextweight pos = Array.get nextweights pos

end
