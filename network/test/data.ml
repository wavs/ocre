class data = 
object (self)
  val mutable taille_du_sexe = "HUGE"
  method get_t() = taille_du_sexe
  method set_t t0 = taille_du_sexe <- t0

  val mutable andurance = "42 secondes"
  method get_a() = andurance
  method set_a a0 = andurance <- a0
end
