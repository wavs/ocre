
class connection =
object (self)
  val mutable v1 = - 666
  method get_v1() = v1
  method set_v1 v10 = v1 <- v10

  val mutable v2 = - 666
  method get_v2() = v2
  method set_v2 v20 = v2 <- v20

  method couple_print() =
    print_string("("^string_of_int(v1)^","^ string_of_int(v2)^")");
    print_newline()

  val mutable weight = 0.
  method get_weight() = weight
  method set_weight weight0 = weight <- weight0
  method weight_print() =
    print_float(weight);
    print_newline()

  method connection_print() =
    print_newline();
    print_string("Connexion : ");
    self#couple_print();
    print_string("Poids : ");
    self#weight_print()

end
