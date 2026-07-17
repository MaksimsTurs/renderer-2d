CCOMPILER := gcc
CWARNS		:= -Wall -Wextra
COPT			:= -std=c99 -march=native -mtune=native -O2 -fno-math-errno -ftrapping-math

all: mkdirs libvector libmatrix libtransform

mkdirs:
	mkdir -p libs
	mkdir -p objs

libvector: mkdrs
	$(CCOMPILER) $(CWARNS) $(COPT) vector.c -c
	mv vector.o objs/vector.o
	ar rsc libvector.a objs/vector.o
	mv libvector.a libs/libvector.a

libmatrix: mkdirs
	$(CCOMPILER) $(CWARNS) $(COPT) matrix.c -c
	mv matrix.o objs/matrix.o
	ar rsc libmatrix.a objs/matrix.o
	mv libmatrix.a libs/libmatrix.a

libtransform: mkdirs
	$(CCOMPILER) $(CWARNS) $(COPT) transform.c -c
	mv transform.o objs/transform.o
	$(CCOMPILER) $(CWARNS) $(COPT) vector.c -c
	mv vector.o objs/vector.o
	ar rsc libtransform.a objs/transform.o objs/vector.o
	mv libtransform.a libs/libtransform.a
