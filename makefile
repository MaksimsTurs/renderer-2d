LIB_PATH := -L./libs
INCLUDE_PATH := -I./includes

CC := gcc
CWARN	:= -Wall -Wextra -Wshadow -Wundef
COPT := -O2 -mtune=native -march=native
CFLAGS := $(CWARN) $(COPT) -std=c99 $(LIB_PATH) $(INCLUDE_PATH)

all: mkdirs libframebuffer

mkdirs:
	mkdir -p libs
	mkdir -p objs

libframebuffer: mkdirs
	$(CC) $(CFLAGS) framebuffer.c -c
	mv framebuffer.o objs/framebuffer.o
	$(CC) $(CFLAGS) utils.c -c
	mv utils.o objs/utils.o
	ar rsc libframebuffer.a objs/framebuffer.o objs/utils.o
	mv libframebuffer.a libs/libframebuffer.a
