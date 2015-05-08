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

static struct custom_operations manager_ops = {
custom_finalize_default,
custom_compare_default,
custom_hash_default,
custom_serialize_default,
custom_deserialize_default
};

/* Accessing the DdManager * part of an OCaml custom block */
#define Manager_val(v) (*((DdManager **) Data_custom_val(v)))

/* Allocating an OCaml custom block to hold the given WINDOW * */
static value alloc_manager(DdManager * d)
{
  value v = alloc_custom(&manager_ops, sizeof(DdManager *), 0, 1);
  Manager_val(v) = d;
  return v;
}

static struct custom_operations node_ops = {
custom_finalize_default,
custom_compare_default,
custom_hash_default,
custom_serialize_default,
custom_deserialize_default
};

/* Accessing the DdNode * part of an OCaml custom block */
#define DdNode_val(v) (*((DdNode **) Data_custom_val(v)))

/* Allocating an OCaml custom block to hold the given WINDOW * */
static value alloc_node(DdNode * d)
{
  value v = alloc_custom(&node_ops, sizeof(DdNode *), 0, 1);
  DdNode_val(v) = d;
  return v;
}

value caml_Cudd_Init(value numVars)
{
  CAMLparam1(numVars);
  Cudd_ReorderingType REORDER_METHOD = CUDD_REORDER_SIFT;
  DdManager * manager = Cudd_Init(Int_val(numVars),0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);
  Cudd_AutodynEnable(manager, REORDER_METHOD);
  CAMLreturn (alloc_manager(manager));
}

value caml_Cudd_Quit(value manager)
{
  CAMLparam1(manager);
  Cudd_Quit(Manager_val(manager));
  CAMLreturn(Val_unit);
}


value caml_Cudd_RecursiveDeref(value manager, value bdd)
{
  CAMLparam2(manager,bdd);
  Cudd_RecursiveDeref(Manager_val(manager),DdNode_val(bdd));
  CAMLreturn(Val_unit);
}

value caml_Cudd_Not(value bdd)
{ 
  CAMLparam1(bdd);
  DdNode * res = Cudd_Not(DdNode_val(bdd));
  Cudd_Ref(res);
  CAMLreturn(alloc_node(res));
}

value caml_Cudd_ReadOne(value dd)
{
  CAMLparam1(dd);
  CAMLreturn(alloc_node(Cudd_ReadOne(Manager_val(dd))));
}


 
 value caml_Cudd_bddIthVar(value dd, value i)
 {
   CAMLparam2(dd,i);
   CAMLreturn(alloc_node(Cudd_bddIthVar(Manager_val(dd),Int_val(i))));
 }

 value caml_Cudd_IsComplement(value node)
 {
   CAMLparam1(node);
   if(Cudd_IsComplement(DdNode_val(node)))
     CAMLreturn(Val_true);
   else
     CAMLreturn(Val_false);
 }

 value caml_Cudd_IsConstant(value node)
 {
   CAMLparam1(node);
   if(Cudd_IsConstant(DdNode_val(node)))
     CAMLreturn(Val_true);
   else
     CAMLreturn(Val_false);
 }


 value caml_Cudd_bddExistAbstract(value manager, value f, value cube)
 {
   CAMLparam3(manager,f,cube);
   DdNode * c = Cudd_bddExistAbstract(Manager_val(manager),DdNode_val(f),DdNode_val(cube));
   Cudd_Ref(c);
   CAMLreturn(alloc_node(c));
 }

	    
 value caml_Cudd_bddUnivAbstract(value manager, value f, value cube)
 {
   CAMLparam3(manager,f,cube);
   DdNode * c = Cudd_bddUnivAbstract(Manager_val(manager),DdNode_val(f),DdNode_val(cube));
   Cudd_Ref(c);
   CAMLreturn(alloc_node(c));
 }

value caml_Cudd_bddAndAbstract(value manager, value f, value g, value cube)
 {
   CAMLparam4(manager,f,g,cube);
   DdNode * c = Cudd_bddAndAbstract(Manager_val(manager),DdNode_val(f),DdNode_val(g),DdNode_val(cube));
   Cudd_Ref(c);
   CAMLreturn(alloc_node(c));
 }

 value caml_Cudd_bddAnd(value dd, value f, value g)
 {
   CAMLparam3(dd,f,g);
   DdNode * c = Cudd_bddAnd(Manager_val(dd),DdNode_val(f),DdNode_val(g));
   Cudd_Ref(c);
   CAMLreturn(alloc_node(c));
 }

 value caml_Cudd_bddOr(value dd, value f, value g)
 {
   CAMLparam3(dd,f,g);
   DdNode * c = Cudd_bddOr(Manager_val(dd),DdNode_val(f),DdNode_val(g));
   Cudd_Ref(c);
   CAMLreturn(alloc_node(c));
 }

 value caml_Cudd_bddRestrict(value dd, value f, value g)
 {
   CAMLparam3(dd,f,g);
   DdNode * c = Cudd_bddRestrict(Manager_val(dd),DdNode_val(f),DdNode_val(g));
   Cudd_Ref(c);
   CAMLreturn(alloc_node(c));
 }

value caml_Cudd_DumpDot(value manager, value file_name, value bdd)
{
  CAMLparam3(manager,file_name,bdd);
  FILE* f = fopen(String_val(file_name), "w");
  Cudd_DumpDot(Manager_val(manager), 1 , &(DdNode_val(bdd)), NULL, NULL, f);
  fclose(f);
  CAMLreturn(Val_unit);
}

value caml_Cudd_DagSize(value bdd)
{
  CAMLparam1(bdd);
  CAMLreturn(Val_int(Cudd_DagSize(DdNode_val(bdd))));
}

 value caml_Cudd_SwapVariables(value dd,value bdd,value variables,value next_variables)
 {
   CAMLparam4(dd,bdd,variables,next_variables);
   DdNode ** variables_tab = (DdNode **) (malloc(sizeof(DdNode*)*Wosize_val(variables)));
   DdNode ** next_variables_tab = (DdNode **) (malloc(sizeof(DdNode*)*Wosize_val(next_variables)));
   int i;

   for(i = 0; i< Wosize_val(variables); i++)
     variables_tab[i] = Cudd_bddIthVar(Manager_val(dd),Int_val(Field(variables,i)));
   for(i = 0; i< Wosize_val(next_variables); i++)
     next_variables_tab[i] = Cudd_bddIthVar(Manager_val(dd),Int_val(Field(next_variables,i)));


   DdNode * renamed = Cudd_bddSwapVariables(Manager_val(dd),DdNode_val(bdd),variables_tab,next_variables_tab,Wosize_val(variables));
   Cudd_Ref(renamed);
   free(variables_tab);
   free(next_variables_tab);
   CAMLreturn(alloc_node(renamed));
 }

 value caml_Cudd_bddVectorCompose(value dd,value bdd,value vector)
{
  CAMLparam3(dd,bdd,vector);
   DdNode ** tab = (DdNode **) (malloc(sizeof(DdNode*)*Wosize_val(vector)));
   
   int i;

   for(i = 0; i< Wosize_val(vector); i++)
     tab[i] = DdNode_val(Field(vector,i));

   DdNode * substitued = Cudd_bddVectorCompose(Manager_val(dd),DdNode_val(bdd),tab);
   Cudd_Ref(substitued);
   free(tab);
   CAMLreturn(alloc_node(substitued));
}

value caml_cudd_equal(value bdda,value bddb)
{
  CAMLparam2(bdda,bddb);
  if( DdNode_val(bdda) == DdNode_val(bddb))
    CAMLreturn(Val_true);
  else 
    CAMLreturn(Val_false);
}

value caml_cudd_compare(value bdda,value bddb)
{
  CAMLparam2(bdda,bddb);
  if( DdNode_val(bdda) < DdNode_val(bddb))
    CAMLreturn(Val_int(-1));
  else 
  if( DdNode_val(bdda) > DdNode_val(bddb))
    CAMLreturn(Val_int(1));
  else
    CAMLreturn(Val_int(0));
}

value caml_Cudd_E(value bdd)
{
  CAMLparam1(bdd);
  CAMLreturn(alloc_node(Cudd_E(DdNode_val(bdd))));
}

value caml_Cudd_T(value bdd)
{
  CAMLparam1(bdd);
  CAMLreturn(alloc_node(Cudd_T(DdNode_val(bdd))));
}

value caml_Cudd_NodeReadIndex(value bdd)
{
  CAMLparam1(bdd);
  CAMLreturn(Val_int(Cudd_NodeReadIndex(DdNode_val(bdd))));
}


