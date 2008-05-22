let main() =
  let data = new Pattern.pattern in
  let inputs = Array.make 2 3. in
    inputs.(0) <- 0.;
    inputs.(1) <- 0.;
    data#set_inputs inputs;
    let outputs = Array.make 1 3. in
      outputs.(0) <- 0.;
      data#set_outputs outputs;
      let p = new Perceptron.perceptron 3 2 1 data in
        p#pretty_print();
        for i = 0 to 10000 do
          p#forward();
          p#error_out();
          p#weight_up_out();
          p#error_hidd();
          p#weight_up_hidd();
        done;
        p#pretty_print()

let _ = main()
