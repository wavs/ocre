(***                                                     2008 © ***)
(******************************************************************)
(* OCRe                                                           *)
          (******)    (******)   (*****)  (****)
          (******)    (******)   (*****)  (****)
          (******)    (******)   (*****)  (****)
          (******************)   (*****)  (****)
          (******************)   (*****)  (****)
          (******)    (******)   (*************)
          (******)    (******)   (*************)
          (******)    (******)   (*************)


                 (**************)     (***********)  (***)
                 (**************)     (***********)  (***)
                 (*****)              (****)         (***)
                 (*****) (********)   (********)     (***)
                 (*****) (********)   (********)     (***)
                 (*****)    (***)     (****)
                 (**************)     (***********)  (***)
                 (**************)     (***********)  (***)
(*                                                                *)
(********************MULTI*LAYER*PERCEPTRON************************)
(***                                         by the HUGE Team © ***)



(*Neuron*)
(*****************************begin********************************)
class neuron =
object
  val mutable output = 0.; (*valeur de sortie du neurone*)
  method getoutput() = output; (*retourner output*)
  method setoutput output0 = output <- output0; (*modifier output*)

  val mutable sum = 0.; (*somme pondérée prise en paramètre par la fonction d'activation*)
  method getsum() = sum; (*retourner netsum*)
  method setsum sum0 = sum <- sum0; (*modifier netsum*)

  val mutable delta = 0.; (*permet de calculer la nouvelle valeur du poids de chaque connection après rétro-propagation de l'erreur*)
  method getdelta() = delta; (*retourner delta*)
  method setdelta delta0 = delta <- delta0; (*modifier delta*)

  val mutable beta = 0.5; (*paramètre de la fonction d'activation (prendre 0,5, 1 ou 5 par exemple)*)
  method getbeta = beta; (*retourner beta*)
  method setbeta beta0 = beta <- beta0; (*modifier beta*)

  val mutable weights = Array.make 1 0.5; (*vecteur de poids des connections avec les neurones précédents si il y en a*)
  method getweights() = weights; (*retourner weights*)
  method setweights weights0 = weights <- weights0; (*modifier weights*)

  method active() = output <- (1./.(1.+.(exp((-.beta)*.(sum))))); (*calcule la valeur d'activation d'un neurone*)

  method print() = (*affichage des infos du neurone*)
    print_newline();
    print_string "output value : ";
    print_float output;
    print_newline();
    print_string "sum value : ";
    print_float sum;
    print_newline();
    print_string "delta value : ";
    print_float delta;
    print_newline();
    print_string "beta value : ";
    print_float beta;
    print_newline();
    print_string "Weights vector values : "; (* /!\ afficher le contenu du vecteur de poids aussi - mettre une putain de 'a option /!\ *)
    print_newline();
    for j = 0 to (Array.length weights) - 1 do
      print_string "* ";
      print_float (weights.(j));
      print_newline()
    done
end
(******************************end*********************************)


(*Layer*)
(*****************************begin********************************)
class layer =
object
  val mutable neurons = (*vecteur de neurones de la couche*)
    Array.make 1 (new neuron);
  method getneurons() = neurons; (*retourner neurons*)
  method setneurons neurons0 = neurons <- neurons0; (*modifier neurons*)

  method print() = (*affiche les infos des neurones d'une couche*)
    for i = 0 to (Array.length neurons) - 1 do
      print_newline();
      (neurons.(i))#print();
      print_newline()
    done
end
(******************************end*********************************)


(*Perceptron*)
(*****************************begin********************************)
class perceptron =
object (self)
  val mutable bias = 1.; (*biais*)
  method getbias() = bias; (*retourner bias*)
  method setbias bias0 = bias <- bias0; (*modifier bias*)

  val mutable layers = Array.make 1 (new layer); (*tab des couches du réseau*)
  method getlayers() = layers; (*retourner layers*)
  method setlayers layers0 = layers <- layers0; (*modifier layers*)

  val mutable learnrate = 0.05; (*coefficient d'apprentissage*)
  method getlearnrate() = learnrate; (*retourner learnrate*)
  method setlearnrate learnrate0 = learnrate <- learnrate0; (*modifier learnrate*)

  method sum() = (*calcule la somme pondérée de chaque neurone de chaque couche*)
    for i = 1 to (Array.length layers) - 1 do (*on ne traite pas la première couche car elle ne dépend d'aucune sous-couche (d'où i = 1)*)
      for j = 0 to (Array.length (layers.(i)#getneurons())) - 1 do (*on parcourt chaque neurone de chaque couche*)
        (layers.(i)#getneurons()).(j)#setsum 0.; (*on initialise l'activation à zéro*)
        for k = 0 to (Array.length (layers.(i - 1)#getneurons())) - 1 do (*on parcourt chaque neurone de la couche précédente*)
          (layers.(i)#getneurons()).(j)#setsum ((layers.(i)#getneurons()).(j)#getsum() +.
                                                ((layers.(i - 1)#getneurons()).(k)#getoutput() +. bias) *.
                                                (((layers.(i)#getneurons()).(j)#getweights()).(k)))
        done; (*l'activation de chaque neurone de chaque couche est calculée et mise à jour au sein des neurones*)
      done;
    done

  method active() = (*calcule l'activation d'un neurone*)
    self#sum(); (*on actualise la valeur de sum*)
    for i = 1 to (Array.length layers) - 1 do (*on ne traite pas la première couche car elle ne dépend d'aucune sous-couche (d'où i = 1)*)
      for j = 0 to (Array.length (layers.(i)#getneurons())) - 1 do (*on parcourt chaque neurone de chaque couche*)
        (layers.(i)#getneurons()).(j)#active() (*nécessite de passer sum juste avant pour être correct*)
      done; (*activation calculée pour chaque neurone de chaque couche*)
    done

  (*method delta() = (*calcule le nouveau delta qui servira à calculer le nouveau poids de chaque connexion*)
    for i = 1 to (Array.length layers) - 1 do (*on parcourt la liste des couches*)
      for j = 0 to (Array.length (layers.(i)#getneurons())) - 1 do (*on traite différemment la couche de sortie des autres*)
        if i = (Array.length layers) - 1 then
          (layers.(i)#getneurons()).(j)#setdelta (((*f'*)((layers.(i)#getneurons()).(j)#getsum())) *.
                                                  ((*Tj*) -. (layers.(i)#getneurons()).(j)#getoutput()) )
        else
          (layers.(i)#getneurons()).(j)#setdelta ((*f'*)((layers.(i)#getneurons()).(j)#getsum())) *.
                                                  (layers.(i)#getneurons()).(j + 1)#getdelta() *.
                                                  ((layers.(i)#getneurons()).(j + 1)#getweights()).(j))
 done;
 done

  method weights() = (*met à jour les poids des connections grâce au delta calculé*)
    for i = 1 to (Array.length layers) - 1 do (*on parcourt la liste des couches*)
      for j = 1 to (Array.length (layers.(i)#getneurons())) - 1 do (*o*)
        
      done;
    done*)
end
(******************************end*********************************)


let main() = (*Boucle principale*)
  for i = 1 to 42 do
    print_string
("


(******)    (******)   (*****)  (****)
(******)    (******)   (*****)  (****)
(******)    (******)   (*****)  (****)
(******************)   (*****)  (****)
(******************)   (*****)  (****)
(******)    (******)   (*************)
(******)    (******)   (*************)
(******)    (******)   (*************)


       (**************)     (***********)  (***)
       (**************)     (***********)  (***)
       (*****)              (****)         (***)
       (*****) (********)   (********)     (***)
       (*****) (********)   (********)     (***)
       (*****)    (***)     (****)
       (**************)     (***********)  (***)
       (**************)     (***********)  (***)

")
  done

let _ = main()


(*THE END*)
