class perceptron input output nbhlayers nbn =
object(self)

  val mutable nblayers = nbhlayers + 2
  val mutable layers = ref (Array.make (nbhlayers + 2)
    (new Layer.layer nbn))
  val mutable learning_rate = 10.
  val mutable patterns = new Data.tab_xor
  val mutable quad_error = 69.

  method get_quad () = quad_error
  method set_quad x = quad_error <- x


  method print_layer () =
    print_string("Il y'a: "^string_of_int(nblayers)^" couches\n");
    for i = 0 to nblayers - 1 do
      print_string("couche numero"^string_of_int(i + 1)^": \n");
      !layers.(i)#print_neurons();
    done;
  method print_layer_and_weight () =
    print_string("Il y'a: "^string_of_int(nblayers)^" couches\n\n");
    for i = 0 to nblayers - 1 do
      print_string("couche numero"^string_of_int(i + 1)^": \n\n");
     !layers.(i)#print_weight_and_neuron();
    done;


  method set_nblayers x = nblayers <- x
  method get_nblayers() = nblayers

  method init() =
    !layers.(0) <- new Layer.layer input;
    !layers.(nbhlayers + 1) <- new Layer.layer output;
      for i = 0 to nblayers - 3 do
        !layers.(i)#init_neurons nbn;
      done;
      (!layers.(nblayers -2))#init_neurons output;
      (!layers.(nblayers -1))#init_neurons 0;
      patterns#init_tab()



  method learn() = print_int 42



(*

7 etapes :

   1. Placer le groupe de données (pattern) en entré
   2. Trouver les valeurs des cellules cachées
   3. Trouver les valeurs des cellules de sortie
   4. Trouver l'erreur dans la couche de sortie
   5. Utiliser l'algorithme de rétro-propagation pour ajuster les poids des connections menant aux cellules de sortie
   6. Utiliser une formule pour trouver les erreurs sur la couche cachée
   7. Ajuster les poids menant aux cellules de la couche cachée

*)

(*boucle principale insert here*)

(*1*)
  method set_input_pattern numero =
    let inlayer = !layers.(0) in
    let data = patterns#get_pos_tab numero in
      for i = 0 to inlayer#get_nbneurons() - 1 do
        begin
          inlayer#set_neurons_value
            i
            (float_of_int(data#get_input  i));
        end
      done;
      (!layers).(0) <- inlayer
(*2*)
  method set_forward_propagate () =
    let f x beta= 1./.(1. +. exp(float_of_int(beta) *. -.1. *. x)) in
    print_string(string_of_int(nblayers));
    for i = 1 to nblayers - 1 do
      (*pour chaque couches je parcours chaque neuronne*)

      for j = 0 to (!layers).(i)#get_nbneurons() - 1 do
        (*pour chaque neurones je calcule la nouvelle valeur des
          cellules cachees :D pourquoi parceque je le vaux bien! *)
        let newvalue = ref 0. in
        for k = 0 to (!layers).(i - 1)#get_nbneurons() - 1 do
          (* cette nouvelle valeur est equivalente a la somme des
             (chaque valeur des neurones de la couche precedente fois
             le poid entre ce dernier et le neurone courrant)*)
          newvalue := !newvalue +.
            (((!layers).(i - 1)#get_neurons k)#get_value() *.
               (((!layers).(i -1)#get_neurons k)#get_nextweight j))
        done;
          (*oups pas oublie le biais*)
          newvalue := !newvalue +.
            (((((!layers).(i - 1))#get_bias ())#get_value()) *.
               (((!layers).(i -1)#get_bias())#get_nextweight j));
          (*applique la fonction d'activation*)
          newvalue := (f !newvalue 1);
          (*remise a jour de la valeur des neurones de la couche
        cachees*)
          ((!layers).(i)#get_neurons j)#set_value !newvalue;
      done;
    done;
(*3*)
    (* Il semblerai que l'etape trois est lieu a notre etape 2. il se
       pourrait que l'on doit applique une application similaire a
        heaviside
*)
(*4*)
    (* L'on doit ici proceder au calcul de l'erreur de la sortie qui
       peut s'ecrire sous cette forme : f(x)*(1 - f(x)*(d - y))
       or f(x) a deja etait calcule!!*)
  method set_error_for_ouput_neurons num_pattern =
    let llayer = (!layers).(nblayers - 1) in
      for i = 0 to llayer#get_nbneurons() - 1 do
        let fx = llayer#get_neurons_value i in
        let d = patterns#get_pos_tab num_pattern in
        let error = fx*.(1. -. fx)*.
          ((float_of_int (d#get_output i)) -. fx) in
          llayer#set_neurons_error i error;
          print_string("this is the output"^string_of_int(d#get_output i)^"\n");
      done

(* on rajoute une methode qui nous permet de calculer l'erreur quad
   qui rappellons le est de la form: somme des[ (theo - valeur
   obtenu)au caarre] il peut etre sympa de la diviser par le nbr de
   neurones;*)
  method set_err_quad num_pattern =
    let llayer = (!layers).(nblayers - 1) in
    let sum = ref 0. in
      for i = 0 to llayer#get_nbneurons() - 1 do
        let f = llayer#get_neurons_value i in
        let d = float_of_int((patterns#get_pos_tab num_pattern)#get_output i) in
          sum := !sum +. ((d -. f) *. (d -. f));
      done;
      self#set_quad (!sum /. float_of_int(llayer#get_nbneurons()))

(* Pour 5-6-7 deux choix se presentent: calcule d'erreur en fonction
   des poids precedent ou calcule des poids puis des erreurs; il
   semblerai donc que je sois oblige de coder deux fonctions de
   backpropagation qui s'appelleront chacune backp1 et backp2 je
   devrais mettre deux k .. ca ferait kk comme ca ! Bahh c'est KK p2*)
(*5*)
  (*  poid ij = poid ij + coef d'apprendtissage*erreurj*valeuri
      le learning_rate c'est le nom de la variable*)
  method backpropagation_weight num_couche =
      (*on va parcourrir la liste des poids de chaques neuronnes*)
      for i = 0 to ((!layers).(num_couche -1))#get_nbneurons() - 1 do
        (* on s'occupe du neurone numero i*)
        let neuron = (!layers).(num_couche -1)#get_neurons i in
          for j = 0 to (Array.length (neuron#get_nextweights())) - 1 do
(*             neuron#print_weight(); *)
(*             print_string("juste avant ct le poid du neurons\n"); *)
            let newpoid =
              (neuron#get_nextweight j) +.
              (learning_rate *.
              (((!layers).(num_couche)#get_neurons_error j))*.
             neuron#get_value()) in
            neuron#set_nextweight j newpoid;
(*             neuron#print_weight(); *)
          (*   print_string("juste avant ct les poids des neurones apres le changement de poids!!\n"); *)
(*             print_string(string_of_int(i)^"to neurone"^string_of_int(j)^"\n"); *)
         done;
          ((!layers).(num_couche -1))#set_neurons i neuron;
      done;
      (*JE NE Dois pas oublie le biais!*)
    let bias =  (!layers).(num_couche -1)#get_bias() in
      for j = 0 to (Array.length (bias#get_nextweights())) - 1 do
        let newpoid =
            (bias#get_nextweight j) +.
              (learning_rate *.
                 (((!layers).(num_couche)#get_neurons_error j))*.
             bias#get_value()) in
            bias#set_nextweight j newpoid;
        done;
        ((!layers).(num_couche -1))#set_bias bias
(*6*)
          (*il faudra ptet penser a faire une boucle pour faire ceci
            quelque soit le nombre de couche!!*)
    (*soit i -> j ou j neuronne de sortie alors on a l'erreur du
      neuronne i qui vaut (fprime de la valeur du neuronne i) multiplie
      par la somme des erreurs des neuronne j fois la valeur des
      poids de i vers j*)
  method refresh_hidden_neurons_value num_couche =
(* pour i = 0 jusquau nombre de neuronne -1 faire *)
(*     calcule de l'erreur du neuroone() = *)
(*     calcule de la somme des poid* les erreurs *)
(*       pour j = 0 jusqua taille du tableau de poid faire *)
(*     sum := sum + (valeur du poid en j)*valeur de l'erreur dans la *)
(*     couche suivant du neurone j *)
(*     f'de la valeur du neuronne multiplie par sum *)
(*     finpour *)
    for i = 0 to ((!layers).(num_couche -1))#get_nbneurons() - 1 do
      let sum = ref 0. in
      let neuron = (!layers).(num_couche -1)#get_neurons i in
        for j = 0 to ((Array.length (neuron#get_nextweights())) - 1)
        do
          sum := !sum +. (neuron#get_nextweight j)*.
            (((!layers).(num_couche))#get_neurons j)#get_error();
        done;
        neuron#set_error ((neuron#get_value()) *.
                            (1. -. (neuron#get_value()))
                          *. !sum);
        (!layers).(num_couche -1)#set_neurons i neuron;
    done

(*7*)
(*enfaite l'on va passer outre les 7 points exposer plus haut la 7eme
  fonction aurra pour but de faire une retropopagation total a partir
  du calcule de l'erreur sur les sorties!*)
  method back_propagation () =
    let cpt = ref (nblayers - 1) in
      (*notre cpt voit les couches en virtuelle comme si elles
        allaient de 1 a n ou n et le nombre de couches*)
      while (!cpt > 0) do
        (* mise a jour des poids  *)
(*           si on est pas sur la premiere couche mise a jour des
             erreur *)
        self#backpropagation_weight !cpt;
        if (!cpt > 1) then
          self#refresh_hidden_neurons_value !cpt;
        cpt := !cpt - 1;
      done;

end
