CC := gcc
CWARNS := -Wall -Wextra
COPT := -O2 -fno-math-errno -ftrapping-math -fomit-frame-pointer
CFLAGS := -std=c99 -std=c99 -march=native -mtune=native $(CWARNS) $(COPT)

all: mkdirs libmatrix libtransform

mkdirs:
	mkdir -p libs
	mkdir -p objs

libmatrix: mkdirs
	$(CC) $(CFLAGS) matrix.c -c
	mv matrix.o objs/matrix.o
	ar rsc libmatrix.a objs/matrix.o
	mv libmatrix.a libs/libmatrix.a

libtransform: mkdirs
	$(CC) $(CFLAGS) transform.c -c
	mv transform.o objs/transform.o
	ar rsc libtransform.a objs/transform.o
	mv libtransform.a libs/libtransform.a
