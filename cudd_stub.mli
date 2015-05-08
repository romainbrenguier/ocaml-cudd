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
type ddManager
type bdd

external cudd_Init : int -> ddManager = "caml_Cudd_Init"

external cudd_Quit : ddManager -> unit = "caml_Cudd_Quit"

(** Dereference a node. All functions returning a Bdd reference it by default. *)
external cudd_RecursiveDeref : ddManager -> bdd -> unit = "caml_Cudd_RecursiveDeref"

external cudd_Not : bdd -> bdd = "caml_Cudd_Not"

external cudd_ReadOne : ddManager -> bdd = "caml_Cudd_ReadOne"

external cudd_bddIthVar : ddManager -> int -> bdd = "caml_Cudd_bddIthVar"

external cudd_IsConstant : bdd -> bool = "caml_Cudd_IsConstant"

external cudd_IsComplement : bdd -> bool = "caml_Cudd_IsComplement"

external cudd_bddExistAbstract : ddManager -> bdd -> bdd -> bdd = "caml_Cudd_bddExistAbstract"

external cudd_bddUnivAbstract : ddManager -> bdd -> bdd -> bdd = "caml_Cudd_bddUnivAbstract"

external cudd_bddAndAbstract : ddManager -> bdd -> bdd -> bdd -> bdd = "caml_Cudd_bddAndAbstract"

external cudd_bddAnd : ddManager -> bdd -> bdd -> bdd = "caml_Cudd_bddAnd"

external cudd_bddOr : ddManager -> bdd -> bdd -> bdd = "caml_Cudd_bddOr"
external cudd_DumpDot : ddManager -> string -> bdd -> unit = "caml_Cudd_DumpDot"
external cudd_DagSize : bdd -> int = "caml_Cudd_DagSize"

external cudd_SwapVariables : ddManager -> bdd -> int array -> int array -> bdd = "caml_Cudd_SwapVariables"


external cudd_bddVectorCompose : ddManager -> bdd -> bdd array -> bdd = "caml_Cudd_bddVectorCompose"

external cudd_bddRestrict : ddManager -> bdd -> bdd -> bdd = "caml_Cudd_bddRestrict"

external cudd_T : bdd -> bdd = "caml_Cudd_T"
external cudd_E : bdd -> bdd = "caml_Cudd_E"
external cudd_NodeReadIndex : bdd -> int = "caml_Cudd_NodeReadIndex"

(** Comparison functions. *)
external cudd_equal : bdd -> bdd -> int = "caml_cudd_equal"
external cudd_compare : bdd -> bdd -> int = "caml_cudd_compare"
