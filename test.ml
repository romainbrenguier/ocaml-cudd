(* 
compile with the following command:
ocamlc -custom cudd.o cudd.cmo add.o add.cmo -I cudd-2.5.0/include/ cudd-2.5.0/cudd/libcudd.a cudd-2.5.0/util/libutil.a cudd-2.5.0/epd/libepd.a cudd-2.5.0/mtr/libmtr.a cudd-2.5.0/st/libst.a test.ml -o test *)

let main =
  Cudd.init 10;
  let a = Add.times (Add.const 2.) (Add.ithVar 0) in
  let b = Add.times (Add.const 2.) (Add.ithVar 1) in
  Add.dumpDot "test_b.dot" b;
  let c = Add.matrixMultiply a b [| Add.ithVar 0 |] Add.PlusTimes
			     (* Add.plus a b*)
  in
  print_endline "writing test.dot";
  Add.dumpDot "test.dot" (Add.plus c a)
	      (* Printf.printf "c : %f\n" (Add.v c) *)
