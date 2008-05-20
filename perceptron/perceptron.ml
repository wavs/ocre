
class perceptron =
object (self)
  val mutable nblayers = 1

  val mutable nbnbhl = 6

  val mutable treshold = 1. (*seuil pour heaviside*)

  val mutable lambda = 0.01 (*coef d'apprentissage*)

  val mutable iter = 500 (*nombre d'itérations pour l'apprentissage*)

  val mutable error = 0.

  val mutable neurons = Array.make 1 (new Neuron.neuron)

  val mutable connections = Array.make 1 (new Connection.connection)

  val mutable learningdata = Array.make 0 (new Data.data 0 0)

(**
*Retourne le nombre de couches du réseau
*)
  method getnbl() = nblayers

(**
*Remplace le nombre de couches du réseau par nbl0
*
*@param nbl0 un entier
*)
  method setnbl nbl0 = nblayers <- nbl0

(**
*Retourne le nombre de neurones par couche cachée 
*)
  method getnbn() = nbnbhl

(**
*Remplace le nombre de neurones par couche cachée par nbn0
*
*@param nbn0 un entier
*)
  method setnbn nbn0 = nbnbhl <- nbn0

(**
*Retourne le seuil de heaviside 
*)
  method gett() = treshold

(**
*Remplace le seuil de heaviside par t0
*
*@param t0 un float 
*)
  method sett t0 = treshold <- t0

(**
*Retourne lambda
*)
  method getl() = lambda

(**
*Remplace lambda par une autre valeur
*
*@param l0 un float
*)
  method setl l0 = lambda <- l0

(**
*Retourne iter
*)
  method getit() = iter

(**
*Remplace iter par une autre valeur
*
*@param i0 un entier
*)
  method setit i0 = iter <- i0

(**
*Retourne error (erreur totale moyenne du perceptron)
*)
  method geter() = error

(**
*Met à jour error 
*)
  method seter() = 
    let sum = ref 0. in
      for i = Array.length neurons - 1 downto 0 do
        let n = neurons.(i) in
          if n#getl() = nblayers then
            begin
              self#outerror (n#geti());
              sum := !sum +. n#gete()
            end
      done;
      error <- (0.5 *. float_of_int(learningdata.(0)#geto())) *. !sum  
    
(**
*Renvoie le neurone à la position i
*)
  method getn i = neurons.(i) 

(**
*Renvoie le vecteur de neurones 
*)
  method getns() = neurons

(**
*Remplace le vecteur de neurones par n0
*
*@param n0 un vecteur de neurones
*)
  method setns n0 = neurons <- n0

(**
*Remplace le neurone à la position i par n0
*
*@param i un entier
*@param n0 un neurone  
*)
  method setn i n0 = neurons.(i) <- n0

(**
*Trouve un neurone d'identifiant id
*
*@param id un identifiant entier 
*)
  method findn id = 
    let i = ref 0 in
      while (!i < Array.length neurons) &&
            (neurons.(!i)#geti() <> id) do
              i := !i + 1
      done;
      neurons.(!i)

(**
*Calcule le nombre total de neurones 
*)
  method nbn() =
    let result = ref 0 in 
      result := learningdata.(0)#geti() 
              + learningdata.(0)#geto()
              + (nblayers - 2) * nbnbhl ;
      !result

(**
*Initialise le vecteur de neurones 
*)
  method initneurons() = 
    (*init du vect de neurones*)
    self#setns (Array.make (self#nbn()) (new Neuron.neuron));
    (*init des id*)
    let nb_input = (learningdata.(0))#geti() in
    let nb_output = (learningdata.(0))#geto() in
    let layer_cpt = ref nb_input in  
      (*init des indicateurs de la couche d'entree*)
      for i = 0 to nb_input - 1 do
          let a = new Neuron.neuron in
            a#seti i;
            a#setl 1;
            self#setn i a;
        done; 
        (*init des indicateurs des couches cachees*)
        for i = 2 to nblayers - 1 do
          for j = !layer_cpt to !layer_cpt + nbnbhl - 1 do
            let a = new Neuron.neuron in
              a#seti j;
              a#setl i;
              self#setn j a; neurons.(j)#setl i
          done;
          layer_cpt := !layer_cpt + nbnbhl          
        done;
        (*init des indicateurs de la couche de sortie*)
        for i = Array.length neurons - nb_output to Array.length neurons - 1 do
          let a = new Neuron.neuron in
            a#seti i;
            a#setl nblayers;
            self#setn i a
        done

(**
*Affiche les infos sur les neurones 
*) 
  method nprint() = 
    print_newline();
    for i = 0 to Array.length neurons - 1 do
      neurons.(i)#print()
    done;
    print_newline()

(**
*Renvoie la connexion à la position i
*
*@param i un entier 
*)
  method getc i = connections.(i)

(**
*Renvoie le vecteur de connexions
*)
  method getcs() = connections

(**
*Remplace le vecteur de connexions par un autre
*
*@param c0 le nouveau vecteur de connexions 
*)
  method setcs c0 = connections <- c0

(**
*Remplace la connexion à la position i par c0
*
*@param i un entier
*@param c0 une connexion 
*)
  method setc i c0 = connections.(i) <- c0

(**
*Renvoie la connexion entre n1 et n2
*
*@param n1 un identifiant de neurone
*@param n2 un identifiant d'un autre neurone
*)
  method findc n1 n2 = 
    let i = ref 0 in
      while (!i < Array.length connections) && 
            not(connections.(!i)#getn1() = n1 &&
                connections.(!i)#getn2() = n2) do
              i := !i + 1
      done;
      connections.(!i)

(**
*Renvoie le nombre de connexions
*
*)
  method nbc() =
    let res1 = ref 0 in
    let data = learningdata.(0) in
    let indatalen = data#geti() in
    let outdatalen = data#geto() in
      res1 := indatalen * nbnbhl + nbnbhl * outdatalen;
      if nblayers >= 3 then
        res1 := !res1 + (nbnbhl * nbnbhl) * (nblayers - 3);
      !res1

(**
*Initialise les poids des connexions
*
*)
  method initweights() =
    Random.init 7;
    for i = 0 to Array.length connections - 1 do
      let c = connections.(i) in
      let alea = Random.float 1. in
        if alea > 0.5 then
          c#setw (Random.float 0.5)
        else
          c#setw (Random.float (-. 0.5))
    done

(**
*Initialise le vecteur de connexions et met leur poids à une val random petite
*
*)
  method initconnections() =
   self#setcs (Array.make (self#nbc()) (new Connection.connection));
    let k = ref 0 in
      while !k < self#nbc() do
        for i = 0 to Array.length neurons - 1 do
          for j = 0 to Array.length neurons - 1 do
            if neurons.(j)#getl() = neurons.(i)#getl() + 1 then
              begin
                let c = new Connection.connection in
                  c#setn1 (neurons.(i)#geti());
                  c#setn2 (neurons.(j)#geti());
                  self#setc (!k) c;
                  k := !k + 1
              end
          done
        done
      done;
    self#initweights();

(**
*Affiche les infos sur les connexions 
*) 
  method cprint() = 
    print_newline();
    for i = 0 to Array.length connections - 1 do
      connections.(i)#print()
    done;
    print_newline()

(**
*Retourne le vecteur de données
*)
  method getld() = learningdata

(**
*Remplace le vecteur de données
*
*@param ld0 est le vecteur de données remplaçant l'ancien
*)
  method setld ld0 = learningdata <- ld0

(**
*Fonction de permutation des données
*
*@remark permute l'ordre des données
*
*
*)
  method permutedata() =
    Random.self_init();
    let compareThatShit x y =
      let xx = Random.int 10 in
      let yy = Random.int 10 in
        if xx = yy then 0
        else
          if xx > yy then 1
          else (-1)
    in
      Array.sort compareThatShit learningdata

(**
*Imprime les données d'apprentissage à l'écran
*
*@remark that's fun !
*
*)
  method learningdata_print() =
    for i = 0 to Array.length learningdata - 1 do
      print_string ("Donnee n° "^string_of_int(i)^" :\n");
      learningdata.(i)#inputs_print();
      learningdata.(i)#outputs_print()
    done;

(**
*Charge les données dans le perceptron
*
*@remark il reste à les charger dans les neurones au cours de l'apprentissage
*
*)
  method initdata() =
    let td = new Data.tabdata in
      td#set_tab (td#get_tab2());
      self#setld (td#get_tab())

(**
*Fonction de somme pondérée
*
*@remark ceci est mon premier commentaire OCamlDoc
*
*@param n2 est l'id du neurone traîté
*
*)
  method getsum n2 = 
    let sum = ref 0. in
      for i = 0 to Array.length connections - 1 do
        let c = connections.(i) in
          if c#getn2() = n2 then
            let n1 = self#findn (c#getn1()) in
              sum := !sum +. c#getw() *. n1#getv() +. treshold
      done;
      !sum

(**
*Fonction de heaviside
*
*@remark ceci transforme la valeur de sortie en un 1 ou un 0
*
*@param x est un float
*
*)
  method heaviside x =
    if x < 0. then 0. else 1.

(**
*Fonction sigmoïde
*
*@remark ceci est la fonction d'activation du réseau
*
*@param x est un float
*
*)
  method sigmoid x =
    1./.(1. +. exp(-. x))

(**
*Fonction sigmoïde dérivée
*
*@remark ceci est ma foi une belle dérivée
*
*@param x est un float
*
*)
  method sigmoideriv x =
    (exp(-. x)) /. ((1. +. exp(-. x)) *. (1. +. exp(-. x)))

(**
*Erreur d'un neurone de sortie
*
*@param n est l'identifiant du neurone traîté
*
*)
  method outerror n =
    (self#findn n)#sete (self#sigmoideriv(self#getsum n) 
                *. ((self#getn n)#geth() 
                -. (self#getn n)#getv()))

(**
*Erreur d'un neurone d'une couche interne/d'entrée
*
*@param n est l'identifiant du neurone traîté
*
*)
  method inerror n =
    let sum = ref 0. in
      for i = 0 to Array.length neurons - 1 do
        let n2 = neurons.(i) in
          if n2#getl() = (self#findn n)#getl() + 1 then
            sum := !sum +. (self#findc n (n2#geti()))#getw() *. n2#gete()
      done;
      (self#findn n)#sete (self#sigmoideriv(self#getsum n) *. !sum)

(**
*Mise à jour des poids dans toutes les couches
*
*@remark l'apprentissage est donc opérationnel !
*
*)
  method wupdate() =
    for i = 0 to Array.length connections - 1 do
      let c = connections.(i) in
        c#setw (lambda *. ((self#findn (c#getn2()))#gete()) 
                       *. ((self#findn (c#getn1()))#getv()))
    done
  
(**
*Initialisation du réseau
*
*@remark c'est ça qui est bon
*
*)  
  method init() =
    self#initdata();
    self#initneurons();
    self#initconnections()

(**
*Procédeure d'apprentissage
*
*@remark soit on précise le nb iter soit on précise l'erreur à atteindre
*
*)  
  method learn() =
    self#init();
    for i = 0 to iter do

      (**)self#seter();
      print_string "erreur : ";
      print_float (self#geter());
      print_newline();(**)
      (*on permute les données*)
      self#permutedata();
      (*on met à jour les valeurs d'entrée*)
      for j = 0 to Array.length learningdata - 1 do
        for k = 0 to learningdata.(0)#geti() - 1 do
          neurons.(k)#setv ((learningdata.(j)#get_inputs()).(k))
        done;
        (*on met à jour les valeurs de sortie désirées*)
        let nb_output = learningdata.(0)#geto() in
        let r = ref 0 in
          for m = Array.length neurons - nb_output to Array.length neurons - 1
          do
            neurons.(m)#seth (((learningdata.(j))#get_outputs()).(!r));
            r := !r + 1
          done;
          (*on propage les entrées vers les sorties*)
          for o = 0 to Array.length neurons - 1 do
            let n = neurons.(o) in
              if n#getl() > 1 then
                begin
                  n#setv (self#sigmoid(self#getsum (n#geti())))
                end
          done;
          (*on calcule l'erreur des sorties et on rétropropage*)
          for q = 0 to Array.length neurons - 1 do
            let n = neurons.(q) in
              if n#getl() = nblayers then
                self#outerror (n#geti())
              else
                self#inerror (n#geti())
          done;
          (*on met à jour les poids dans toutes les couches*)
          self#wupdate()
      done
    done

(**
*Sauve dans un fichier les paramètres du réseau (poids)
*
*@remark on peut imaginer y stocker les coef qui vont bien aussi
*
*) 
  method save() = print_int(42)

(**
*Charge les paramètres du réseau
*) 
  method load() = print_int(69)

(**
*Reconnait le caractere dont l'indice est rentre
*
*@param
*
*) 
  method run x =
    for i = 0 to learningdata.(0)#geti() - 1 do
      neurons.(i)#setv ((learningdata.(x)#get_inputs()).(i))
    done;
      for o = 0 to Array.length neurons - 1 do
        let n = neurons.(o) in
          if n#getl() > 1 then
            begin
              n#setv (self#sigmoid(self#getsum (n#geti())))
            end
      done
end
