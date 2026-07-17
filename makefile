LIB_PATH			:= libs

CCOMPILER			:= gcc
CWARN_FLAGS		:= -Wall -Wextra -Wswitch-default -Wshadow -Wundef
CEXTRA_FLAGS	:= -L$(LIB_PATH) -std=c99 -mtune=native -march=native
COPT_FLAGS		:= -O2

LIBS					:= -lm -l:libvector.a

all: mkdirs makedeps
	$(CCOMPILER) $(CWARN_FLAGS) $(CEXTRA_FLAGS) $(COPT_FLAGS) framebuffer.c -c $(LIBS)
	mv framebuffer.o objs/framebuffer.o
	$(CCOMPILER) $(CWARN_FLAGS) $(CEXTRA_FLAGS) $(COPT_FLAGS) utils.c -c $(LIBS)
	mv utils.o objs/utils.o
	ar rsc libframebuffer.a objs/framebuffer.o objs/utils.o
	mv libframebuffer.a libs/libframebuffer.a

mkdirs:
	mkdir -p libs
	mkdir -p objs

makedeps:
	cd deps/linear-algebra.c && make libvector
	cp deps/linear-algebra.c/libs/* libs
