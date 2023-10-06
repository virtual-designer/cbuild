CC = gcc
GLOBAL_FLAGS = -g
# CPPFLAFS = -DNDEBUG
CFLAGS = $(GLOBAL_FLAGS) -Wall -Wextra -std=c11
OBJECTS = $(patsubst %.c, %.o, $(wildcard src/*.c))
BIN = cbuild

all: $(BIN)
$(BIN): $(OBJECTS)
	$(CC) -o $(BIN) $(GLOBAL_FLAGS) $(OBJECTS)
clean:
	$(RM) $(OBJECTS)
	$(RM) $(BIN)
