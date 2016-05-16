CUDD_INCLUDE=cudd-2.5.0/cudd/libcudd.a cudd-2.5.0/util/libutil.a cudd-2.5.0/epd/libepd.a cudd-2.5.0/mtr/libmtr.a cudd-2.5.0/st/libst.a 

CUDD_I=cudd-2.5.0/include/

default:  cudd.cmo cudd.cmxa cudd.o 

clean:
	rm -f *.cmo *.cmi *.o *.cma *.cmx *.cmxa *.a
	ocamlbuild -clean

cudd.o: cudd.c 
	ocamlc -I $(CUDD_I) -c cudd.c
	mv cudd.o _build/

cudd.cmo: cudd.ml 
	ocamlbuild cudd.cmo

cudd.cmxa: cudd.ml
	ocamlbuild cudd.cmxa

cudd.cma: cudd.cmx cudd.o cudd.cmo cudd_stub.cmi cudd.cmi
	ocamlmklib -custom -verbose -o cudd $(CUDD_INCLUDE) cudd.o cudd.cmo cudd.cmx cudd_stub.mli cudd.mli -L$(CUDD_I)

install: cudd_stub.cmi cudd.cmi cudd.o cudd.cmo cudd.cma cudd.cmxa
	ocamlfind install ocaml-cudd META cudd.cm* *.mli *.a *.o

uninstall:
	ocamlfind remove ocaml-cudd

doc: doc/Cudd.html

doc/Cudd.html: *.mli
	mkdir doc ; ocamldoc -html cudd.mli add.mli -d doc

install_cudd:
	./install_cudd.sh

.phony: default clean install_cudd install uninstall

