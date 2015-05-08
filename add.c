/*
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
 */

#include "util.h"
#include "cudd.h"
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>

/*static struct custom_operations manager_ops = {
custom_finalize_default,
custom_compare_default,
custom_hash_default,
custom_serialize_default,
custom_deserialize_default
};
*/

/* Accessing the DdManager * part of an OCaml custom block */
#define Manager_val(v) (*((DdManager **) Data_custom_val(v)))

/* Allocating an OCaml custom block to hold the given WINDOW * */
/*static value alloc_manager(DdManager * d)
{
  value v = alloc_custom(&manager_ops, sizeof(DdManager *), 0, 1);
  Manager_val(v) = d;
  return v;
}
*/

static struct custom_operations node_ops = {
custom_finalize_default,
custom_compare_default,
custom_hash_default,
custom_serialize_default,
custom_deserialize_default
};

/* Accessing the DdNode * part of an OCaml custom block */
#define DdNode_val(v) (*((DdNode **) Data_custom_val(v)))
#define AddNode_val(v) (*((DdNode ***) Data_custom_val(v)))

/* Allocating an OCaml custom block to hold the given WINDOW * */
static value alloc_node(DdNode * d)
{
  value v = alloc_custom(&node_ops, sizeof(DdNode *), 0, 1);
  DdNode_val(v) = d;
  return v;
}

/*
value caml_Cudd_RecursiveDeref(value manager, value bdd)
{
  CAMLparam2(manager,bdd);
  Cudd_RecursiveDeref(Manager_val(manager),DdNode_val(bdd));
  CAMLreturn(Val_unit);
}

value caml_Cudd_IsConstant(value add)
{ 
  CAMLparam1(add);
  if(Cudd_IsConstant(DdNode_val(add)))
    CAMLreturn(Val_true);
  else
    CAMLreturn(Val_false);
}

value caml_Cudd_E(value add)
{
  CAMLparam1(add);
  CAMLreturn(alloc_node(Cudd_E(DdNode_val(add))));
}

value caml_Cudd_T(value add)
{
  CAMLparam1(add);
  CAMLreturn(alloc_node(Cudd_T(DdNode_val(add))));
}
*/
value caml_Cudd_V(value add)
{
  CAMLparam1(add);
  double d = Cudd_V(AddNode_val(add));
  CAMLreturn(caml_copy_double(d));
}

/*
value caml_Cudd_NodeReadIndex(value add)
{
  CAMLparam1(add);
  CAMLreturn(Val_int(Cudd_NodeReadIndex(*AddNode_val(add))));
}
*/
value caml_Cudd_addConst(value dd, value a)
{
  CAMLparam2(dd,a);
  DdNode * c = Cudd_addConst(Manager_val(dd),Double_val(a));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addPlus(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addPlus(Manager_val(dd),AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addMinus(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addMinus(Manager_val(dd),AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addTimes(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addTimes(Manager_val(dd),AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addDivide(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addDivide(Manager_val(dd),AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addMinimum(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addMinimum(Manager_val(dd),AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addMaximum(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addMaximum(Manager_val(dd),AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addAgreement(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addAgreement(Manager_val(dd),AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addDiff(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addDiff(Manager_val(dd),AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addThreshold(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addThreshold(Manager_val(dd),AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addSetNZ(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addSetNZ(Manager_val(dd),AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addLog(value dd, value f)
{
  CAMLparam2(dd,f);
  DdNode * c = Cudd_addLog(Manager_val(dd),*AddNode_val(f));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}


value caml_Cudd_addDumpDot(value manager, value file_name, value add)
{
  CAMLparam3(manager,file_name,add);
  FILE* f = fopen(String_val(file_name), "w");
  Cudd_DumpDot(Manager_val(manager), 1 , AddNode_val(add), NULL, NULL, f);
  fclose(f);
  CAMLreturn(Val_unit);
}
