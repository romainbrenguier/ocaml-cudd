# ocaml-cudd
An Ocaml interface to BDD functions of the CUDD library


## Installation
To install this library, you need Ocaml and ocamlbuild. 
On debian/ubuntu simply run `sudo apt-get install ocamlbuild`.
To install the library first run the `install_cudd.sh` script, then `make`.

## API Documentation
The documentation for the library is available in the `doc` directory or at the adress:
http://htmlpreview.github.io/?https://github.com/romainbrenguier/ocaml-cudd/blob/master/doc/index.html

## Using the library
To compile with ocaml-cudd assuming myprog.ml is in the ocaml-cudd directory:
ocamlc -custom cudd.o cudd.cmo add.o add.cmo -I cudd-2.5.0/include/ cudd-2.5.0/cudd/libcudd.a cudd-2.5.0/util/libutil.a cudd-2.5.0/epd/libepd.a cudd-2.5.0/mtr/libmtr.a cudd-2.5.0/st/libst.a myprog.ml -o myprog