CC = gcc
CFLAGS = -g -Wall -Wextra
CPPFLAGS = -I.. -I. -I../include
LIBBUILD_OBJECTS = libbuild.o alloc.o log.o
LIBCBUILD_OBJECTS = $(LIBBUILD_OBJECTS) libcbuild.o entry.o 

all: libbuild libcbuild

libbuild: $(LIBBUILD_OBJECTS)
	$(AR) -rc libbuild.a $(LIBBUILD_OBJECTS)

libcbuild: $(LIBCBUILD_OBJECTS)
	$(AR) -rc libcbuild.a $(LIBCBUILD_OBJECTS)

clean:
	$(RM) *.a
	$(RM) *.o
