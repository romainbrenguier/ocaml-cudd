(*
 * Copyright 2014 Romain Brenguier
 * Author: Romain Brenguier <romain.brenguier@ulb.ac.be>
 * 
 * This file is part of Ocaml-cudd.
 * 
 * Ocaml-cudd is a free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *)
(*type ddManager = Cudd_stub.ddManager
type bdd = Cudd_stub.bdd*)
type t = Add_stub.t

(*let manager_ref = ref None 

let init size = match !manager_ref with
  | None -> manager_ref := Some (Cudd_stub.cudd_Init size)
  | Some _ -> 
     Printf.eprintf "warning: Cudd DdManager has already been initialized\n"

let manager () = match !manager_ref with 
  | Some x -> x 
  | None -> 
     Printf.eprintf "warning: Cudd DdManager has not been initialized.\n";
     Printf.eprintf "Use [Cudd.init size] to initialize it before using any cudd function.\n";
     init 100; match !manager_ref with Some x -> x
  

let quit () = 
  Cudd_stub.cudd_Quit (manager ()); 
  manager_ref := None
 *)
let manager () = Cudd.manager ()

let deref add = Add_stub.cudd_RecursiveDeref (manager()) add

let isConstant a = 
  Add_stub.cudd_IsConstant a 

let t a = Add_stub.cudd_T a
let e a = Add_stub.cudd_E a
let v a = Add_stub.cudd_V a

let const f = 
  let c = Add_stub.cudd_addConst (manager()) f in
  Gc.finalise deref c; c

let const_int f = 
  let c = Add_stub.cudd_addConst_int (manager()) f in
  Gc.finalise deref c; c

let ithVar i = 
  let c = Add_stub.cudd_addIthVar (manager()) i in
  Gc.finalise deref c; c

let plus a b =
  let c = Add_stub.cudd_addPlus (manager()) a b in
  Gc.finalise deref c; c

let minus a b =
  let c = Add_stub.cudd_addMinus (manager()) a b in
  Gc.finalise deref c; c

let times a b =
  let c = Add_stub.cudd_addTimes (manager()) a b in
  Gc.finalise deref c; c

let divide a b =
  let c = Add_stub.cudd_addDivide (manager()) a b in
  Gc.finalise deref c; c

let minimum a b =
  let c = Add_stub.cudd_addMinimum (manager()) a b in
  Gc.finalise deref c; c

let maximum a b =
  let c = Add_stub.cudd_addMaximum (manager()) a b in
  Gc.finalise deref c; c

let agreement a b =
  let c = Add_stub.cudd_addAgreement (manager()) a b in
  Gc.finalise deref c; c

let diff a b =
  let c = Add_stub.cudd_addDiff (manager()) a b in
  Gc.finalise deref c; c

let threshold a b =
  let c = Add_stub.cudd_addThreshold (manager()) a b in
  Gc.finalise deref c; c

let setNZ a b =
  let c = Add_stub.cudd_addSetNZ (manager()) a b in
  Gc.finalise deref c; c

let log a =
  let c = Add_stub.cudd_addLog (manager()) a in
  Gc.finalise deref c; c

let dumpDot f b =
  Add_stub.cudd_addDumpDot (manager()) f b 

type ring = PlusTimes | MinPlus | MaxPlus
let matrixMultiply a b z r =
  let i = match r with PlusTimes -> 1 | MinPlus -> 2 | MaxPlus -> 3 in
  Add_stub.cudd_addMatrixMultiply (manager()) a b z i
