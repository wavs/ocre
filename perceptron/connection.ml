class connection =
object (self)
  val mutable weight = 0.

  val mutable n1 = 0

  val mutable n2 = 0

  method getw() = weight
  method setw w0 = weight <- w0

  method getn1() = n1
  method setn1 n10 = n1 <- n10

  method getn2() = n2
  method setn2 n20 = n2 <- n20

  method print() = 
    print_string ("("^(string_of_int n1)^
                  ","^(string_of_int n2)^
                  ") : "^(string_of_float weight)^
                  "\n")
end

