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
type manager = Cudd_stub.ddManager
type bdd = Cudd_stub.bdd


let manager_ref = ref None 

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


let deref bdd = Cudd_stub.cudd_RecursiveDeref (manager()) bdd

let bddTrue () = Cudd_stub.cudd_ReadOne (manager())
let bddFalse () = Cudd_stub.cudd_Not (bddTrue ())

let ithVar i = Cudd_stub.cudd_bddIthVar (manager()) i

let bddNot x = 
  let b = Cudd_stub.cudd_Not x in
  Gc.finalise deref b; b

let bddAnd a b = 
  let c = Cudd_stub.cudd_bddAnd (manager()) a b in
  Gc.finalise deref c; c

let bddOr a b = 
  let c = Cudd_stub.cudd_bddOr (manager()) a b in
  Gc.finalise deref c; c

type cube = bdd

let isComplement n = Cudd_stub.cudd_IsComplement n
let isConstant n = Cudd_stub.cudd_IsConstant n

let bddExistAbstract f c = 
  if isConstant f then f 
  else
    let b = Cudd_stub.cudd_bddExistAbstract (manager()) f c in
    Gc.finalise deref b; b

let bddUnivAbstract f c =
  (* there seem to be problems when the BDD is trivial *)
  if isConstant f then f 
  else
    let b = Cudd_stub.cudd_bddUnivAbstract (manager()) f c in
    Gc.finalise deref b; b

let bddAndAbstract f g c =
  let b = Cudd_stub.cudd_bddAndAbstract (manager()) f g c in
  Gc.finalise deref b; b


let value x = 
  if Cudd_stub.cudd_IsConstant x
  then if isComplement x then 0 else 1
  else -1 

let bddRestrict f c =  Cudd_stub.cudd_bddRestrict (manager()) f c

let make_cube l = 
  List.fold_left (fun a b -> bddAnd a (ithVar b)) (bddTrue ()) l

let bddSwapVariables bdd var nvar =
  Cudd_stub.cudd_SwapVariables (manager()) bdd var nvar

let equal b c = 
  Cudd_stub.cudd_equal b c = 1

let dumpDot f b = Cudd_stub.cudd_DumpDot (manager()) f b

let bddVectorCompose f a = Cudd_stub.cudd_bddVectorCompose (manager()) f a

let t a = Cudd_stub.cudd_T a
let e a = Cudd_stub.cudd_E a
let nodeReadIndex n = Cudd_stub.cudd_NodeReadIndex n

let compare b c = Cudd_stub.cudd_compare b c

let dagSize bdd = Cudd_stub.cudd_DagSize bdd
