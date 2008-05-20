class data x y =
object(self)

  val mutable nbinputs = x
  val mutable nboutputs = y
  val mutable inputs = Array.make x 1
  val mutable outputs = Array.make y 1 

end
  
