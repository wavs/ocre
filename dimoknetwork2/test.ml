let main() =
  let pattern1 = new Pattern.pattern in
  let inputs = Array.make 2 3. in
    inputs.(0) <- 0.;
    inputs.(1) <- 0.;
    pattern1#set_inputs inputs;
    let outputs = Array.make 1 3. in
      outputs.(0) <- 0.;
      pattern1#set_outputs outputs;

 let pattern2 = new Pattern.pattern in
  let inputs = Array.make 2 3. in
    inputs.(0) <- 1.;
    inputs.(1) <- 0.;
    pattern2#set_inputs inputs;
    let outputs = Array.make 1 3. in
      outputs.(0) <- 1.;
      pattern2#set_outputs outputs;

 let pattern3 = new Pattern.pattern in
  let inputs = Array.make 2 3. in
    inputs.(0) <- 0.;
    inputs.(1) <- 1.;
    pattern3#set_inputs inputs;
    let outputs = Array.make 1 3. in
      outputs.(0) <- 1.;
      pattern3#set_outputs outputs;

 let pattern4 = new Pattern.pattern in
  let inputs = Array.make 2 3. in
    inputs.(0) <- 1.;
    inputs.(1) <- 1.;
    pattern4#set_inputs inputs;
    let outputs = Array.make 1 3. in
      outputs.(0) <- 0.;
      pattern4#set_outputs outputs;
      let data = [|pattern1;pattern2;pattern3;pattern4|] in

      let p = new Perceptron.perceptron 3 2 1 data in
        p#set_patterns data;
        (*p#pretty_print();
        p#learn();
        p#pretty_print()*)

        for i = 0 to Array.length data - 1 do
          data.(i)#print_inputs();
          data.(i)#print_outputs()
        done;
        p#permute_patterns();
        p#print_patterns()
        
let _ = main()
