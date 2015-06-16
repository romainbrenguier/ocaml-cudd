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
type t

external cudd_RecursiveDeref : Cudd_stub.ddManager -> t -> unit = "caml_Cudd_IsConstant"

external cudd_IsConstant : t -> bool = "caml_Cudd_IsConstant"

external cudd_E : t -> t = "caml_Cudd_E"

external cudd_T : t -> t = "caml_Cudd_T"

external cudd_V : t -> float = "caml_Cudd_V"

external cudd_NodeReadIndex : t -> int = "caml_Cudd_NodeReadIndex"

external cudd_addConst : Cudd_stub.ddManager -> float -> t = "caml_Cudd_addConst"

external cudd_addConst_int : Cudd_stub.ddManager -> int -> t = "caml_Cudd_addConst_int"

external cudd_addIthVar : Cudd_stub.ddManager -> int -> t = "caml_Cudd_addIthVar"

external cudd_addPlus : Cudd_stub.ddManager -> t -> t -> t = "caml_Cudd_addPlus"

external cudd_addMinus : Cudd_stub.ddManager -> t -> t -> t = "caml_Cudd_addMinus"

external cudd_addTimes : Cudd_stub.ddManager -> t -> t -> t = "caml_Cudd_addTimes"

external cudd_addDivide : Cudd_stub.ddManager -> t -> t -> t = "caml_Cudd_addDivide"

external cudd_addMinimum : Cudd_stub.ddManager -> t -> t -> t = "caml_Cudd_addMinimum"

external cudd_addMaximum : Cudd_stub.ddManager -> t -> t -> t = "caml_Cudd_addMaximum"

external cudd_addAgreement : Cudd_stub.ddManager -> t -> t -> t = "caml_Cudd_addAgreement"

external cudd_addDiff : Cudd_stub.ddManager -> t -> t -> t = "caml_Cudd_addDiff"

external cudd_addThreshold : Cudd_stub.ddManager -> t -> t -> t = "caml_Cudd_addThreshold"

external cudd_addSetNZ : Cudd_stub.ddManager -> t -> t -> t = "caml_Cudd_addSetNZ"

external cudd_addLog : Cudd_stub.ddManager -> t -> t = "caml_Cudd_addLog"

external cudd_addDumpDot : Cudd_stub.ddManager -> string -> t -> unit = "caml_Cudd_addDumpDot"

external cudd_addMatrixMultiply : Cudd_stub.ddManager -> t -> t -> t array -> int -> t = "caml_Cudd_addMatrixMultiply"
