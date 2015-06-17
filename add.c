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
#include "cuddInt.h"
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/callback.h>

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
//#define AddNode_val(v) (*((DdNode ***) Data_custom_val(v)))
#define AddNode_val(v) (DdNode_val(v))

/* Allocating an OCaml custom block to hold the given WINDOW * */
static value alloc_node(DdNode * d)
{
  value v = alloc_custom(&node_ops, sizeof(DdNode *), 0, 1);
  DdNode_val(v) = d;
  return v;
}

/*
static value alloc_add_node(DdNode ** d)
{
  value v = alloc_custom(&node_ops, sizeof(DdNode **), 0, 1);
  AddNode_val(v) = d;
  return v;
  }*/


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
  DdNode *c = Cudd_addConst(Manager_val(dd),Double_val(a));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

 value caml_Cudd_addIthVar(value dd, value i)
 {
   CAMLparam2(dd,i);
   DdNode * r = Cudd_addIthVar(Manager_val(dd),Int_val(i));
   //Cudd_Ref(r);
   CAMLreturn(alloc_node(r));
 }


value caml_Cudd_addConst_int(value dd, value a)
{
  CAMLparam2(dd,a);
  DdNode * c = Cudd_addConst(Manager_val(dd),Int_val(a));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addPlus(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode *r = Cudd_addApply(Manager_val(dd),Cudd_addPlus,AddNode_val(f),AddNode_val(g));
  Cudd_Ref(r);
  CAMLreturn(alloc_node(r));
}


value caml_Cudd_addMinus(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addApply(Manager_val(dd),Cudd_addMinus,AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addTimes(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addApply(Manager_val(dd),Cudd_addTimes,AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addDivide(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addApply(Manager_val(dd),Cudd_addDivide,AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addMinimum(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addApply(Manager_val(dd),Cudd_addMinimum,AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addMaximum(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addApply(Manager_val(dd),Cudd_addMaximum,AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addAgreement(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addApply(Manager_val(dd),Cudd_addAgreement,AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addDiff(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addApply(Manager_val(dd),Cudd_addDiff,AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addThreshold(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addApply(Manager_val(dd),Cudd_addThreshold,AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addSetNZ(value dd, value f, value g)
{
  CAMLparam3(dd,f,g);
  DdNode * c = Cudd_addApply(Manager_val(dd),Cudd_addSetNZ,AddNode_val(f),AddNode_val(g));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}

value caml_Cudd_addLog(value dd, value f)
{
  CAMLparam2(dd,f);
  DdNode * c = Cudd_addLog(Manager_val(dd),DdNode_val(f));
  Cudd_Ref(c);
  CAMLreturn(alloc_node(c));
}


value caml_Cudd_addDumpDot(value manager, value file_name, value add)
{
  CAMLparam3(manager,file_name,add);
  FILE* f = fopen(String_val(file_name), "w");
  Cudd_DumpDot(Manager_val(manager), 1 , &(AddNode_val(add)) , NULL, NULL, f);
  fclose(f);
  CAMLreturn(Val_unit);
}


#include "cuddInt.h"

static DdNode *
addMMRecur(
  DdManager * dd,
  DdNode * A,
  DdNode * B,
  int  topP,
  int * vars,
  DdNode * sum (DdManager *, DdNode **, DdNode **),
  DdNode * product (DdManager *, DdNode **, DdNode **),
  DdNode * zero
	   )
{
    DdNode *At,		/* positive cofactor of first operand */
	   *Ae,		/* negative cofactor of first operand */
	   *Bt,		/* positive cofactor of second operand */
	   *Be,		/* negative cofactor of second operand */
	   *t,		/* positive cofactor of result */
	   *e,		/* negative cofactor of result */
	   *scaled,	/* scaled result */
	   *add_scale,	/* ADD representing the scaling factor */
	   *res;
    int	i;		/* loop index */
    double scale;	/* scaling factor */
    int index;		/* index of the top variable */
    CUDD_VALUE_TYPE value;
    unsigned int topA, topB, topV;
    DD_CTFP cacheOp;

    statLine(dd);
    // zero = DD_ZERO(dd);

    if (A == zero || B == zero) {
        return(zero);
    }

    if (cuddIsConstant(A) && cuddIsConstant(B)) {
	/* Compute the scaling factor. It is 2^k, where k is the
	** number of summation variables below the current variable.
	** Indeed, these constants represent blocks of 2^k identical
	** constant values in both A and B.
	*/
	value = cuddV(A) * cuddV(B);
	for (i = 0; i < dd->size; i++) {
	    if (vars[i]) {
		if (dd->perm[i] > topP) {
		    value *= (CUDD_VALUE_TYPE) 2;
		}
	    }
	}
	res = cuddUniqueConst(dd, value);
	return(res);
    }

    /* Standardize to increase cache efficiency. Clearly, A*B != B*A
    ** in matrix multiplication. However, which matrix is which is
    ** determined by the variables appearing in the ADDs and not by
    ** which one is passed as first argument.
    */
    if (A > B) {
	DdNode *tmp = A;
	A = B;
	B = tmp;
    }

    topA = cuddI(dd,A->index); topB = cuddI(dd,B->index);
    topV = ddMin(topA,topB);

    cacheOp = (DD_CTFP) addMMRecur;
    res = cuddCacheLookup2(dd,cacheOp,A,B);
    if (res != NULL) {
	/* If the result is 0, there is no need to normalize.
	** Otherwise we count the number of z variables between
	** the current depth and the top of the ADDs. These are
	** the missing variables that determine the size of the
	** constant blocks.
	*/
	if (res == zero) return(res);
	scale = 1.0;
	for (i = 0; i < dd->size; i++) {
	    if (vars[i]) {
		if (dd->perm[i] > topP && (unsigned) dd->perm[i] < topV) {
		    scale *= 2;
		}
	    }
	}
	if (scale > 1.0) {
	    cuddRef(res);
	    add_scale = cuddUniqueConst(dd,(CUDD_VALUE_TYPE)scale);
	    if (add_scale == NULL) {
		Cudd_RecursiveDeref(dd, res);
		return(NULL);
	    }
	    cuddRef(add_scale);
	    scaled = cuddAddApplyRecur(dd,product,res,add_scale);
	    if (scaled == NULL) {
		Cudd_RecursiveDeref(dd, add_scale);
		Cudd_RecursiveDeref(dd, res);
		return(NULL);
	    }
	    cuddRef(scaled);
	    Cudd_RecursiveDeref(dd, add_scale);
	    Cudd_RecursiveDeref(dd, res);
	    res = scaled;
	    cuddDeref(res);
	}
        return(res);
    }

    /* compute the cofactors */
    if (topV == topA) {
	At = cuddT(A);
	Ae = cuddE(A);
    } else {
	At = Ae = A;
    }
    if (topV == topB) {
	Bt = cuddT(B);
	Be = cuddE(B);
    } else {
	Bt = Be = B;
    }

    t = addMMRecur(dd, At, Bt, (int)topV, vars,sum,product,zero);
    if (t == NULL) return(NULL);
    cuddRef(t);
    e = addMMRecur(dd, Ae, Be, (int)topV, vars,sum,product,zero);
    if (e == NULL) {
	Cudd_RecursiveDeref(dd, t);
	return(NULL);
    }
    cuddRef(e);

    index = dd->invperm[topV];
    if (vars[index] == 0) {
	/* We have split on either the rows of A or the columns
	** of B. We just need to connect the two subresults,
	** which correspond to two submatrices of the result.
	*/
	res = (t == e) ? t : cuddUniqueInter(dd,index,t,e);
	if (res == NULL) {
	    Cudd_RecursiveDeref(dd, t);
	    Cudd_RecursiveDeref(dd, e);
	    return(NULL);
	}
	cuddRef(res);
	cuddDeref(t);
	cuddDeref(e);
    } else {
	/* we have simultaneously split on the columns of A and
	** the rows of B. The two subresults must be added.
	*/
	res = cuddAddApplyRecur(dd,sum,t,e);
	if (res == NULL) {
	    Cudd_RecursiveDeref(dd, t);
	    Cudd_RecursiveDeref(dd, e);
	    return(NULL);
	}
	cuddRef(res);
	Cudd_RecursiveDeref(dd, t);
	Cudd_RecursiveDeref(dd, e);
    }

    cuddCacheInsert2(dd,cacheOp,A,B,res);

    /* We have computed (and stored in the computed table) a minimal
    ** result; that is, a result that assumes no summation variables
    ** between the current depth of the recursion and its top
    ** variable. We now take into account the z variables by properly
    ** scaling the result.
    */
    if (res != zero) {
	scale = 1.0;
	for (i = 0; i < dd->size; i++) {
	    if (vars[i]) {
		if (dd->perm[i] > topP && (unsigned) dd->perm[i] < topV) {
		    scale *= 2;
		}
	    }
	}
	if (scale > 1.0) {
	    add_scale = cuddUniqueConst(dd,(CUDD_VALUE_TYPE)scale);
	    if (add_scale == NULL) {
		Cudd_RecursiveDeref(dd, res);
		return(NULL);
	    }
	    cuddRef(add_scale);
	    scaled = cuddAddApplyRecur(dd,product,res,add_scale);
	    if (scaled == NULL) {
		Cudd_RecursiveDeref(dd, res);
		Cudd_RecursiveDeref(dd, add_scale);
		return(NULL);
	    }
	    cuddRef(scaled);
	    Cudd_RecursiveDeref(dd, add_scale);
	    Cudd_RecursiveDeref(dd, res);
	    res = scaled;
	}
    }
    cuddDeref(res);
    return(res);

} /* end of addMMRecur */


DdNode *
addMatrixMultiply(
  DdManager * dd,
  DdNode * A,
  DdNode * B,
  DdNode ** z,
  int  nz,
  DdNode * sum (DdManager *, DdNode **, DdNode **),
  DdNode * product (DdManager *, DdNode **, DdNode **),
  DdNode * zero)
{
    int i, nvars, *vars;
    DdNode *res; 

    /* Array vars says what variables are "summation" variables. */
    nvars = dd->size;
    vars = ALLOC(int,nvars);
    if (vars == NULL) {
	dd->errorCode = CUDD_MEMORY_OUT;
	return(NULL);
    }
    for (i = 0; i < nvars; i++) {
        vars[i] = 0;
    }
    for (i = 0; i < nz; i++) {
        vars[z[i]->index] = 1;
    }

    do {
	dd->reordered = 0;
	res = addMMRecur(dd,A,B,-1,vars,sum,product,zero);
    } while (dd->reordered == 1);
    FREE(vars);
    return(res);

} 




value caml_Cudd_addMatrixMultiply(value dd,value a,value b,value vector,value r)
{
  CAMLparam5(dd,a,b,vector,r);
  DdNode ** tab = (DdNode **) (malloc(sizeof(DdNode*)*Wosize_val(vector)));
   
  int i;

  for(i = 0; i< Wosize_val(vector); i++)
    {
      tab[i] = DdNode_val(Field(vector,i));
      //Cudd_Ref(tab[i]);
    }

  /*  
  DdNode * (*c_sum)(DdManager*,DdNode**,DdNode**);
  DdNode * (*c_product)(DdManager*,DdNode**,DdNode**);  

    DdNode * zero;
  int ring = Int_val(r);

  assert(ring >= 0 && ring <= 2);
  if(ring == 1) {
    printf("add_plus\n");
    c_sum = Cudd_addPlus;
    c_product = Cudd_addTimes;
    zero = DD_ZERO(Manager_val(dd));
  }
  else if(ring == 2) {
    c_sum = Cudd_addMinimum;
    c_product = Cudd_addPlus;
    zero = DD_ZERO(Manager_val(dd));
  } 

  DdNode * result = addMatrixMultiply(Manager_val(dd),DdNode_val(a),DdNode_val(b),tab,i,c_sum,c_product,zero);
  Cudd_Ref(result);
  */
  DdNode * result = Cudd_addMatrixMultiply(Manager_val(dd),DdNode_val(a),DdNode_val(b),tab,i);
  Cudd_Ref(result);

  free(tab);
  CAMLreturn(alloc_node(result));
}
