class perceptron input output nbhlayers nbn =
object(self)

  val mutable nblayers = nbhlayers + 2
  val mutable layers = Array.make (nbhlayers + 2)
    (new Layer.layer nbn)
  val mutable learning_rate = 0.1
  val mutable patterns = new Data.tab_xor
  val mutable quad_error = 69.

  method print_layer () =
    print_string("Il y'a: "^string_of_int(nblayers)^" couches\n");
    for i = 0 to nblayers - 1 do
      print_string("couche numero"^string_of_int(i + 1)^": \n");
      layers.(i)#print_neurons();
    done;
  method print_layer_and_weight () =
    print_string("Il y'a: "^string_of_int(nblayers)^" couches\n\n");
    for i = 0 to nblayers - 1 do
      print_string("couche numero"^string_of_int(i + 1)^": \n\n");
      layers.(i)#print_weight_and_neuron();
    done;


  method set_nblayers x = nblayers <- x
  method get_nblayers() = nblayers

  method init() =
    layers.(0) <- new Layer.layer input;
    layers.(nbhlayers + 1) <- new Layer.layer output;
      for i = 0 to nblayers - 3 do
        layers.(i)#init_neurons nbn;
      done;
      (layers.(nblayers -2))#init_neurons output;
      (layers.(nblayers -1))#init_neurons 0;
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
    let inlayer = layers.(0) in
    let data = patterns#get_pos_tab numero in
      for i = 0 to inlayer#get_nbneurons() - 1 do
        begin
          inlayer#set_neurons_value
            i
            (float_of_int(data#get_input  i));
        end
      done;
      layers.(0) <- inlayer
(*2*)
  method set_forward_propagate () =
    print_string(string_of_int(nblayers));
    for i = 1 to nblayers - 1 do
      (*pour chaque couches je parcours chaque neuronne*)
      let newvalue = ref 0. in
      for j = 0 to layers.(i)#get_nbneurons() - 1 do
        (*pour chaque neuronnes je calcule la nouvelle valeur des
          cellules cachees :D pourquoi parceque je le vaux bien! *)
        for k = 0 to layers.(i - 1)#get_nbneurons() - 1 do
          (* cette nouvelle valeur est equivalente a la somme des
             (chaque valeur des neurones de la couche precedente fois
             le poid entre ce dernier et le neurone courrant)*)
          newvalue := !newvalue +.
            ((layers.(i - 1)#get_neurons k)#get_value() *.
               ((layers.(i -1)#get_neurons k)#get_nextweight j))
        done;
      done;
    done;
(*3*)

(*4*)

(*5*)

(*6*)

(*7*)

end
