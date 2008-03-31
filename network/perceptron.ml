
class perceptron =
object (self)
  val mutable bias = 1.
  method get_bias() = bias
  method set_bias bias0 = bias <- bias0

  val mutable treshold = 300
    (*seuil d'apprentissage*)
  method get_treshold() = treshold
  method set_treshold treshold0 = treshold <- treshold0
  method treshold_print() =
    print_int(treshold);
    print_newline()

  val mutable eta = 0.1
    (*avec 0 <= eta <= 1 le coef d'apprentissage*)
  method get_eta() = eta
  method set_eta eta0 = eta <- eta0
  method eta_print() =
    print_float(eta);
    print_newline()

  val mutable nb_layers = 3 
    (*num de la couche de sortie - à partir de 1*)
  method get_nb_layers() = nb_layers
  method set_nb_layers nb_layers0 = nb_layers <- nb_layers0
  method nb_layers_print() =
    print_int(nb_layers);
    print_newline()

val mutable nb_n_by_l = 8 
  (*nb neurones par couche cachée*)
  method get_nb_n_by_l() = nb_n_by_l
  method set_nb_n_by_l nb_n_by_l0 = nb_n_by_l <- nb_n_by_l0
  method nb_n_by_l_print() =
    print_int(nb_n_by_l);
    print_newline()

  val mutable learning_data = Array.make 0 (new Data.data 0 0)
  method get_learning_data() = learning_data
  method set_learning_data learning_data0 = learning_data <- learning_data0
  method permute_data() =
    Random.self_init();
    let compareThatShit x y =
      let xx = Random.int 10 in
      let yy = Random.int 10 in
        if xx = yy then 0
        else
          if xx > yy then 1
          else (-1)
    in
      Array.sort compareThatShit learning_data
  method learning_data_print() =
    for i = 0 to Array.length learning_data - 1 do
      print_string ("Donnee n° "^string_of_int(i)^" :\n");
      learning_data.(i)#inputs_print();
      learning_data.(i)#outputs_print()
    done;

  val mutable connections = Array.make 42 (new Connection.connection)
  method get_connections() = connections
  method set_connections connections0 = connections <- connections0
  method set_connection1 i connection0 = connections.(i) <- connection0
  method set_connection a b w = 
    for i = 0 to Array.length connections - 1 do
      let connection = connections.(i) in
        if ((connection#get_v1() = a) && (connection#get_v2() = b)) ||
          ((connection#get_v2() = a) && (connection#get_v1() = b)) then
            connection#set_weight w
    done
  method connections_print() = 
    print_newline();
    for i = 0 to Array.length connections - 1 do
      connections.(i)#connection_print()
    done;
    print_newline()
      
  val mutable neurons = Array.make 23 (new Neuron.neuron)
  val mutable nb_neurons = 42
  method get_nb_neurons() = nb_neurons
  method set_nb_neurons nb_neurons0 = nb_neurons <- nb_neurons0
  method calc_nb_neurons() =
    let result = ref 0 in 
      result := Array.length (learning_data.(0)#get_inputs()) 
              + Array.length (learning_data.(0)#get_outputs())
              + (nb_layers - 2) * nb_n_by_l ;
      !result
  method nb_neurons_print() =
    print_int nb_neurons;
    print_newline()
  method get_neurons() = neurons
  method set_neurons neurons0 = neurons <- neurons0
  method set_neuron i neuron0 = neurons.(i) <- neuron0
  method find_neuron id = 
    let i = ref (Array.length neurons - 1) in
    while (!i >= 0) && ((neurons.(!i))#get_id() <> id) do
      i := !i - 1;
    done;
    neurons.(!i)
  method neurons_print() = 
    print_newline();
    for i = 0 to Array.length neurons - 1 do
      neurons.(i)#neuron_print()
    done;
    print_newline()

  method activation() = 
    for i = 0 to Array.length neurons - 1 do
      let weight_sum = ref 0. in
      let neuron = neurons.(i) in
        for j = 0 to Array.length neurons - 1 do
          let neuron2 = neurons.(j) in
              if neuron2#get_layer() = neuron#get_layer() - 1 then
                begin
                  for k = 0 to Array.length connections - 1 do
                    let connection = connections.(k) in
                      if ((connection#get_v1() = neuron#get_id())
                       && (connection#get_v2() = neuron2#get_id()))
                      || ((connection#get_v2() = neuron#get_id())
                       && (connection#get_v1() = neuron2#get_id())) then
                          weight_sum := !weight_sum
                                     +. (neuron#get_observed_output()
                                     +. bias) (*checker que le biais
    est la*)
                                     *. connection#get_weight()
                  done
                end
        done;
        neuron#set_weight_sum !weight_sum;
        neuron#activate()
    done

  val mutable error_sum = 007.
  method get_error_sum() = error_sum
  method set_error_sum error_sum0 = error_sum <- error_sum0
  method calc_error_sum = 
    let sum = ref 0. in
      for i = 0 to Array.length neurons - 1 do
        let neuron = neurons.(i) in
          if neuron#get_layer() = nb_layers then
            begin
              neuron#calc_error2()
            end
      done;
      error_sum <- !sum;
      for i = 0 to Array.length neurons - 1 do
        let neuron1 = neurons.(i) in
        let sum2 = ref 0. in
          if (neuron1#get_layer() > 1)
            && (neuron1#get_layer() < nb_layers) then
              begin
                for j = 0 to Array.length neurons - 1 do
                    let neuron2 = neurons.(j) in
                      if neuron2#get_layer() = nb_layers then
                        begin
                          for k = 0 to Array.length connections - 1 do
                            let connection = connections.(k) in
                              if ((connection#get_v1() = neuron1#get_id())
                                  && (connection#get_v2() = neuron2#get_id()))
                                || ((connection#get_v2() = neuron1#get_id())
                                    && (connection#get_v1() = neuron2#get_id())) then
                                  sum2 := !sum2 +. neuron2#get_error()
                                  *. connection#get_weight()
                          done
                        end
                  done
              end;
          error_sum <- error_sum +. !sum2
      done
  method error_sum_print() = 
    print_float(error_sum);
    print_newline() 

  val mutable v_obs_out = Array.make 3 0.
  method get_obs_out() = v_obs_out
  method set_v_obs_out v_obs_out0 = v_obs_out <- v_obs_out0
  method set_v_obs_out2() = v_obs_out <- Array.make (Array.length ((learning_data.(0))#get_outputs())) 0.
  method set_obs_out i x = v_obs_out.(i) <- x
  method update_v_obs_out() =
    self#set_v_obs_out2();
    let z = ref 0 in
      for i = 0 to Array.length neurons - 1 do
        let neuron = neurons.(i) in
          if neuron#get_layer() = nb_layers then
            begin
              v_obs_out.(!z) <- (neuron#get_observed_output());
              z := !z + 1
            end
      done
  method obs_out_print i = 
    print_float(v_obs_out.(i));
    print_newline()
  method v_obs_out_print() =
    print_newline();
    for i = 0 to Array.length v_obs_out - 1 do
      self#obs_out_print i
    done;

  method init_weights() =
    Random.init 7;
    for i = 0 to Array.length connections - 1 do
      let connection = connections.(i) in
      let alea = Random.float 1. in
        if alea > 0.5 then
          connection#set_weight (Random.float 0.5)
        else
          connection#set_weight (Random.float (-. 0.5))
    done

  method nb_connections() =
    let res1 = ref 0 in
    let data = learning_data.(0) in
    let indatalen = Array.length (data#get_inputs()) in
    let outdatalen = Array.length (data#get_outputs()) in
      res1 := indatalen * nb_n_by_l + nb_n_by_l * outdatalen;
      if nb_layers >= 3 then
        res1 := !res1 + (nb_n_by_l * nb_n_by_l) * (nb_layers - 3);
      !res1

  method init_connections() =
   self#set_connections (Array.make (self#nb_connections()) (new Connection.connection));
    let k = ref 0 in
      while !k < self#nb_connections() do
        for i = 0 to Array.length neurons - 1 do
          for j = 0 to Array.length neurons - 1 do
            if neurons.(j)#get_layer() = neurons.(i)#get_layer() + 1 then
              begin
                let c = new Connection.connection in
                  c#set_v1 (neurons.(i)#get_id());
                  c#set_v2 (neurons.(j)#get_id());
                  self#set_connection1 (!k) c;
                  k := !k + 1
              end
          done
        done
      done;
    (*init des poids des connexions*)
    self#init_weights();
    
  val mutable delta_sum = 69.
  method get_delta_sum() = delta_sum
  method set_delta_sum delta_sum0 = delta_sum <- delta_sum0
  method calc_delta_sum connection = 
    let sum = ref 0. in
      for i = 0 to Array.length connections - 1 do
        let connection0 = connections.(i) in
          if connection0#get_v2() = connection#get_v1() then
            begin
              self#calc_delta connection0;
              sum := !sum +. self#get_delta() 
              *. connection0#get_weight()
            end
      done;
      !sum

  val mutable delta = 2.
  method get_delta() = delta
  method set_delta delta0 = delta <- delta0
  method calc_delta connection =
    let neuron = self#find_neuron (connection#get_v2()) in
    let output_pred = ((self#find_neuron (connection#get_v1()))#get_observed_output()) in
      if neuron#get_layer() = nb_layers then
        begin
          delta <- neuron#get_error() 
          *. output_pred 
          *. (1. -. output_pred)
        end
      else
        begin
          delta <- output_pred 
          *. (1. -. output_pred) 
          *. (self#calc_delta_sum connection)
        end

  method adjust_weights() = 
    (*ajuster les poids en rétropropageant l'erreur ainsi:*)
    for i = Array.length connections - 1 downto 0 do
      let connection = connections.(i) in
        self#calc_delta connection;
        connection#set_weight (connection#get_weight()
       +. eta *. delta 
       *. ((self#find_neuron (connection#get_v1()))#get_observed_output()))    
    done

  method init_neurons() = 
    (*maj du nb de neurones*)
    self#set_nb_neurons (self#calc_nb_neurons());
    (*init du vect de neurones*)
    self#set_neurons (Array.make (self#get_nb_neurons()) (new Neuron.neuron));
    (*init des id*)
    let nb_input = Array.length ((learning_data.(0))#get_inputs()) in
    let nb_output = Array.length ((learning_data.(0))#get_outputs()) in
    let layer_cpt = ref nb_input in
      
      (*init des indicateurs de la couche d'entree*)
      for i = 0 to nb_input - 1 do
          let a = new Neuron.neuron in
            a#set_id i;
            a#set_layer 1;
            self#set_neuron i a;
        done; 
        (*init des indicateurs des couches cachees*)
        for i = 2 to nb_layers - 1 do
          for j = !layer_cpt to !layer_cpt + nb_n_by_l - 1 do
            let a = new Neuron.neuron in
              a#set_id j;
              a#set_layer i;
              self#set_neuron j a; neurons.(j)#set_layer i
          done;
          layer_cpt := !layer_cpt + nb_n_by_l          
        done;
        (*init des indicateurs de la couche de sortie*)
        for i = Array.length neurons - nb_output to Array.length neurons - 1 do
          let a = new Neuron.neuron in
            a#set_id i;
            a#set_layer nb_layers;
            self#set_neuron i a
        done
          
  method init() =
    (*init des donnees*)
    let td = new Data.tabdata in
      td#set_tab (td#get_tab2());
      self#set_learning_data (td#get_tab());
      (*init des neurones*)
      self#init_neurons();
      (*init des connexions*)
      self#init_connections();
      (*init des sorties*)
      self#update_v_obs_out()
        
  method run data (*input_data*) =
    for i = 0 to Array.length (learning_data.(0)#get_outputs()) - 1 do
      for j = 0 to Array.length (learning_data.(0)#get_inputs()) - 1 do
        neurons.(i)#set_observed_output
          (((learning_data.(data))#get_inputs()).(j))
      done
    done;
    self#activation();
    self#update_v_obs_out()

  method train() =
    (*while sqrt(error_sum) < treshold do*)                   
    for l = 0 to treshold do
      self#calc_error_sum;
      print_string "erreur : ";
      print_float (self#get_error_sum());
      print_newline();
    (*3 Permuter aléatoirement les données d'entrainement*)
    self#permute_data();
      for i = 0 to Array.length learning_data - 1 do
        (*initialiser les valeurs des neurones d'entrée et de sortie*)
        for j = 0 to  Array.length (learning_data.(0)#get_inputs()) - 1
        do
          neurons.(j)#set_observed_output (((learning_data.(i))#get_inputs()).(j))
        done;
        
        let nb_output = Array.length (learning_data.(0)#get_outputs())
        in
        let k = ref 0 in
          for j = Array.length neurons - nb_output to Array.length neurons - 1
          do
            neurons.(j)#set_wanted_output
              (((learning_data.(i))#get_outputs()).(!k));
            k := !k + 1
          done;
          (*calculer les sorties observées*)
          self#activation();        
          (*ajuster les poids*)
          self#adjust_weights()
      done
    done;
    print_string "done";
    self#update_v_obs_out()
      
  method save() = print_int(42)
  method load() = print_int(69)
end
