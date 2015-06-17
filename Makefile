CUDD_INCLUDE=cudd-2.5.0/cudd/libcudd.a cudd-2.5.0/util/libutil.a cudd-2.5.0/epd/libepd.a cudd-2.5.0/mtr/libmtr.a cudd-2.5.0/st/libst.a 

CUDD_I=cudd-2.5.0/include/

default: cudd.cmo cudd.o add.cmo add.o

clean:
	rm -f *.cmo *.cmi *.o *.cma *.cmx *.cmxa *.a


cudd_stub.cmi: cudd_stub.mli
	ocamlc -c cudd_stub.mli

cudd.cmi: cudd.mli cudd_stub.cmi
	ocamlc -c cudd.mli

add_stub.cmi: add_stub.mli
	ocamlc -c add_stub.mli

add.cmi: add.mli add_stub.cmi
	ocamlc -c add.mli

cudd.o: cudd.c 
	ocamlc -I $(CUDD_I) -c cudd.c

add.o: add.c 
	ocamlc -I $(CUDD_I) -c add.c

cudd.cmo: cudd.ml cudd.cmi
	ocamlc -c cudd.ml

add.cmo: add.ml add.cmi
	ocamlc -c add.ml

cudd.cmx: cudd.ml cudd_stub.cmi cudd.cmi
	ocamlopt -c cudd.ml

cudd.cma: cudd.cmx cudd.o cudd.cmo cudd_stub.cmi cudd.cmi
	ocamlmklib -custom -verbose -o cudd $(CUDD_INCLUDE) cudd.o cudd.cmo cudd.cmx cudd_stub.mli cudd.mli -L$(CUDD_I)

install:
	ocamlfind install ocaml-cudd META cudd.cm* *.mli *.a *.o

uninstall:
	ocamlfind remove ocaml-cudd


doc: doc/Cudd.html

doc/Cudd.html: *.mli
	mkdir doc ; ocamldoc -html cudd.mli add.mli -d doc

install_cudd:
	./install_cudd.sh

.phony: default clean install_cudd install uninstall

