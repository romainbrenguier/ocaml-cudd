(* 
compile with the following command:
ocamlc -custom cudd.o cudd.cmo add.o add.cmo -I cudd-2.5.0/include/ cudd-2.5.0/cudd/libcudd.a cudd-2.5.0/util/libutil.a cudd-2.5.0/epd/libepd.a cudd-2.5.0/mtr/libmtr.a cudd-2.5.0/st/libst.a test.ml -o test *)

let main =
  Cudd.init 10;
  let a = Add.const 10. in
  let b = Add.const 7. in
  let c = Add.divide a b in
  print_endline "c";
  print_endline "writing test.dot";
  Add.dumpDot "test.dot" c
