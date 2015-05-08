(** Interface to ADD *)

(** type for ADDs *)
type t 

(** Cudd_IsConstant. Is the ADD constant ? *)
val isConstant : t -> bool

(** Cudd_NodeReadIndex. Returns the index of the ADD (65535 for a constant ADD)*)
(*val nodeReadIndex : t -> int*)

(** Cudd_T. Returns the positive subnode of the ADD *)
val t : t -> t
(** Cudd_E. Returns the negative subnode of the ADD *)
val e : t -> t
(** Cudd_V. Returns the value of the assumed constant ADD *)
val v : t -> float

(** Cudd_addPlus. *)
val plus : t -> t -> t

(** Cudd_addMinus. *)
val minus : t -> t -> t

(** Cudd_addTimes. *)
val times : t -> t -> t

(** Cudd_addDivide. *)
val divide : t -> t -> t

(** Cudd_addMinimum. *)
val minimum : t -> t -> t

(** Cudd_addMaximum. *)
val maximum : t -> t -> t

(** Cudd_addAgreement. *)
val agreement : t -> t -> t

(** Cudd_addDiff. *)
val diff : t -> t -> t

(** Cudd_addThreshold. *)
val threshold : t -> t -> t

(** Cudd_addSetNZ. *)
val setNZ : t -> t -> t

(** Cudd_addLog. *)
val log : t -> t

(** Cudd_addConst. Return a constant ADD with the given value. *)
val const : float -> t

val dumpDot : string -> t -> unit
