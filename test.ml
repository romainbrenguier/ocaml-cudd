(*  compile with the following command:
ocamlc -custom cudd.o cudd.cmo add.o add.cmo -I cudd-2.5.0/include/ cudd-2.5.0/cudd/libcudd.a cudd-2.5.0/util/libutil.a cudd-2.5.0/epd/libepd.a cudd-2.5.0/mtr/libmtr.a cudd-2.5.0/st/libst.a test.ml -o test *)

open Add

let main =
  Cudd.init 10;
  let a = times (const 2.) (ithVar 0) in
  let b = times (const 2.) (ithVar 1) in
  dumpDot "test_b.dot" b;
  let ring = {sum=Minimum;product=Plus;zero=0.} in
  let c = matrixMultiply a b [| ithVar 0 |] ring in
  print_endline "writing test.dot";
  dumpDot "test.dot" (plus c a)

