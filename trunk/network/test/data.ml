class data = 
object (self)
  val mutable taille_du_sexe = "HUGE"
  method get_t() = taille_du_sexe
  method set_t t0 = taille_du_sexe <- t0
    
  val mutable endurance = "42 secondes"
  method get_e() = endurance
  method set_e a0 = endurance <- e0
end
