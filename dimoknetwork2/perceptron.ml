class perceptron nbneuronbyhiddenlayer 
                 nbinputs 
                 nboutputs
                 data =
object(self)
  
  val mutable patterns = Array.make 4 (new Pattern.pattern)
  val mutable current_pattern = data.(0)
  val mutable quad = 10.
  val mutable learning_rate = 0.1
  val mutable inputs = (data.(0))#get_inputs()
  val mutable hiddenlayer = Array.make nbneuronbyhiddenlayer 1.
  val mutable outputs = Array.make nboutputs 1.
  val mutable in_hidd_weights_v = Array.make nbinputs 
                               (Array.make nbneuronbyhiddenlayer 0.5)
  val mutable hidd_out_weights_v = Array.make nbneuronbyhiddenlayer
                                (Array.make nboutputs 0.5) 
  val mutable out_errors = Array.make nboutputs 0.
  val mutable hidd_errors = Array.make nbneuronbyhiddenlayer 0.

  method get_patterns() = patterns
  method set_patterns p = patterns <- p
  method print_patterns() = 
    for i = 0 to Array.length (self#get_patterns()) - 1 do
      print_string "pattern n° ";
      print_int i;
      print_string " :\n";
      ((self#get_patterns()).(i))#print_inputs();
      ((self#get_patterns()).(i))#print_outputs();
      print_newline()
    done

  method get_current_pattern() = current_pattern
  method set_current_pattern cp = current_pattern <- cp

  method get_quad() = quad
  method set_quad q = quad <- q
  method print_quad() =
    print_string "erreur quadratique : "; 
    print_float quad;
    print_newline()

  method get_leaning_rate() = learning_rate
  method set_learning_rate lr = learning_rate <- lr
  method print_learning_rate() =
    print_string "valeur du coefficient d'apprentissage : ";
    print_float learning_rate;
    print_newline()

  method get_inputs() = inputs
  method get_input i = inputs.(i)
  method set_inputs inp = inputs <- inp
  method set_input i inp = inputs.(i) <- inp
  method print_inputs() =
    print_string "valeurs des neurones de la couche d'entrée :\n";
    for i = 0 to Array.length inputs - 1 do
      print_float inputs.(i);
      print_newline()
    done

  method get_hiddenlayer() = hiddenlayer
  method get_hiddenlayern i = hiddenlayer.(i)
  method set_hiddenlayer hidd = hiddenlayer <- hidd
  method set_hiddenlayern i hidd = hiddenlayer.(i) <- hidd
  method print_hiddenlayer() =
    print_string "valeurs des neurones de la couche cachée :\n";
    for i = 0 to Array.length hiddenlayer - 1 do
      print_float hiddenlayer.(i);
      print_newline()
    done

  method get_outputs() = outputs
  method get_output i = outputs.(i)
  method set_outputs out = outputs <- out
  method set_output i out = outputs.(i) <- out
  method print_outputs() =
    print_string "valeurs des neurones de la couche de sortie :\n";
    for i = 0 to Array.length outputs - 1 do
      print_float outputs.(i);
      print_newline()
    done

  method get_in_hidd_weights_v() = in_hidd_weights_v
  method get_in_hidd_weights i = in_hidd_weights_v.(i)
  method get_in_hidd_weight i j = (in_hidd_weights_v.(i)).(j)
  method set_in_hidd_weights_v i = in_hidd_weights_v <- i
  method set_in_hidd_weights i inhid = in_hidd_weights_v.(i) <- inhid
  method set_in_hidd_weight i j inhid = (in_hidd_weights_v.(i)).(j) <- inhid
  method print_in_hidd_weights_v() =
    for i = 0 to Array.length in_hidd_weights_v - 1 do
      print_string "Voici les poids du neurone ";
      print_int i;
      print_string " entre la couche d'entrée et la couche cachée :\n";
      for j = 0 to Array.length (in_hidd_weights_v.(i)) - 1 do
        print_float (in_hidd_weights_v.(i)).(j);
        print_newline()
      done
    done   

  method get_hidd_out_weights_v() = hidd_out_weights_v
  method get_hidd_out_weights i = hidd_out_weights_v.(i)
  method get_hidd_out_weight i j = (hidd_out_weights_v.(i)).(j)
  method set_hidd_out_weights_v i = hidd_out_weights_v <- i
  method set_hidd_out_weights i hidout = hidd_out_weights_v.(i) <- hidout
  method set_hidd_out_weight i j hidout = (hidd_out_weights_v.(i)).(j) <- hidout
  method print_hidd_out_weights_v() =
    for i = 0 to Array.length hidd_out_weights_v - 1 do
      print_string "Voici les poids du neurone ";
      print_int i;
      print_string " entre la couche cachée et la couche de sortie :\n";
      for j = 0 to Array.length (hidd_out_weights_v.(i)) - 1 do
        print_float (hidd_out_weights_v.(i)).(j);
        print_newline()
      done
    done 

  method get_out_errors() = out_errors
  method get_out_error i = out_errors.(i)
  method set_out_errors err = out_errors <- err
  method set_out_error i err = out_errors.(i) <- err
  method print_out_errors() =
    print_string "valeurs des erreurs de la couche de sortie :\n";
    for i = 0 to nboutputs - 1 do
      print_float out_errors.(i);
      print_newline()
    done

  method get_hidd_errors() = hidd_errors
  method get_hidd_error i = hidd_errors.(i)
  method set_hidd_errors err = hidd_errors <- err
  method set_hidd_error i err = hidd_errors.(i) <- err
  method print_hidd_errors() =
    print_string "valeurs des erreurs de la couche de sortie :\n";
    for i = 0 to nbneuronbyhiddenlayer - 1 do
      print_float hidd_errors.(i);
      print_newline()
    done 

  method pretty_print() =
    self#print_inputs();
    self#print_hiddenlayer();
    self#print_outputs();
    self#print_in_hidd_weights_v();
    self#print_hidd_out_weights_v()

  method activation x = 1./.(1. +. exp(-.x))

  method netsum1() = 
    for i = 0 to Array.length (self#get_hiddenlayer()) - 1 do
      let sum = ref 0. in
        for j = 0 to Array.length (self#get_inputs()) - 1 do
          sum := self#get_input j *. self#get_in_hidd_weight j i
        done;
        self#set_hiddenlayern i (self#activation (!sum +. 1.))
    done

  method netsum2() = 
    for i = 0 to Array.length (self#get_outputs()) - 1 do
      let sum = ref 0. in
        for j = 0 to Array.length (self#get_hiddenlayer()) - 1 do
          sum := self#get_hiddenlayern j *. self#get_hidd_out_weight j i
        done;
        self#set_output i (self#activation (!sum +. 1.))
    done  

  method forward() =
    self#netsum1();
    self#netsum2();

  method error_out() =
    for i = 0 to nboutputs - 1 do
      self#set_out_error i (((current_pattern#get_outputs()).(i) -.
                              self#get_output i ) *.
                              (self#get_output i) *.
                              (1. -. self#get_output i))
    done

  method weight_up_out() =
    for i = 0 to Array.length (self#get_hidd_out_weights_v()) - 1 do
      for j = 0 to Array.length (self#get_hidd_out_weights i) - 1 do
        self#set_hidd_out_weight i j (self#get_hidd_out_weight i j +.
                                     (learning_rate *. 
                                     self#get_out_error j *.
                                     self#get_hiddenlayern i))
      done
    done

  method error_hidd() =
    for i = 0 to nbneuronbyhiddenlayer - 1 do
      let error = ref 0. in
        for j = 0 to nboutputs - 1 do
          error := !error +. (self#get_out_error j) *. 
                   (self#get_hidd_out_weight i j )
        done;
        error := !error *. (self#get_hiddenlayern i) *.
                 (1. -. self#get_hiddenlayern i);
        self#set_hidd_error i (!error)
    done
    
  method weight_up_hidd() =
    for i = 0 to Array.length (self#get_in_hidd_weights_v()) - 1 do
      for j = 0 to Array.length (self#get_in_hidd_weights i) - 1 do
        self#set_in_hidd_weight i j (self#get_in_hidd_weight i j +.
                                     (learning_rate *. 
                                     self#get_hidd_error j *.
                                     (self#get_input i +. 1.(*biais*))))
      done 
    done

  method quaderror() =
    let sum = ref 0. in
      for i = 0 to nboutputs - 1 do
        sum := !sum +. (((current_pattern#get_outputs()).(i) -.
                              self#get_output i )) *. (((current_pattern#get_outputs()).(i) -.
                              self#get_output i ))
      done;
      quad <- 1./.2. *. !sum
      
  method permute_patterns() =
    Random.self_init();
    let compareThatShit x y =
      let xx = Random.int 10 in
      let yy = Random.int 10 in
        if xx = yy then 0
        else
          if xx > yy then 1
          else (-1)
    in
      Array.sort compareThatShit patterns

  method learn() =
    (*on load le jeu de données*)
    self#set_patterns data;
    (*while self#get_quad() > 0.005 do*)
    for iter = 1 to 10000 do
      self#quaderror();
      self#print_quad();
      (*on permute les données*)
      self#permute_patterns();
      (*on lance l'apprentissage de chaque pattern*)
      for i = 0 to Array.length patterns - 1 do
        current_pattern <- patterns.(i);
        (*on charge la pattern dans le reseau*)
        inputs <- current_pattern#get_inputs();
        (*et c'est parti mon kiki !*)
        self#forward();
        self#error_out();
        self#weight_up_out();
        self#error_hidd();
        self#weight_up_hidd();
      done
    done

end

  
