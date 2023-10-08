CC = gcc
GLOBAL_FLAGS = -g
CPPFLAGS = -DNDEBUG -I. -I.. -I../include -I../include/cbuild
CFLAGS = $(GLOBAL_FLAGS) -Wall -Wextra -std=c11
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
BIN = cbuild

all: $(BIN)
$(BIN): $(OBJECTS)
	$(CC) -o $(BIN) $(GLOBAL_FLAGS) $(OBJECTS) ../lib/libbuild.a
clean:
	$(RM) $(OBJECTS)
	$(RM) $(BIN)
