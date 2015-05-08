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


(** An Ocaml interface to the CUDD BDD library. *)


(** Abstract type for BDDs. 
BDDs are automatically referenced at creation and dereferenced with garbage collection.
*)
type bdd

(** Initialization of CUDD. 
Should be called with the number of variables you plan to use. 
Reordering is automatically activated.
 *)
val init : int -> unit
val quit : unit -> unit
val manager : unit -> Cudd_stub.ddManager

val ithVar : int -> bdd
val bddTrue : unit -> bdd 
val bddFalse : unit -> bdd
val bddNot : bdd -> bdd
val bddAnd : bdd -> bdd -> bdd
val bddOr : bdd -> bdd -> bdd

type cube
val make_cube : int list -> cube
val bddExistAbstract : bdd -> cube -> bdd
val bddUnivAbstract : bdd -> cube -> bdd
val bddAndAbstract : bdd -> bdd -> cube -> bdd

val bddSwapVariables : bdd -> int array -> int array -> bdd

(** Warning: this function will cause a core dump if the biggest index of the array is not as big as the biggest variable in the bdd *) 
val bddVectorCompose : bdd -> bdd array -> bdd

val dumpDot : string -> bdd -> unit

val bddRestrict : bdd -> bdd -> bdd

(** return 1 if the bdd is the constant true, 0 for the constant false, and -1 if it is not constant *)
val value : bdd -> int

(** tells if two BDD are the same *)
val equal : bdd -> bdd -> bool

val compare : bdd -> bdd -> int

(** then child of a node *)
val t : bdd -> bdd
(** else child of a node *)
val e : bdd -> bdd


val nodeReadIndex : bdd -> int
val isComplement : bdd -> bool
val isConstant : bdd -> bool

val dagSize : bdd -> int
